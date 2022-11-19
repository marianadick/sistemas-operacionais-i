#include "thread.h"
#include <iostream>

__BEGIN_API

/* /------ INICIALIZAÇÃO E DECLARAÇÃO DE ATRIBUTOS DA CLASSE THREADS ------/ */

Thread * Thread::_running = nullptr;
unsigned int Thread::_thread_counter = 0;

// Thread main e dispatcher, além do contexto da main
Thread Thread::_main;
Thread Thread::_dispatcher;
CPU::Context Thread::_main_context;

// Filas de threads prontas e suspensas
Thread::Ready_Queue Thread::_ready;
Thread::Ready_Queue Thread::_suspended;

/* /---------------------------------------------------------/ */



/* /------ MÉTODOS DA CLASSE THREADS ------/ */

 void Thread::init(void (*main)(void *))
{
    db<Thread>(TRC) << ">> Threads main and dispatcher are being initialized.\n";

    // Instancia as filas de threads prontas e suspensas
    new (&_ready) Thread::Ready_Queue();
    new (&_suspended) Thread::Ready_Queue();

    // Instancia a thread Main
    new (&_main) Thread(main, (void *) "Main");

    // Instancia main context
    new (&_main_context) CPU::Context();

    // Instancia a thread Dispatcher 
    // [Cast para void pointer do método dispatcher, em seguida é feito um cast para void do conteúdo desse void pointer]
    new (&_dispatcher) Thread((void (*) (void *)) &Thread::dispatcher, (void *) NULL);

    // Atualiza o ponteiro da thread em execução e altera o estado da main para RUNNING
    Thread::_running = &Thread::_main;
    Thread::_main._state = RUNNING;
    
    // Troca o contexto de fato
    CPU::switch_context(&_main_context, _main.context());
};

void Thread::dispatcher()
{
    db<Thread>(TRC) << ">> Dispatcher is scheduling next thread.\n";
    while (Thread::_thread_counter > 2) {
        // Escolhe uma thread da fila para ser executada
        Thread * next = Thread::_ready.remove()->object();

        // Adiciona dispatcher na fila novamente
        Thread::_dispatcher._state = READY;
        Thread::_ready.insert(&Thread::_dispatcher._link);

        // Atualiza o ponteiro _running para apontar para a próxima
        Thread::_running = next;
        next->_state = RUNNING;

        // Troca o contexto entre a dispatcher e a próxima
        Thread::switch_context(&Thread::_dispatcher, next);
        if (next->_state == FINISHING) {
            Thread::_ready.remove(next);
        }
    }

    // Finaliza a dispatcher e retorna o controle para a main
    Thread::_dispatcher._state = FINISHING;
    Thread::_ready.remove(&Thread::_dispatcher);
    Thread::switch_context(&Thread::_dispatcher, &Thread::_main);
};

void Thread::yield()
{
    db<Thread>(TRC) << ">> Thread [" << Thread::_running->id() <<"] is yielding.\n";

    // Mantém a referência da thread a ser substituída
    Thread * prev = Thread::_running;

    // Se a thread atual estiver finalizando e tiver feito uma requisição de join, ela deve chamar resume()
    // para que a thread que chamou join() [que está suspensa], seja reinserida na fila de prontos
    if (prev->_state == FINISHING && prev->_joining != nullptr) 
    {
        prev->resume();
    }

    // Remove da fila e retorna o ponteiro para a thread em questão
    Thread * next = Thread::_ready.remove()->object();

    // Atualiza a prioridade da tarefa que estava sendo executada [Thread::running]
    // Isso ocorre apenas de ela não estiver finalizando, suspensa, esperando e não for a main
    if (prev->_state != FINISHING && prev->_state != SUSPENDED && prev->_state != WAITING && prev != &Thread::_main) 
    {
        // Atualiza a posição na lista
        prev->_link.rank(std::chrono::duration_cast<std::chrono::microseconds>
            (std::chrono::high_resolution_clock::now().time_since_epoch()).count());

        // Reinsere
        prev->_state = READY;
        Thread::_ready.insert(&prev->_link);
    }

    // Atualiza running e troca o contexto
    Thread::_running = next;
    next->_state = RUNNING;
    Thread::switch_context(prev, next);
}

int Thread::join()
{
    db<Thread>(TRC) << ">> Thread [" << this->id() << "] wants to join.\n";
    // Na primeira vez que chama join (_running = Main)    
    _joining = _running;
    _joining->suspend();
    return _exit_code;
}

void Thread::suspend()
{
    db<Thread>(TRC) << ">> Thread [" << this->id() << "] is suspending.\n";
    // Remove da fila de prontos
    Thread::_ready.remove(this);
    // Troca o estado e a adiciona na fila de suspensas
    _state = SUSPENDED;
    Thread::_suspended.insert(&this->_link);
    yield();
}

void Thread::resume()
{
    db<Thread>(TRC) << ">> Thread [" << this->id() << "] is resuming.\n";
    // Remove da fila de suspensas a thread que efetuou o join
    Thread::_suspended.remove(_joining);
    // Adiciona na fila de prontos
    _joining->_state = READY;
    Thread::_ready.insert(&_joining->_link);
}

void Thread::sleep() {
    db<Thread>(TRC) << ">> Thread [" << this->id() << "] is sleeping.\n";
    _state = WAITING;
    yield();
}
    
void Thread::wakeup() {
    db<Thread>(TRC) << "Thread [" << this->id() << "] is waking up.\n";
    // Insere a thread acordada na fila de prontos
    _state = READY;
    Thread::_ready.insert(&this->_link);
    yield();
}

int Thread::switch_context(Thread * prev, Thread * next) 
{   
    db<Thread>(TRC) << ">> Switching context from Thread [" << prev->id() << "] " <<
                        "to Thread [" << next->id() <<"].\n";

    // Verifica os id's das 2 para ver se não são a mesma thread
    if (prev->id() != next->id()) {
        Thread::_running = next;
        return CPU::switch_context(prev->_context, next->_context);
    }
    return 0;
};

CPU::Context * Thread::context()
{
    return _context;
};

Thread::Ready_Queue::Element * Thread::link() {
    return &_link;
};

int Thread::id() 
{
    return _id;
};

Thread::~Thread() 
{
    db<Thread>(TRC) << ">> Thread [" << id() << "] has ended.\n";
    // Remove a thread em questão da fila de prontos
    Thread::_ready.remove(this);        
    if (_context) {
        delete _context;
    }
};

void Thread::thread_exit (int exit_code) 
{
    db<Thread>(TRC) << ">> Thread [" << id() << "] exit code: " << exit_code << ".\n";
    Thread::_thread_counter--;
    Thread::_exit_code = exit_code;
    _state = FINISHING;
    yield();
};

/* /---------------------------------------------------------/ */

__END_API