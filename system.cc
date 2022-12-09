#include "header-files/system.h"
#include <iostream>
#include "header-files/thread.h"

__BEGIN_API

// Recebe uma função que não tem valor de retorno e recebe um pointeiro void
void System::init(void (*mainFunction)(void *)) 
{   
    db<System>(TRC) << ">> System initialized. Starting Thread Main initialization.\n";
    Thread::init(mainFunction);
};

__END_API