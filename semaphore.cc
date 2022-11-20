#include "semaphore.h"
#include <iostream>

__BEGIN_API

void Semaphore::p() {
    if (fdec(value) < 0) {
        sleep();
    }
}

void Semaphore::v() {
    if (finc(value) < 1) {
        wakeup();
    }
}

int Semaphore::finc(volatile int & number) {
    return CPU::finc(number);
}

int Semaphore::fdec(volatile int & number) {
    return CPU::fdec(number);
}

void Semaphore::sleep() {
    Thread * asleep_thread = Thread::running();
    // Coloca a thread atual na fila de espera e deixa ela dormindo
    _waiting.insert(asleep_thread->link());
    asleep_thread->sleep();
}

void Semaphore::wakeup() {
    // Pega a próxima thread da fila de espera e a acorda
    Thread * awaken_thread = _waiting.remove()->object();
    awaken_thread->wakeup();
}

void Semaphore::wakeup_all() {
    // Acorda todas as threads na fila de espera
    while (_waiting.size()) {
        wakeup();
    }
}

__END_API