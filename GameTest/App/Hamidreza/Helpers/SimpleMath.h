// A simple math library for the basics.
// This is absolutely a worthwhile investment for the project.

#ifndef _SIMPLEMATH_H_
#define _SIMPLEMATH_H_

#pragma once

#include <cmath>

#define M_PI	3.14159265358f  // Tasty pi
#define DEG2RAD 0.01745329251f  // multiply to convert from degrees to radians
#define RAD2DEG 57.2957795130f  // multiply to convert from radians to degrees 

class Vec2
{
public:

	float x;
	float y;

	Vec2():x(0),y(0){};
	Vec2(float ax, float ay): x(ax),  y(ay)	{};
	Vec2(float axy)		    : x(axy), y(axy){};
	
	Vec2 operator - () const { return Vec2(-this->x, -this->y); }
	Vec2 operator + (const float operand) const { return Vec2(this->x + operand, this->y + operand); }
	Vec2 operator - (const float operand) const { return Vec2(this->x - operand, this->y - operand); }
	Vec2 operator * (const float operand) const { return Vec2(this->x * operand, this->y * operand); }
	Vec2 operator / (const float operand) const { return Vec2(this->x / operand, this->y / operand); }

	Vec2 operator + (const Vec2 operand)  const { return Vec2(this->x + operand.x, this->y + operand.y); }
	Vec2 operator - (const Vec2 operand)  const { return Vec2(this->x - operand.x, this->y - operand.y); }
	Vec2 operator * (const Vec2 operand)  const { return Vec2(this->x * operand.x, this->y * operand.y); }
	Vec2 operator / (const Vec2 operand)  const { return Vec2(this->x / operand.x, this->y / operand.y); }

	Vec2 operator += (const float operand) { return Vec2(this->x += operand, this->y += operand); }
	Vec2 operator -= (const float operand) { return Vec2(this->x -= operand, this->y -= operand); }
	Vec2 operator *= (const float operand) { return Vec2(this->x *= operand, this->y *= operand); }
	Vec2 operator /= (const float operand) { return Vec2(this->x /= operand, this->y /= operand); }

	Vec2 operator += (const Vec2 operand) { return Vec2(this->x += operand.x, this->y += operand.y); }
	Vec2 operator -= (const Vec2 operand) { return Vec2(this->x -= operand.x, this->y -= operand.y); }
	Vec2 operator *= (const Vec2 operand) { return Vec2(this->x *= operand.x, this->y *= operand.y); }
	Vec2 operator /= (const Vec2 operand) { return Vec2(this->x /= operand.x, this->y /= operand.y); }

	float LengthSquared() const { return x * x + y * y; }
	float Length() const { return sqrtf(x * x + y * y); }
	
	float Distance(const Vec2 target) const { return (*this - target).Length(); }
	float DistanceSquared(const Vec2 target) const { return (*this - target).LengthSquared(); }

	float EulerAngle() const { return atan2f(this->y, this->x) * RAD2DEG; }
	Vec2 Normalized() const { return Vec2(x, y) / Length(); }

	Vec2 DirectionTo(const Vec2 target) const { return (target - *this).Normalized(); }
	
	Vec2 RotateAround(const float degrees, const Vec2 origin) const
	{
		float rads = degrees * DEG2RAD;
		Vec2 inputVec2 = *this;
		Vec2 vecToRotateAround = inputVec2 - origin;
		Vec2 vecToReturn;

		vecToReturn.x = cos(rads) * (inputVec2.x - vecToRotateAround.x) - sin(rads) * (inputVec2.y - vecToRotateAround.y) + vecToRotateAround.x;
		vecToReturn.y = sin(rads) * (inputVec2.x - vecToRotateAround.x) + cos(rads) * (inputVec2.y - vecToRotateAround.y) + vecToRotateAround.y;

		return vecToReturn;
	}

	Vec2 Rotate(const float degrees) const
	{
		float rads = degrees * DEG2RAD;
		Vec2 inputVec2 = *this;
		Vec2 vecToReturn;

		vecToReturn.x = cos(rads) * (inputVec2.x) - sin(rads) * (inputVec2.y);
		vecToReturn.y = sin(rads) * (inputVec2.x) + cos(rads) * (inputVec2.y);

		return vecToReturn;
	}

	// factor 0 returns a, 1 returns b.
	// Intentionally not clamped to allow for overshoots, if i get around to it or find a use for it.
	static Vec2 Interpolate(const Vec2 a, const Vec2 b, const float factor) 
	{
		return(a - (a - b) * factor);
	}

	float SimpleEllipseDistance(const Vec2 target, const float BToARatio) const // A is the major/horizontal axis of the ellipse, B is the minor/vertical one.
	{
		Vec2 vecToReturn = *this;
		Vec2 differenceVec = target - vecToReturn;
		return Vec2(differenceVec.x * BToARatio, differenceVec.y).Length();
	}

	static Vec2 RandomInUnitCircle() { float angle = (rand() % 360) * DEG2RAD; return Vec2(cos(angle), sin(angle)); }
};

class Color
{
public:

	float r;
	float g;
	float b;

	Color() :r(0), g(0), b(0) {};
	Color(float ar, float ag, float ab) : r(ar), g(ag), b(ab) {};
	Color(float argb) : r(argb), g(argb), b(argb) {};

	Color operator + (const float operand) const { return Color(this->r + operand, this->g + operand, this->b + operand); }
	Color operator - (const float operand) const { return Color(this->r - operand, this->g - operand, this->b - operand); }
	Color operator * (const float operand) const { return Color(this->r * operand, this->g * operand, this->b * operand); }
	Color operator / (const float operand) const { return Color(this->r / operand, this->g / operand, this->b / operand); }

	Color operator + (const Color operand) const { return Color(this->r + operand.r, this->g + operand.g, this->b + operand.b); }
	Color operator - (const Color operand) const { return Color(this->r - operand.r, this->g - operand.g, this->b - operand.b); }

	static Color Interpolate(const Color a, const Color b, const float factor) // Mandatory for fun visuals
	{
		return(a - (a - b) * factor);
	}
};

class Math 
{

public:

	static float Max(const float A, const float B) 
	{
		if (A >= B)
		{
			return A;
		}
		else
		{
			return B;
		}
	}

	static int Max(const int A, const int B)
	{
		if (A >= B)
		{
			return A;
		}
		else
		{
			return B;
		}
	}

	static float Interpolate(const float a, const float b, const float factor) 
	{
		return a - (a - b) * factor;
	}

	static float Clamp(const float value, const float min, const float max)
	{
		if (value <= min)
		{
			return min;
		}
		else if (value >= max)
		{
			return max;
		}
		else
		{
			return value;
		}
	}

	static int Clamp(const int value, const int min, const int max)
	{
		if (value <= min)
		{
			return min;
		}
		else if (value >= max)
		{
			return max;
		}
		else
		{
			return value;
		}
	}

};
#endif