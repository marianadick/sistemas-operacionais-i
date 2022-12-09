#include "system.h"
#include "header-files/debug.h"
#include "header-files/thread.h"
#include "header-files/traits.h"
#include <iostream>

__BEGIN_API

void System::init(void (*mainFuntion)(void *))
{
	db<System>(INF) << "System::init() chamado\n";
	setvbuf(stdout, 0, _IONBF, 0);

	Thread::init(mainFuntion);
}

__END_API