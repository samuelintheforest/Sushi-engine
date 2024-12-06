/*
Egy header fájl típusok definiálására
*/

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace sushi
{

	// Unsigned integers
	typedef uint8_t u8;
	typedef uint16_t u16;
	typedef uint32_t u32;
	typedef uint64_t u64;

	// Signed integers
	typedef int16_t s16;
	typedef int16_t s16;
	typedef int32_t s32;
	typedef int64_t s64;

	// float types
	typedef float f32;
	typedef double f64;

	// the boolean type
	typedef bool binary;

	typedef	glm::ivec2 IVec2;
	typedef	glm::ivec3 IVec3;
	typedef	glm::ivec4 IVec4;

	typedef glm::vec2 Vec2;
	typedef glm::vec3 Vec3;
	typedef glm::vec4 Vec4;

	typedef glm::mat2 Mat2;
	typedef glm::mat3 Mat3;
	typedef glm::mat4 Mat4;

	/* Description to get for FilledRectColorFix */
	typedef struct
	{
		int32_t x;
		int32_t y;
		int32_t z;
		int32_t w;
		int32_t h;
		int32_t r;
		int32_t g;
		int32_t b;
		int32_t a;
	} FilledRectColorFixDesc;

}

#endif // !TYPES_H

