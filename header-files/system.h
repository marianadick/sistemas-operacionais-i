#ifndef system_h
#define system_h

#include <stdio.h>
#include "thread.h"
#include "traits.h"
#include "debug.h"

__BEGIN_API

class System
{
public:
    /*
     * Este método irá realizar a inicialização de todas as variáveis internas do SO.
     */ 
    // ESTÁ RECLAMANDO DE OVERLOADING
    //static void init();

    /*
     * Cria a Thread Main
     */
    static void init(void (*mainFunction)(void *));
};

__END_API

#endif