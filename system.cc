#include "system.h"
#include <iostream>
#include "thread.h"

__BEGIN_API

void System::init() 
{
    db<System>(TRC) << ">> System initialized\n";
    setvbuf(stdout, 0, _IONBF, 0);
};

__END_API