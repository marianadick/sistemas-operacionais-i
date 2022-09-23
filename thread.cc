#include "thread.h"
#include <iostream>

__BEGIN_API

// Inicializando atributos de Thread
Thread * Thread::_running = nullptr;
unsigned int Thread::_thread_counter = 0;

int Thread::switch_context(Thread * prev, Thread * next) 
{   
    db<Thread>(TRC) << ">> Switching context from Thread [" <<  prev->id() << "] " <<
                        "to Thread [" << next->id() <<"]\n";
    // Verifica os id's das 2 para ver se não são a mesma thread
    if (prev->id() != next->id()) {
        Thread::_running = next;
        return CPU::switch_context(prev->_context, next->_context);
    }
    return 0;
};

void Thread::thread_exit (int exit_code) 
{
    // IGNORAR exit_code POR ENQUANTO (nesse trabalho 2)

    db<Thread>(TRC) << ">> Thread [" << id() << "] exit code: " << exit_code << "\n";
    _exit_code = exit_code;
    _thread_counter--;
};

int Thread::id() 
{
    return _id;
};

void Thread::dispatcher()
{
    db<Thread>(TRC) << ">> Scheduling next thread.";
    while (Thread::_thread_counter > 2) {
        // Escolhe primeira thread da fila para ser executada
        // TO-FIX Mariana: Não tem uma maneira melhor de pegar isso?
        Thread * next = Thread::_ready.remove()->object();

        // Adiciona dispatcher na fila novamente
        Thread::_dispatcher._state = READY;
        Thread::_ready.insert(&Thread::_dispatcher._link);

        // Atualiza o ponteiro _running para apontar para a próxima
        Thread::_running = next;
        // Atualiza estado
        Thread::_running->_state = RUNNING;

        // Troca o contexto
        Thread::switch_context(&Thread::_dispatcher, Thread::_running);
        if (Thread::_running->_state == FINISHING) {
            Thread::_ready.remove(Thread::_running);
        }
    }
    Thread::_dispatcher._state = FINISHING;
    Thread::_ready.remove(&Thread::_dispatcher._link);
    Thread::switch_context(&Thread::_dispatcher, &Thread::_main);
};

 void Thread::init(void (*main)(void *))
{
    db<Thread>(TRC) << ">> Threads main and dispatcher are being initialized.\n";
};

CPU::Context * Thread::context()
{
    return _context;
};

Thread::~Thread() {
    db<Thread>(TRC) << ">> Thread [" << id() << "] has ended.\n";
    if (_context) {
        delete _context;
    }
};

__END_API