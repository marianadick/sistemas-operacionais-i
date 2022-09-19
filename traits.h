#ifndef traits_h
#define traits_h

// Não alterar as 3 declarações abaixo

#define __BEGIN_API             namespace SOLUTION {
#define __END_API               }
#define __USING_API            using namespace SOLUTION;

__BEGIN_API

class CPU; // Declaração das classes criadas nos trabalhos devem ser colocadas aqui
class System;
class Debug;
class Thread;

// Declaração da classe Traits
template<typename T> struct Traits {
};

template<> struct Traits<Debug>: public Traits<void>
{
    static const bool error = false;
    static const bool warning = false;
    static const bool info = false;
    static const bool trace = false;
};

template<> struct Traits<CPU> : public Traits<void>
{
    // Declaração do tamanho da Pilha (32 kB)
    static const unsigned int STACK_SIZE = 1024 * 32;
    static const bool debugged = true;
};

template<> struct Traits<System> : public Traits<void>
{
    static const bool debugged = true;
};

template<> struct Traits<Thread> : public Traits<void>
{
    static const bool debugged = true;
};

__END_API

#endif

