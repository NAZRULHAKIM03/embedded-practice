#include <stdio.h>
#include <assert.h>
#include "ring_buffer.h"

int main(){
    RingBuffer rb;
    uint8_t out;

    // Test 1: Initial State
    rb_init(&rb);
    assert(rb_is_empty(&rb));
    assert(rb_count(&rb) == 0);

    // Test 2: basic push/pop, order preserved
    assert(rb_push(&rb, 'A') == 0);
    assert(rb_push(&rb, 'B') == 0);
    assert(rb_push(&rb, 'C') == 0);
    assert(rb_count(&rb) == 3);
    assert(rb_pop(&rb, &out) == 0); assert(out == 'A');
    assert(rb_pop(&rb, &out) == 0); assert(out == 'B');
    assert(rb_pop(&rb, &out) == 0); assert(out == 'C');
    assert(rb_is_empty(&rb));

    // Test 3: fill to full
    for (int i=0; i<RB_SIZE; i++)
        assert(rb_push(&rb, (uint8_t)i) == 0);
    assert(rb_is_full(&rb));
    assert(rb_count(&rb) == RB_SIZE);

    // Test 4: Overflow - push fails, count unchanged, data intact
    assert(rb_push(&rb, 0xFF) == -1);
    assert(rb_count(&rb) == RB_SIZE);
    assert(rb_peek(&rb, &out) == 0); assert(out == 0);  // First byte still 0

    // Test 5: drain to empty
    for (int i=0; i<RB_SIZE; i++)
        assert(rb_pop(&rb, &out) == 0);
    assert(rb_is_empty(&rb));
    assert(rb_count(&rb) == 0);

    // Test 6: pop on empty
    assert(rb_pop(&rb, &out) == -1);

    // Test 7: Wraparound - distinct values so order is verifiable
    for (int round=0; round<2; round++){
        for (int i=0; i<200; i++)
            assert(rb_push(&rb, (uint8_t)i) == 0);
        assert(rb_count(&rb) == 200);
        for (int i=0; i<200; i++){
            assert(rb_pop(&rb, &out) == 0); 
            assert(out == (uint8_t)i);
        }
        assert(rb_is_empty(&rb));
    }

    // Test 8: peek does not consume
    assert(rb_push(&rb, 'X') == 0);
    assert(rb_peek(&rb, &out) == 0); assert(out == 'X');
    assert(rb_count(&rb) == 1);
    assert(rb_pop(&rb, &out) == 0); assert(out == 'X');

    // Test 9: Clear resets state
    for (int i=0; i<10; i++)
        assert(rb_push(&rb, 0xCC) == 0);
    rb_clear(&rb);
    assert(rb_count(&rb) == 0);
    assert(rb_is_empty(&rb));

    // Test 10: order preservation across the wrap boundary
    for (int round=0; round<2; round++){
        for (int i=0; i<RB_SIZE; i++)
            assert(rb_push(&rb, (uint8_t)i) == 0);
        for (int i=0; i<RB_SIZE; i++){
            assert(rb_pop(&rb, &out) == 0);
            assert(out == (uint8_t)i);
        }
        assert(rb_is_empty(&rb));
    }

    printf("All 10 Tests passed.\n");
    return 0;
}