#include "header-files/system.h"
#include "header-files/debug.h"
#include "header-files/thread.h"
#include "header-files/traits.h"
#include <iostream>

__BEGIN_API

void System::init(void (*mainFuntion)(void *))
{
	db<System>(TRC) << ">> Initializing System.\n";
	Thread::init(mainFuntion);
}

__END_API