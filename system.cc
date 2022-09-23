#include "system.h"
#include <iostream>
#include "thread.h"

__BEGIN_API

void System::init() 
{
    db<System>(TRC) << ">> System initialized\n";
    Thread::init(main);
};

__END_API