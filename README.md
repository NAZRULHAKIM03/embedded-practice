# Embedded Practice

Low-level C exercises for embedded systems. bit manipulation, ring buffers,
state machines and other patterns used in firmware development.

Each folder covers one topic and has its own README with details.

## Topics

- `01-bit-manipulation/` — set/clear/toggle bits, extract bit fields, byte swaps
- `02-ring-buffer/` — fixed-size circular buffer for ISR ↔ main-loop data
- `03-strings-parsing/` — command parsing, hex conversion, itoa
- `04-state-machines/` — traffic light, button debounce
- `05-linked-list/` — free list memory pool (no malloc)

## Purpose

Practice writing clean, portable C for embedded roles. fixed-width types,
deterministic behavior, no hidden allocations. Not tied to any specific MCU.