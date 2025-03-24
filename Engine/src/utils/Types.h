#pragma once
#include <iostream>
#include <cstdint>
#include <glm/glm.hpp>

#define GLM_VEC3_ZERO glm::vec3(0)
#define GLM_VEC3_ONE glm::vec3(1)


// these are for axis aligned
// in future i have to make my own vectors and stuff like unity does but now i'll stick to glm
inline const glm::vec3 VEC3_ZERO = glm::vec3(0);
inline const glm::vec3 VEC3_ONE = glm::vec3(1);
inline const glm::vec3 VEC3_UP = glm::vec3(0, 1, 0);
inline const glm::vec3 VEC3_DOWN = glm::vec3(0, -1, 0);
inline const glm::vec3 VEC3_LEFT = glm::vec3(-1, 0, 0);
inline const glm::vec3 VEC3_RIGHT = glm::vec3(1, 0, 0);
inline const glm::vec3 VEC3_FRONT = glm::vec3(0, 0, 1);
inline const glm::vec3 VEC3_BACK = glm::vec3(0, 0, -1);

// some default colors
inline const glm::vec4 WHITE = glm::vec4(1, 1, 1, 1);
inline const glm::vec4 BLACK = glm::vec4(0, 0, 0, 1);
inline const glm::vec4 RED	 = glm::vec4(1, 0, 0, 1);
inline const glm::vec4 GREEN = glm::vec4(0, 1, 0, 1);
inline const glm::vec4 BLUE  = glm::vec4(0, 0, 1, 1);

// Unsinged Ints
typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

// Ints
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

// Floats
typedef float  f32;
typedef double f64;