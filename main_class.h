#ifndef main_class_h
#define main_class_h

#include <iostream>
#include "cpu.h"
#include "traits.h"
#include "thread.h"
#include "semaphore.h"

#include "Engine.h"

__BEGIN_API

class MainClass
{
public:
    MainClass() {}
    
    ~MainClass() {}

    static void runGame(void * name);
};

__END_API

#endif
