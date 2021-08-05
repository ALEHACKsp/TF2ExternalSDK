#pragma once
#include "../Vector/Vector.h"
#include <cmath>
#include <cfloat>
#include <algorithm>
#include <array>

#undef min
#undef max

#define PI 3.14159265358979323846
#define M_RADPI 57.295779513082
#define DEG2RAD(x) ((float)(x) * (float)((float)(PI) / 180.0f))
#define RAD2DEG(x) ((float)(x) * (float)(180.0f / (float)(PI)))

using matrix3x4_t = float[3][4];

class VMatrix
{
private:
	Vec3 m[4][4];

public:
	inline const matrix3x4_t &As3x4() const {
		return *((const matrix3x4_t *)this);
	}
};

#pragma warning (push)
#pragma warning (disable : 26451)
#pragma warning (disable : 4244)

namespace Math
{
	inline double __declspec (naked) __fastcall FastSqrt(double n)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}

	inline float NormalizeAngle(float ang)
	{
		return (!std::isfinite(ang) ? 0.0f : std::remainder(ang, 360.0f));
	}

	inline void SinCos(float radians, float *sine, float *cosine)
	{
		_asm
		{
			fld		DWORD PTR[radians]
			fsincos

			mov edx, DWORD PTR[cosine]
			mov eax, DWORD PTR[sine]

			fstp DWORD PTR[edx]
			fstp DWORD PTR[eax]
		}
	}

	inline void ClampAngles(Vec3 &v)
	{
		v.x = std::max(-89.0f, std::min(89.0f, NormalizeAngle(v.x)));
		v.y = NormalizeAngle(v.y);
		v.z = 0.0f;
	}

	inline void VectorAngles(const Vec3 &forward, Vec3 &angles)
	{
		float tmp, yaw, pitch;

		if (forward.y == 0 && forward.x == 0)
		{
			yaw = 0;

			if (forward.z > 0)
				pitch = 270;
			else
				pitch = 90;
		}

		else
		{
			yaw = RAD2DEG(atan2f(forward.y, forward.x));

			if (yaw < 0)
				yaw += 360;

			tmp = forward.Lenght2D();
			pitch = RAD2DEG(atan2f(-forward.z, tmp));

			if (pitch < 0)
				pitch += 360;
		}

		angles[0] = pitch;
		angles[1] = yaw;
		angles[2] = 0;
	}

	inline void AngleVectors(const Vec3 &angles, Vec3 *forward)
	{
		float sp, sy, cp, cy;

		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}
	}

	inline void AngleVectors(const Vec3 &angles, Vec3 *forward, Vec3 *right, Vec3 *up)
	{
		float sr, sp, sy, cr, cp, cy;
		SinCos(DEG2RAD(angles.x), &sp, &cp);
		SinCos(DEG2RAD(angles.y), &sy, &cy);
		SinCos(DEG2RAD(angles.z), &sr, &cr);

		if (forward)
		{
			forward->x = cp * cy;
			forward->y = cp * sy;
			forward->z = -sp;
		}

		if (right)
		{
			right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
			right->y = (-1 * sr * sp * sy + -1 * cr * cy);
			right->z = -1 * sr * cp;
		}

		if (up)
		{
			up->x = (cr * sp * cy + -sr * -sy);
			up->y = (cr * sp * sy + -sr * cy);
			up->z = cr * cp;
		}
	}

	inline Vec3 CalcAngle(const Vec3 &source, const Vec3 &destination, bool clamp = true)
	{
		Vec3 angles = Vec3(0.0f, 0.0f, 0.0f);
		Vec3 delta = (source - destination);
		float fHyp = FastSqrt((delta.x * delta.x) + (delta.y * delta.y));

		angles.x = (atanf(delta.z / fHyp) * M_RADPI);
		angles.y = (atanf(delta.y / delta.x) * M_RADPI);
		angles.z = 0.0f;

		if (delta.x >= 0.0f)
			angles.y += 180.0f;

		if (clamp)
			ClampAngles(angles);

		return angles;
	}

	inline float CalcFov(const Vec3 &src, const Vec3 &dst)
	{
		Vec3 v_src = Vec3();
		AngleVectors(src, &v_src);

		Vec3 v_dst = Vec3();
		AngleVectors(dst, &v_dst);

		float result = RAD2DEG(acos(v_dst.Dot(v_src) / v_dst.LenghtSqr()));

		if (!isfinite(result) || isinf(result) || isnan(result))
			result = 0.0f;

		return result;
	}

	inline void VectorTransform(const Vec3 &input, const matrix3x4_t &matrix, Vec3 &output)
	{
		for (auto i = 0; i < 3; i++)
			output[i] = input.Dot((Vec3 &)matrix[i]) + matrix[i][3];
	}

	inline float RemapValClamped(float val, float A, float B, float C, float D)
	{
		if (A == B)
			return val >= B ? D : C;

		float cVal = (val - A) / (B - A);
		cVal = std::clamp(cVal, 0.0f, 1.0f);

		return C + (D - C) * cVal;
	}

	inline void MatrixSetColumn(const Vec3 &in, int column, matrix3x4_t &out)
	{
		out[0][column] = in.x;
		out[1][column] = in.y;
		out[2][column] = in.z;
	}

	inline void AngleMatrix(const Vec3 &angles, matrix3x4_t &matrix)
	{
		float sr, sp, sy, cr, cp, cy;

		SinCos(DEG2RAD(angles[1]), &sy, &cy);
		SinCos(DEG2RAD(angles[0]), &sp, &cp);
		SinCos(DEG2RAD(angles[2]), &sr, &cr);

		matrix[0][0] = cp * cy;
		matrix[1][0] = cp * sy;
		matrix[2][0] = -sp;

		float crcy = cr * cy;
		float crsy = cr * sy;
		float srcy = sr * cy;
		float srsy = sr * sy;

		matrix[0][1] = sp * srcy - crsy;
		matrix[1][1] = sp * srsy + crcy;
		matrix[2][1] = sr * cp;

		matrix[0][2] = (sp * crcy + srsy);
		matrix[1][2] = (sp * crsy - srcy);
		matrix[2][2] = cr * cp;

		matrix[0][3] = 0.0f;
		matrix[1][3] = 0.0f;
		matrix[2][3] = 0.0f;
	}

	inline void MatrixAngles(const matrix3x4_t &matrix, float *angles)
	{
		float forward[3] = {};
		float left[3] = {};
		float up[3] = {};

		forward[0] = matrix[0][0];
		forward[1] = matrix[1][0];
		forward[2] = matrix[2][0];

		left[0] = matrix[0][1];
		left[1] = matrix[1][1];
		left[2] = matrix[2][1];

		up[2] = matrix[2][2];

		const float xyDist = sqrtf(forward[0] * forward[0] + forward[1] * forward[1]);

		if (xyDist > 0.001f)
		{
			angles[1] = RAD2DEG(atan2f(forward[1], forward[0]));
			angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));
			angles[2] = RAD2DEG(atan2f(left[2], up[2]));
		}

		else
		{
			angles[1] = RAD2DEG(atan2f(-left[0], left[1]));
			angles[0] = RAD2DEG(atan2f(-forward[2], xyDist));
			angles[2] = 0.0f;
		}
	}
}

#pragma warning (pop)