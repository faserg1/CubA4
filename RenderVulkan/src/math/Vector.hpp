#ifndef RENDERVULKAN_VECTOR_HPP
#define RENDERVULKAN_VECTOR_HPP

#include <cmath>

namespace CubA4
{
	namespace render
	{
		namespace math
		{
			class Vector final
			{
			public:
				Vector() = default;
				Vector(float x, float y, float z) :
					x(x), y(y), z(z)
				{

				}
				float x;
				float y;
				float z;

				float length()
				{
					return sqrt(x*x + y*y + z*z);
				}

				Vector normalize()
				{
					return (*this) / length();
				}
				Vector operator / (const float value)
				{
					Vector t;
					t.x = x / value;
					t.y = y / value;
					t.z = z / value;
					return t;
				}

				Vector *operator /= (const float value)
				{
					x = x / value;
					y = y / value;
					z = z / value;
					return this;
				}

				friend Vector operator-(const Vector &one, const Vector &two)
				{
					return {one.x - two.x, one.y - two.y, one.z - two.z};
				}

				friend float dot(Vector one, Vector two)
				{
					return one.x * two.x + one.y * two.y + one.z * two.z;
				}

				friend Vector cross(Vector one, Vector two)
				{
					Vector t;
					t.x = one.y * two.z - one.z * two.y;
					t.y = one.z * two.x - one.x * two.z;
					t.z = one.x * two.y - one.y * two.x;
					return t;
				}
			};
		}
	}
}

#endif // RENDERVULKAN_VECTOR_HPP
