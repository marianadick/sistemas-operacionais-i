#ifndef thread_h
#define thread_h

#include "cpu.h"
#include "traits.h"
#include "debug.h"
#include "list.h"
#include <ctime> 
#include <chrono>

__BEGIN_API

class Thread
{
protected:
    typedef CPU::Context Context;
public:

    typedef Ordered_List<Thread> Ready_Queue;

    // Thread State
    enum State {
        RUNNING,
        READY,
        FINISHING,
        SUSPENDED
    };

    /*
     * Construtor vazio. Necessário para inicialização, mas sem importância para a execução das Threads.
     */ 
    Thread() { }

    /*
     * Cria uma Thread passando um ponteiro para a função a ser executada
     * e os 'N' parâmetros passados para a função. Além disso, instancia o contexto da Thread.
     * PS: devido ao template, este método deve ser implementado neste mesmo arquivo .h
     */ 
    template<typename ... Tn>
    Thread(void (* entry)(Tn ...), Tn ... an);

    /*
     * Retorna a Thread que está em execução.
     */ 
    static Thread * running() { return _running; }

    /*
     * Método para trocar o contexto entre duas thread, a anterior (prev) e a próxima (next).
     * Deve encapsular a chamada para a troca de contexto realizada pela class CPU.
     * Valor de retorno é negativo se houve erro, ou zero caso contrário.
     */ 
    static int switch_context(Thread * prev, Thread * next);

    /*
     * Termina a thread.
     * exit_code é o código de término devolvido pela tarefa. 
     */  
    void thread_exit (int exit_code);

    /*
     * Retorna o ID da thread.
     */ 
    int id();

    /*
     * Disptacher de threads. 
     * Enquanto houverem threads do usuário Chama o escalonador para definir a próxima tarefa a ser executada.
     */
    static void dispatcher(); 

    /*
     * Realiza a inicialização da class Thread.
     * Cria as Threads main e dispatcher. Troca contexto para Thread Main.
     */ 
    static void init(void (*main)(void *));

    /*
     * Devolve o processador para a thread dispatcher que irá escolher outra thread pronta
     * para ser executada.
     */
    static void yield(); 

    /*
     * Suspende a thread atualmente em execução até que a thread alvo finalize. O inteiro retornado 
     * é o argumento recebido por thread_exit().
     */
    int join();

    /*
     * Suspende a thread até que o resume() seja chamado.
     */ 
    void suspend();

    /*
     * Coloca uma thread que estava suspensa de volta na fila de prontos.
     */
    void resume();

    /*
     * Destrutor de uma thread. Realiza todo os procedimentos para manter a consistência da classe.
     */ 
    ~Thread();

    /*
     * Qualquer outro método que você achar necessário para a solução.
     */ 

    Context * context();

private:
    int _id;
    Context * volatile _context;
    static Thread * _running;
    
    static Thread _main; 
    static CPU::Context _main_context;
    static Thread _dispatcher;
    static Ready_Queue _ready;
    static Ready_Queue _suspended;
    Ready_Queue::Element _link;
    volatile State _state;

     /*
      * Atributo de classe para contagem do número de threads (inicializado em thread.cc) 
      */
    static unsigned int _thread_counter;

    /*
     * Armazena o exit_code da thread
     */ 
    int _exit_code;

    /*
     * Informa se a thread em questão fez uma requisição de join
     */ 
    bool _called_join;
};

/*
 * Construtor da Thread. Além disso, antes de instanciar um objeto, inicializa o atributo _link do mesmo
 */
template<typename ... Tn>
Thread::Thread(void (* entry)(Tn ...), Tn ... an) : _link(this, (std::chrono::duration_cast<std::chrono::microseconds>
    (std::chrono::high_resolution_clock::now().time_since_epoch()).count()))
{
    db<Thread>(TRC) << ">> Thread [" << _thread_counter << "] was created\n";

    _context = new CPU::Context(entry, an ...);
    _id = Thread::_thread_counter++;    

    // Insere na lista e altera seu estado para READY
    if (_id > 0)
        _ready.insert(&_link);
    _state = READY;
}

__END_API

#endif