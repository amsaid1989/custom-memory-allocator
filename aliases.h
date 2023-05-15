#ifndef ALIASES_H
#define ALIASES_H

#include <stdint.h>

#define u8 uint8_t
#define u16 uint16_t
#define u32 uint32_t
#define u64 uint64_t

#define i8 int8_t
#define i16 int16_t
#define i32 int32_t
#define i64 int64_t

#define f32 float
#define f64 double

#define INTERNAL static
#define PERSISTENT static

#ifdef __cplusplus
#define CLASS_MEMBER static
#endif // __cplusplus

#endif // !ALIASES_H
