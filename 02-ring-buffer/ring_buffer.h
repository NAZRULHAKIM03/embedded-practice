#ifndef RING_BUFFER_H
#define RING_BUFFER_H

#include <stdint.h>

#define RB_SIZE 256

typedef struct {
    uint8_t buffer[RB_SIZE];
    int head;       // index of the next write
    int tail;       // index of the next read
    int count;      // number of byte currently stored
} RingBuffer;

void rb_init(RingBuffer *rb);
int rb_push(RingBuffer *rb, uint8_t byte);  // 0 = ok, -1 = full
int rb_pop(RingBuffer *rb, uint8_t *out);   // 0 = ok, -1 = empty
int rb_peek(RingBuffer *rb, uint8_t *out);  // 0 = ok, -1 = empty
int rb_count(RingBuffer *rb);
int rb_is_full(RingBuffer *rb);
int rb_is_empty(RingBuffer *rb);
void rb_clear(RingBuffer *rb);

#endif