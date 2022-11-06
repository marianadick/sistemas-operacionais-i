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

// Fila de threads prontas
Thread::Ready_Queue Thread::_ready;

/* /---------------------------------------------------------/ */



/* /------ MÉTODOS DA CLASSE THREADS ------/ */

 void Thread::init(void (*main)(void *))
{
    db<Thread>(TRC) << ">> Threads main and dispatcher are being initialized.\n";

    // Instancia a fila de threads prontas
    new (&_ready) Thread::Ready_Queue();

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
        // Escolhe primeira thread da fila para ser executada
        Thread * next = Thread::_ready.remove()->object();

        // Adiciona dispatcher no final da fila novamente
        Thread::_dispatcher._state = READY;
        Thread::_ready.insert(&Thread::_dispatcher._link);

        // Atualiza o ponteiro _running para apontar para a próxima
        Thread::_running = next;
        
        // Atualiza estado
        next->_state = RUNNING;

        // Troca o contexto
        Thread::switch_context(&Thread::_dispatcher, next);
        if (next->_state == FINISHING) {
            Thread::_ready.remove(next);
        }
    }
    Thread::_dispatcher._state = FINISHING;
    Thread::_ready.remove(&Thread::_dispatcher);
    Thread::switch_context(&Thread::_dispatcher, &Thread::_main);
};

void Thread::yield()
{
    db<Thread>(TRC) << ">> Thread [" << Thread::_running->id() <<"] is yielding.\n";

    // Mantém a referência da thread a ser substituída
    Thread * prev = Thread::_running;

    // Remove da fila e retorna o ponteiro para a thread em questão
    Thread * next = Thread::_ready.remove()->object();

    // Atualiza a prioridade da tarefa que estava sendo executada [Thread::running]
    // Isso ocorre apenas de ela não estiver finalizando e não for a main
    if (prev->_state != FINISHING && prev != &Thread::_main) 
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

int Thread::switch_context(Thread * prev, Thread * next) 
{   
    db<Thread>(TRC) << ">> Switching context from Thread [" <<  prev->id() << "] " <<
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

int Thread::id() 
{
    return _id;
};

Thread::~Thread() 
{
    db<Thread>(TRC) << ">> Thread [" << id() << "] has ended.\n";

    // Varre a lista e, caso encontre, remove a thread em questão dela
    Thread::_ready.remove(this);        
    if (_context) {
        delete _context;
    }
};

void Thread::thread_exit (int exit_code) 
{
    // IGNORAR exit_code POR ENQUANTO

    db<Thread>(TRC) << ">> Thread [" << id() << "] exit code: " << exit_code << ".\n";
    Thread::_thread_counter--;
    _exit_code = exit_code;
    _state = FINISHING;
    yield();
};

/* /---------------------------------------------------------/ */

__END_API