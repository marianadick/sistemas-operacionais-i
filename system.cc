#include "system.h"
#include <iostream>
#include "thread.h"

__BEGIN_API

// Recebe uma função que não tem valor de retorno e recebe um pointeiro void
void System::init(void (*main)(void *)) 
{   
    db<System>(TRC) << ">> System initialized. Starting Thread Main initialization.\n";
    setvbuf(stdout, 0, _IONBF, 0);
    Thread::init(main);
};

__END_API