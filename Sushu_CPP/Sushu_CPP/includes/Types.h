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

	typedef struct
	{ 
		uint32_t x; 
		uint32_t y;
	} IVec2;

	typedef struct 
	{
		uint32_t x;
		uint32_t y;
		uint32_t z;
	} IVec3;

	typedef struct
	{
		float x;
		float y;
	} Vec2;

	typedef struct
	{
		float x;
		float y;
		float z;
	} Vec3;



}

#endif // !TYPES_H

