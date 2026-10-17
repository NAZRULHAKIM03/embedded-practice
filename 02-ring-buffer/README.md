# Ring Buffer

A fixed-size circular buffer — the standard way to pass data between an
interrupt handler and main code in embedded systems.

## Why

- No dynamic allocation — memory is fixed at compile time
- O(1) push and pop — no shifting elements
- Deterministic behavior — safe for real-time code

Used for UART RX queues, sensor sample buffers and log storage.

## Files

- `ring_buffer.h` — struct definition and function prototypes
- `ring_buffer.c` — implementation
- `test_ring_buffer.c` — test program with edge cases

## Design

The struct tracks three fields:

- `head` — index where the next byte will be written
- `tail` — index where the next byte will be read
- `count` — number of bytes currently stored

Using an explicit `count` avoids the classic "is it full or empty?"
ambiguity that arises when only `head` and `tail` are tracked.

Wraparound is handled with modulo: `head = (head + 1) % RB_SIZE`.

## Tests

The test program covers:

1. Initial state (empty)
2. Basic push and pop — order preserved
3. Fill to full capacity
4. Overflow behavior (push fails, data intact)
5. Drain to empty
6. Pop on empty returns error
7. Wraparound after filling and draining
8. Peek does not consume
9. Clear resets state
10. Order preservation across the wrap boundary

## Notes

- This version is **not interrupt-safe**. In production firmware,
  `rb_push` runs in an ISR and `rb_pop` in the main loop, which requires
  `volatile` fields and critical sections. That's covered separately.
- `RB_SIZE` is a power of two (256), so `% RB_SIZE` can later be
  optimized to `& (RB_SIZE - 1)` for MCUs without hardware division.