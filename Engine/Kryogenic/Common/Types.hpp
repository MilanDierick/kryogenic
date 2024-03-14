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

using string  = std::string;
using stringv = std::string_view;
using cstring = char const* const;

#include <glm/glm.hpp>

using vec1  = glm::vec<1, f32>;
using vec2  = glm::vec<2, f32>;
using vec3  = glm::vec<3, f32>;
using vec4  = glm::vec<4, f32>;
using ivec1 = glm::vec<1, i32>;
using ivec2 = glm::vec<2, i32>;
using ivec3 = glm::vec<3, i32>;
using ivec4 = glm::vec<4, i32>;
using uvec1 = glm::vec<1, u32>;
using uvec2 = glm::vec<2, u32>;
using uvec3 = glm::vec<3, u32>;
using uvec4 = glm::vec<4, u32>;
using fvec1 = glm::vec<1, f32>;
using fvec2 = glm::vec<2, f32>;
using fvec3 = glm::vec<3, f32>;
using fvec4 = glm::vec<4, f32>;
using dvec1 = glm::vec<1, f64>;
using dvec2 = glm::vec<2, f64>;
using dvec3 = glm::vec<3, f64>;
using dvec4 = glm::vec<4, f64>;

#endif //KRYOGENIC_COMMON_TYPES_HPP
