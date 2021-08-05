#pragma once
#include <math.h>

class Vec3
{
public:
	float x, y, z;

public:
	Vec3(void)
	{
		x = y = z = 0.0f;
	}

	void Zero()
	{
		x = y = z = 0.f;
	}

	Vec3(float X, float Y, float Z)
	{
		x = X; y = Y; z = Z;
	}

	Vec3(float *v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vec3(const float *v)
	{
		x = v[0]; y = v[1]; z = v[2];
	}

	Vec3(const Vec3 &v)
	{
		x = v.x; y = v.y; z = v.z;
	}

	Vec3 &operator=(const Vec3 &v)
	{
		x = v.x; y = v.y; z = v.z; return *this;
	}

	float &operator[](int i)
	{
		return ((float *)this)[i];
	}

	float operator[](int i) const
	{
		return ((float *)this)[i];
	}

	Vec3 &operator+=(const Vec3 &v)
	{
		x += v.x; y += v.y; z += v.z; return *this;
	}

	Vec3 &operator-=(const Vec3 &v)
	{
		x -= v.x; y -= v.y; z -= v.z; return *this;
	}

	Vec3 &operator*=(const Vec3 &v)
	{
		x *= v.x; y *= v.y; z *= v.z; return *this;
	}

	Vec3 &operator/=(const Vec3 &v)
	{
		x /= v.x; y /= v.y; z /= v.z; return *this;
	}

	Vec3 &operator+=(float v)
	{
		x += v; y += v; z += v; return *this;
	}

	Vec3 &operator-=(float v)
	{
		x -= v; y -= v; z -= v; return *this;
	}

	Vec3 &operator*=(float v)
	{
		x *= v; y *= v; z *= v; return *this;
	}

	Vec3 &operator/=(float v)
	{
		x /= v; y /= v; z /= v; return *this;
	}

	Vec3 operator+(const Vec3 &v) const
	{
		return Vec3(x + v.x, y + v.y, z + v.z);
	}

	Vec3 operator-(const Vec3 &v) const
	{
		return Vec3(x - v.x, y - v.y, z - v.z);
	}

	Vec3 operator*(const Vec3 &v) const
	{
		return Vec3(x * v.x, y * v.y, z * v.z);
	}

	Vec3 operator/(const Vec3 &v) const
	{
		return Vec3(x / v.x, y / v.y, z / v.z);
	}

	Vec3 operator+(float v) const
	{
		return Vec3(x + v, y + v, z + v);
	}

	Vec3 operator-(float v) const
	{
		return Vec3(x - v, y - v, z - v);
	}

	Vec3 operator*(float v) const
	{
		return Vec3(x * v, y * v, z * v);
	}

	Vec3 operator/(float v) const
	{
		return Vec3(x / v, y / v, z / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
	{
		x = X; y = Y; z = Z;
	}

	float Lenght(void) const
	{
		return sqrtf(x * x + y * y + z * z);
	}

	float LenghtSqr(void) const
	{
		return (x * x + y * y + z * z);
	}

	float Normalize()
	{
		float fl_lenght = Lenght();
		float fl_lenght_normal = 1.f / (1.192092896e-07F + fl_lenght);

		x = x * fl_lenght_normal;
		y = y * fl_lenght_normal;
		z = z * fl_lenght_normal;

		return fl_lenght;
	}

	float NormalizeInPlace()
	{
		return Normalize();
	}

	float Lenght2D(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float Lenght2DSqr(void) const
	{
		return (x * x + y * y);
	}

	float DistTo(const Vec3 &v) const
	{
		return (*this - v).Lenght();
	}

	float DistToSqr(const Vec3 &v) const
	{
		return (*this - v).LenghtSqr();
	}

	float Dot(const Vec3 &v) const
	{
		return (x * v.x + y * v.y + z * v.z);
	}

	Vec3 Cross(const Vec3 &v) const
	{
		return Vec3(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
			y > -0.01f && y < 0.01f &&
			z > -0.01f && z < 0.01f);
	}

	Vec3 Scale(float fl) {
		return Vec3(x * fl, y * fl, z * fl);
	}

	void Init(float ix, float iy, float iz)
	{
		x = ix; y = iy; z = iz;
	}
};

class Vec2
{
public:
	float x, y;

public:
	Vec2(void)
	{
		x = y = 0.0f;
	}

	Vec2(float X, float Y)
	{
		x = X; y = Y;
	}

	Vec2(float *v)
	{
		x = v[0]; y = v[1];
	}

	Vec2(const float *v)
	{
		x = v[0]; y = v[1];
	}

	Vec2(const Vec2 &v)
	{
		x = v.x; y = v.y;
	}

	Vec2 &operator=(const Vec2 &v)
	{
		x = v.x; y = v.y; return *this;
	}

	float &operator[](int i)
	{
		return ((float *)this)[i];
	}

	float operator[](int i) const
	{
		return ((float *)this)[i];
	}

	Vec2 &operator+=(const Vec2 &v)
	{
		x += v.x; y += v.y; return *this;
	}

	Vec2 &operator-=(const Vec2 &v)
	{
		x -= v.x; y -= v.y; return *this;
	}

	Vec2 &operator*=(const Vec2 &v)
	{
		x *= v.x; y *= v.y; return *this;
	}

	Vec2 &operator/=(const Vec2 &v)
	{
		x /= v.x; y /= v.y; return *this;
	}

	Vec2 &operator+=(float v)
	{
		x += v; y += v; return *this;
	}

	Vec2 &operator-=(float v)
	{
		x -= v; y -= v; return *this;
	}

	Vec2 &operator*=(float v)
	{
		x *= v; y *= v; return *this;
	}

	Vec2 &operator/=(float v)
	{
		x /= v; y /= v; return *this;
	}

	Vec2 operator+(const Vec2 &v) const
	{
		return Vec2(x + v.x, y + v.y);
	}

	Vec2 operator-(const Vec2 &v) const
	{
		return Vec2(x - v.x, y - v.y);
	}

	Vec2 operator*(const Vec2 &v) const
	{
		return Vec2(x * v.x, y * v.y);
	}

	Vec2 operator/(const Vec2 &v) const
	{
		return Vec2(x / v.x, y / v.y);
	}

	Vec2 operator+(float v) const
	{
		return Vec2(x + v, y + v);
	}

	Vec2 operator-(float v) const
	{
		return Vec2(x - v, y - v);
	}

	Vec2 operator*(float v) const
	{
		return Vec2(x * v, y * v);
	}

	Vec2 operator/(float v) const
	{
		return Vec2(x / v, y / v);
	}

	void Set(float X = 0.0f, float Y = 0.0f)
	{
		x = X; y = Y;
	}

	float Lenght(void) const
	{
		return sqrtf(x * x + y * y);
	}

	float LenghtSqr(void) const
	{
		return (x * x + y * y);
	}

	float DistTo(const Vec2 &v) const
	{
		return (*this - v).Lenght();
	}

	float DistToSqr(const Vec2 &v) const
	{
		return (*this - v).LenghtSqr();
	}

	float Dot(const Vec2 &v) const
	{
		return (x * v.x + y * v.y);
	}

	bool IsZero(void) const
	{
		return (x > -0.01f && x < 0.01f &&
			y > -0.01f && y < 0.01f);
	}
};