#ifndef KRYOGENIC_COMMON_TYPES_HPP
#define KRYOGENIC_COMMON_TYPES_HPP

using i8  = signed char;
using i16 = signed short;
using i32 = signed int;
using i64 = signed long long;

using u8  = unsigned char;
using u16 = unsigned short;
using u32 = unsigned int;
using u64 = unsigned long long;

using f32 = float;
using f64 = double;

using b8  = u8;
using b32 = u32;

using byte  = u8;
using isize = i64;
using usize = u64;

static_assert(1 == sizeof(i8), "i8 is not 1 byte");
static_assert(2 == sizeof(i16), "i16 is not 2 bytes");
static_assert(4 == sizeof(i32), "i32 is not 4 bytes");
static_assert(8 == sizeof(i64), "i64 is not 8 bytes");
static_assert(1 == sizeof(u8), "u8 is not 1 byte");
static_assert(2 == sizeof(u16), "u16 is not 2 bytes");
static_assert(4 == sizeof(u32), "u32 is not 4 bytes");
static_assert(8 == sizeof(u64), "u64 is not 8 bytes");
static_assert(4 == sizeof(f32), "f32 is not 4 bytes");
static_assert(8 == sizeof(f64), "f64 is not 8 bytes");
static_assert(1 == sizeof(b8), "b8 is not 1 byte");
static_assert(4 == sizeof(b32), "b32 is not 4 bytes");
#endif //KRYOGENIC_COMMON_TYPES_HPP
