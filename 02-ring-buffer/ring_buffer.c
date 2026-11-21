#include "ring_buffer.h"

void rb_init(RingBuffer *rb){
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}

int rb_push(RingBuffer *rb, uint8_t byte){
    if (rb->count == RB_SIZE){
        return -1;
    } else {
        rb->buffer[rb->head] = byte;
        rb->head = (rb->head + 1) % RB_SIZE;
        rb->count++;
        return 0;
    }    
}

int rb_pop(RingBuffer *rb, uint8_t *out){
    if (rb->count == 0){
        return -1;
    } else {
        *out = rb->buffer[rb->tail];
        rb->tail = (rb->tail + 1) % RB_SIZE;
        rb->count--;
        return 0;
    }
}

int rb_peek(RingBuffer *rb, uint8_t *out){
    if (rb->count == 0){
        return -1;
    } else {
        *out = rb->buffer[rb->tail];
        return 0;
    }
}

int rb_count(RingBuffer *rb){
    return rb->count;
}

int rb_is_full(RingBuffer *rb){
    return rb->count == RB_SIZE;
}

int rb_is_empty(RingBuffer *rb){
    return rb->count == 0;
}

void rb_clear(RingBuffer *rb){
    rb->head = 0;
    rb->tail = 0;
    rb->count = 0;
}