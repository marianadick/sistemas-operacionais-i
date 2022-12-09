#include "header-files/system.h"

__BEGIN_API

void System::init(void (*mainFuntion)(void *))
{
	db<System>(INF) << "System::init() chamado\n";
	setvbuf(stdout, 0, _IONBF, 0);

	Thread::init(mainFuntion);
}

__END_API