#include "thread.h"

__BEGIN_API

// Inicializando atributos de Thread
Thread * Thread::_running = nullptr;
unsigned int Thread::_thread_counter = 0;

int Thread::switch_context(Thread * prev, Thread * next) 
{   
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

    // ????????? N entendi o q implementar aqui ainda
};

int Thread::id() 
{
    return _id;
};

CPU::Context * Thread::context()
{
    return _context;
};

__END_API