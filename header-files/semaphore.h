#ifndef semaphore_h
#define semaphore_h

#include "cpu.h"
#include "thread.h"
#include "traits.h"
#include "debug.h"
#include "list.h"

__BEGIN_API

class Semaphore
{
public:

    typedef Ordered_List<Thread> Waiting_Queue;

    Semaphore(int v = 1) {
        value = v;
        new (&_waiting) Waiting_Queue();
    };

    ~Semaphore() {
        wakeup_all();
    };

    void p();
    void v();

private:
    // Atomic operations
    int finc(volatile int & number);
    int fdec(volatile int & number);

    // Thread operations
    void sleep();
    void wakeup();
    void wakeup_all();

private:
    /* ATRIBUTOS DO SEMÁFORO */

    /*
     * Indica a capacidade do semáforo
     */ 
    int value;

    /*
     * Fila de threads esperando o semáforo ser liberado
     */ 
    Waiting_Queue _waiting;
};

__END_API

#endif
