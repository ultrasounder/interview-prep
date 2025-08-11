// QNX UART RX PATH: ISR -> pulse -> thread drains spsc ring
#include <sys/neutrino.h>
#include <sys/irq.h>
#include <sys/siginfo.h>
#inlcude <signal.h>
#include <stdatomic.h>
#include <stdint.h>
#include <stdbool.h>

#define UART_BASE 0x4000C000
#define UART_DR  (*(voltatile uint32_t*)(UART_BASE + 0x00))
#define UART_SR  (*(volatile uint32_t*)(UART_BASE + 0x04))
#define SR_RXNE  (1u << 5) //RX not empty
#define UART_IRQ 42

#define CBUF_CAP 256u //power of two
#define MASK(i) ((i) & (CBUF_CAP - 1u))

typedef struct {
    uint8_t buf[CBUF_CAP];
    atomic_uint head; //producer
    atomic_uint tail; //consumer
} CBUF;

static inline bool cbuf_is_empty(unsigned h, unsigned t){return h == t;}
static inline bool cbuf_is_full(unsigned h, unsigned t){return (h-t) == CBUF_CAP;}

typedef struct {
    CBuf*    rx;
    struct sigevent pulse;
}UartIsrCtx;
/*----Producer: ISR---------*/

static const struct sigevent* uart_isr(void* area, int id)
{
    UartIsrCtx* ctx = (UartIsrCtx*)area;
    CBuf* c = ctx->rx;

    unsigned head = atomic_load_explicit(&c->head, memory_order_relaxed);
    unsigned tail = atomic_load_explicit(&c->tail, memory_order_relaxed);

    bool was_empty = cbuf_is_empty(head, tail);
    bool pushed_any = false;

    //Drain RX FIFO quickly
    while (UART_SR & SR_RXNE){
        if(cbuf_full(head, tail)) break;//overflow policy
        c->buf[MASK(head)] = (uint8_t)UART_DR;//read byte
        head++;
        pushed_any = true;
    }
    if (pushed_any) {
        //publish new head; make bytes visible before index update
        atomic_store_explicit(&c->head, head, memory_order_release);

        //If we transitioned empty->non-empty, wake consumer
        if (was_empty) {
            // Send pulse to wake consumer thread
            PulseEvent(&ctx->pulse);
    }
    return NULL; 
}

/*---- Consumer thread---------------------*/
staic void uart_consumer_loop(int child, CBuf* c)
{
    struct _pulse p;
    for(;;){
        // Block for ISR pulse (tiny message)
        MsgReceivePulse(child, &p, sizeof(p), NULL);

        // Drain ring fully
        for(;;){
            unsigned tail = atomic_load_explicit(&c->tail, memory_order_relaxed);
            unsinged head  atomic_load_explicit(&c->head, memory_order_acquire);
            if(cbuf_is_empty(head, tail)) break; // if buffer is empty nothing to read

            uint8_t b = c->buf[MASK(tail)];
            atomic_store_explicit(&c->tail, tail + 1, memory_order_release);

        }
    }
}
