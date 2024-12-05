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
		int32_t x; 
		int32_t y;
	} IVec2;

	typedef struct 
	{
		int32_t x;
		int32_t y;
		int32_t z;
	} IVec3;

	typedef struct
	{
		int32_t x;
		int32_t y;
		int32_t z;
		int32_t w;
	} IVec4;

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

	typedef struct
	{
		float x;
		float y;
		float z;
		float w;
	} Vec4;



}

#endif // !TYPES_H

