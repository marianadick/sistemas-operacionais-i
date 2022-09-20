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
        return CPU::switch_context(prev->context(), next->context());
    }
    return 0;
};

void Thread::thread_exit (int exit_code) 
{
    // IGNORAR exit_code POR ENQUANTO (nesse trabalho 2)

    db<Thread>(TRC) << ">> Thread exit code: " << exit_code << "\n";
    Thread::_exit_code = exit_code;
    _thread_counter--;
};

int Thread::id() 
{
    return _id;
};

CPU::Context * Thread::context()
{
    return _context;
};

Thread::~Thread() {
    db<Thread>(TRC) << ">> Thread " << Thread::_running->id() << " has ended.\n";
    if (_context) {
        delete _context;
    }
};

__END_API