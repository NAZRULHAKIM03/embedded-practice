# Strings & Parsing

Text manipulation for embedded systems — formatting numbers into buffers,
converting between bytes and hex strings and parsing command lines from
a UART. No `stdlib.h` conversion functions: everything is hand-written
with fixed-width types, no malloc and explicit buffer sizes.

## Files

- `str_utils.h` — declarations grouped into itoa / hex / parse sections
- `str_utils.c` — implementation
- `test_strings.c` — assert-based tests covering all functions

## Functions

**itoa**
- `u32_to_dec`, `i32_to_dec` — integer to decimal string (signed handles INT32_MIN safely)
- `u32_to_hex` — u32 to 8 zero-padded lowercase hex chars

**hex**
- `hex_to_u8` — parse 2 hex chars into a byte
- `u8_to_hex` — write a byte as 2 hex chars

**parse**
- `parse_u32_dec` — decimal string to u32 with overflow detection
- `parse_tokens` — split a command line in-place by whitespace (including \r\n)

## Build & Run

    clang -Wall -Wextra -std=c11 str_utils.c test_strings.c -o test_strings
    ./test_strings

## Tests

Cover zero, max u32, INT32_MIN, buffer-too-small, invalid hex chars,
overflow, empty strings, and an end-to-end "SET LED 1" command parse.

## Notes

- `parse_tokens` modifies its input in place — don't pass a `const`
  string literal.
- All buffers are caller-supplied with explicit sizes; overflow is
  reported as `-1`, not asserted. Callers decide whether to abort.
- No `atoi`/`strtol`/`sprintf` — the whole point is to know what's
  happening at the byte level.