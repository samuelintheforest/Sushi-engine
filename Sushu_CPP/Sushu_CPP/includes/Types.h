/*
Egy header fájl típusok definiálására
*/

#ifndef TYPES_H
#define TYPES_H

#include <cstdint>

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

	struct IVec2 
	{ 
		uint32_t x; 
		uint32_t y;
	};
	struct IVec3
	{
		uint32_t x;
		uint32_t y;
		uint32_t z;
	};
	struct Vec2
	{
		float x;
		float y;
	};

	struct Vec3
	{
		float x;
		float y;
		float z;
	};



}

#endif // !TYPES_H

