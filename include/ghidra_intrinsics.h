/* Ghidra decompiler intrinsic pseudo-operations.
 *
 * Ghidra emits a fixed vocabulary of helper "functions" (CONCAT, SUB,
 * LOCK/UNLOCK, ROUND, ABS, ...) for byte-splicing and machine-level
 * operations that have no direct C spelling. The raw ports call these
 * by name; under MSVC's /Zs syntax-only check they were never linked so
 * nobody noticed they had no definition. A real link (winegcc, or any
 * full build) needs them defined - as MACROS, so no symbol is emitted
 * and the operations inline exactly as Ghidra intends.
 *
 * Semantics follow Ghidra's own documented conventions:
 *   CONCAT<hi><lo>(a,b) - concatenate an <hi>-byte high part and an
 *       <lo>-byte low part into an (hi+lo)-byte value (big-end first).
 *   SUB<from><size>(v,off) - extract <size> bytes at byte offset <off>
 *       from a <from>-byte value.
 *   ROUND/ABS - float round-to-nearest / absolute value.
 *   LOCK()/UNLOCK() - x86 bus-lock fences around an atomic sequence;
 *       no-ops here (the surrounding read-modify-write is already
 *       single-threaded-correct in this single-process client build).
 *
 * Only the width combinations the code actually uses are defined; add
 * more here if a new port needs them.
 */
#ifndef GB_GHIDRA_INTRINSICS_H
#define GB_GHIDRA_INTRINSICS_H

#include <stdint.h>

/* CONCAT<hi><lo>: (hi << lo*8) | lo-part, as an (hi+lo)-byte value.
 * The high part is masked to its width so a wider incoming value's
 * spare bits don't leak in. */
#define CONCAT11(hi, lo) \
    ((uint16_t)(((uint16_t)(uint8_t)(hi) << 8) | (uint8_t)(lo)))
#define CONCAT12(hi, lo) \
    ((uint32_t)(((uint32_t)(uint8_t)(hi) << 16) | (uint16_t)(lo)))
#define CONCAT13(hi, lo) \
    ((uint32_t)(((uint32_t)(uint8_t)(hi) << 24) | ((uint32_t)(lo) & 0x00ffffffu)))
#define CONCAT22(hi, lo) \
    ((uint32_t)(((uint32_t)(uint16_t)(hi) << 16) | (uint16_t)(lo)))
#define CONCAT31(hi, lo) \
    ((uint32_t)(((uint32_t)(hi) << 8) | (uint8_t)(lo)))
#define CONCAT44(hi, lo) \
    ((uint64_t)(((uint64_t)(uint32_t)(hi) << 32) | (uint32_t)(lo)))

/* SUB<from><size>(v, off): the <size> bytes at byte offset <off> of a
 * <from>-byte value. */
#define SUB42(v, off) ((uint16_t)((uint32_t)(v) >> ((off) * 8)))

/* ROUND: round a floating value to the nearest integer (Ghidra's ROUND
 * yields the same float type). */
#define ROUND(x) ((double)(int64_t)((x) < 0 ? (x) - 0.5 : (x) + 0.5))

/* ABS: absolute value (used on floats in the raw ports). */
#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

/* LOCK()/UNLOCK(): x86 atomic-sequence fences. No-ops in this build -
 * see the header note. Parenthesised so they're valid statements. */
#define LOCK()   ((void)0)
#define UNLOCK() ((void)0)

#endif /* GB_GHIDRA_INTRINSICS_H */
