#include "cpu.h"
#include <iostream>

__BEGIN_API

// Salva o contexto atual no ponteiro recebido como parâmetro 
void CPU::Context::save()
{
    getcontext(&this->_context);
}

// Restaura o contexto salvo previamente no ponteiro recebido como parâmetro
void CPU::Context::load()
{
    setcontext(&this->_context);
}

// Desalocar espaço ocupado pela STACK
CPU::Context::~Context()
{
    delete(_stack);
}

// int swapcontext(ucontext_t *restrict oucp, const ucontext_t *restrict ucp);
// Salva o contexto atual em "oucp" (primeiro arg.) e restaura o contexto previamente salvo em "ucp" (segundo arg.)
void CPU::switch_context(Context *from, Context *to)
{
    from->save();
    to->load();
}

__END_API
