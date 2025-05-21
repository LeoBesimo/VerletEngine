#pragma once

#pragma once

#include <cmath>
#include <ostream>

namespace Math
{
	struct Vector2
	{
		float x;
		float y;

		Vector2(float x = 0, float y = 0) :
			x(x), y(y)
		{
		}

		Vector2 operator-(void) const
		{
			return Vector2(-x, -y);
		}

		Vector2 operator-(const Vector2& a) const
		{
			return Vector2(x - a.x, y - a.y);
		}

		Vector2 operator-(float a) const
		{
			return Vector2(x - a, y - a);
		}

		Vector2 operator+(void) const
		{
			return Vector2(+x, +y);
		}

		Vector2 operator+(const Vector2& a) const
		{
			return Vector2(x + a.x, y + a.y);
		}

		Vector2 operator+(float a) const
		{
			return Vector2(x + a, y + a);
		}

		Vector2 operator*(const Vector2& a) const
		{
			return Vector2(x * a.x, y * a.y);
		}

		Vector2 operator*(float a) const
		{
			return Vector2(x * a, y * a);
		}

		Vector2 operator/(const Vector2& a) const
		{
			return Vector2(x / a.x, y / a.y);
		}

		Vector2 operator/(float a) const
		{
			return Vector2(x / a, y / a);
		}

		void operator-=(const Vector2& a)
		{
			x -= a.x;
			y -= a.y;
		}

		void operator+=(const Vector2& a)
		{
			x += a.x;
			y += a.y;
		}

		void operator*=(const float a)
		{
			x *= a;
			y *= a;
		}

		void operator*=(const Vector2& a)
		{
			x *= a.x;
			y *= a.y;
		}

		void operator/=(const float a)
		{
			x /= a;
			y /= a;
		}

		void operator/=(const Vector2& a)
		{
			x /= a.x;
			y /= a.y;
		}

		float lenSqr(void) const  //returns length squared of the vector
		{
			return (x * x) + (y * y);
		}

		float len(void) const  //returns lenght of vector
		{
			return std::sqrt(x * x + y * y);
		}

		Vector2 normalize(void)  // normalizes the vector
		{
			float l = len();

			if (l == 0) return Vector2(0, 0);

			float invLen = 1.0f / l;

			x *= invLen;
			y *= invLen;

			return *this;
		}

		void limit(float length)
		{
			float lsqr = length * length;
			if (lenSqr() > lsqr)
			{
				normalize();
				x *= length;
				y *= length;
			}
		}

		float dot(const Vector2& a)
		{
			return x * a.x + y * a.y;
		}

		float cross(const Vector2& a)
		{
			return x * a.y - y * a.x;
		}
	};
}
