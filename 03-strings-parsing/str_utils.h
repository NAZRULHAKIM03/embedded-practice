#ifndef STR_UTILS_H
#define STR_UTILS_H

#include <stdint.h>
#include <stddef.h>

/* --------- itoa : integer -> string ----------- */

// Convert unsigned 32-bit to decimal (no leading zeros). Null-terminates.
// Returns string length or -1 if buf is too small.
int u32_to_dec(uint32_t value, char *buf, size_t buflen);

// Convert signed 32-bit to decimal (with '-' for negatives). Null-terminates.
// Must handle INT32_MIN without overflow. Returns length or -1.
int i32_to_dec(int32_t value, char *buf, size_t buflen); 

// Convert u32 to exactly 8 zero-padded lowercase hex chars + null.
// buf must be >= 9 bytes. Returns 8 or -1.
int u32_to_hex(uint32_t value, char *buf, size_t buflen);

/* -------- hex conversion ------------------- */

// Parse exactly 2 hex chars ("0A", "ff", "FF") into a byte.
// Returns 0 on success, -1 if either char is not a hex digit.
int hex_to_u8(const char *s, uint8_t *out);

// Write a byte as 2 lowercase hex chars + null. buf must be >= 3 bytes.
// Return 2 on success, -1 if buf is too small.
int u8_to_hex(uint8_t value, char *buf, size_t buflen);

/* -------- decimal parsing ----------------- */

// Parse a decimal string (digits only, no sign, no whitespace) into u32.
// Returns 0 on success, -1 on empty / non-digit / overflow.
int parse_u32_dec(const char *s, uint32_t *out);

/* ------- command tokenizer ---------------- */

// Split 'line' in-place by spaces, tabs, '\r', '\n'.
// Writes token pointers into 'tokens' (must hold 'max_tokens' pointers).
// Returns token count (0 for empty/whitespace-only), or -1 if too many.
int parse_tokens(char *line, char *tokens[], int max_tokens);

#endif