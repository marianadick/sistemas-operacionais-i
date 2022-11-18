#include "cpu.h"
#include <iostream>

__BEGIN_API

// Salva o contexto atual no ponteiro do contexto
void CPU::Context::save()
{
    getcontext(&this->_context);
}

// Restaura o contexto salvo previamente no ponteiro do contexto
void CPU::Context::load()
{
    setcontext(&this->_context);
}

// Desaloca espaço ocupado pela STACK
CPU::Context::~Context()
{
    // Verifica se existe uma STACK antes de tentar deletá-la
    if (_stack) {
        delete(_stack);
    }
}

// Troca contexto de 'from' para 'to'
int CPU::switch_context(Context *from, Context *to)
{   
    // retorna 0 se sucesso, retorna -1 se erro
    return swapcontext(&from->_context, &to->_context);
}

int CPU::finc(volatile int & number){
    int val = 1;
    int r;

    asm(
       "lock\n\t"
       "xadd %1, %0":
       "+m"( number), "=r"(r):
       "1"( val ):
       "memory", "cc");

    return number;
}

int CPU::fdec(volatile int & number){
    int val = -1;
    int r;

    asm(
       "lock\n\t"
       "xadd %1, %0":
       "+m"( number), "=r"(r):
       "1"( val ):
       "memory", "cc");

    return number;
}

__END_API
