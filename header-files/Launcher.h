#ifndef LAUNCHER_H
#define LAUNCHER_H

#include "Creep.h"

__BEGIN_API

class Creep;

class Launcher
{
public:
    virtual ~Launcher() {}

    virtual void runLauncher() = 0;
    virtual void createCreepGroup() = 0;
    virtual void createCreepBehavior() = 0;
    virtual void removeCreep(Creep * creep) = 0;
};

__END_API

#endif