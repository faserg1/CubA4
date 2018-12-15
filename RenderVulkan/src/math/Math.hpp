#ifndef RENDERVULKAN_MATH_HPP
#define RENDERVULKAN_MATH_HPP

#include "Matrix.hpp"
#include "Vector.hpp"
#include <cmath>

namespace CubA4
{
	namespace render
	{
		namespace math
		{
			constexpr double Pi = 3.14159265358979323846;

			/**
			\note: Не забываем про различие LeftHanded & RightHanded:
			https://www.youtube.com/watch?v=TGbMzoJqV7c
			*/
			class Math final
			{
			public:
				Math() = delete;

				static Matrix perspectiveLH(float fov, float aspect, float near, float far)
				{
					Matrix m;

					auto yScale = 1 / tan(fov / 2);
					auto xScale = yScale / aspect;

					m.data()[0] = xScale;
					m.data()[5] = yScale;

					m.data()[10] = far / (far - near);
					m.data()[11] = 1;

					m.data()[14] = -near * far / (far - near);

					return std::move(m);
				}
				static Matrix perspectiveRH(float fov, float aspect, float near, float far)
				{
					Matrix m;

					auto yScale = 1 / tan(fov / 2);
					auto xScale = yScale / aspect;

					m.data()[0] = xScale;
					m.data()[5] = yScale;

					m.data()[10] = far / (near - far);
					m.data()[11] = -1;

					m.data()[14] = near * far / (near - far);

					return std::move(m);
				}
				static Matrix lookAtLH(const Vector &eye, const Vector &at, const Vector &up)
				{
					Matrix m;

					auto zaxis = (at - eye).normalize();
					auto xaxis = cross(up, zaxis).normalize();
					auto yaxis = cross(zaxis, xaxis);

					m.data()[0] = xaxis.x;
					m.data()[1] = yaxis.x;
					m.data()[2] = zaxis.x;
					m.data()[3] = 0;

					m.data()[4] = xaxis.y;
					m.data()[5] = yaxis.y;
					m.data()[6] = zaxis.y;
					m.data()[7] = 0;

					m.data()[8] = xaxis.z;
					m.data()[9] = yaxis.z;
					m.data()[10] = zaxis.z;
					m.data()[11] = 0;

					m.data()[12] = -dot(xaxis, eye);
					m.data()[13] = -dot(yaxis, eye);
					m.data()[14] = -dot(zaxis, eye);
					m.data()[15] = 1;

					return std::move(m);
				}
				static Matrix lookAtRH(const Vector &eye, const Vector &at, const Vector &up)
				{
					Matrix m;

					auto zaxis = (eye - at).normalize();
					auto xaxis = cross(up, zaxis).normalize();
					auto yaxis = cross(zaxis, xaxis);

					m.data()[0] = xaxis.x;
					m.data()[1] = yaxis.x;
					m.data()[2] = zaxis.x;
					m.data()[3] = 0;

					m.data()[4] = xaxis.y;
					m.data()[5] = yaxis.y;
					m.data()[6] = zaxis.y;
					m.data()[7] = 0;

					m.data()[8] = xaxis.z;
					m.data()[9] = yaxis.z;
					m.data()[10] = zaxis.z;
					m.data()[11] = 0;

					m.data()[12] = dot(xaxis, eye);
					m.data()[13] = dot(yaxis, eye);
					m.data()[14] = dot(zaxis, eye);
					m.data()[15] = 1;

					return std::move(m);
				}
				static Matrix &rotateByZ(Matrix &m, float angle)
				{
					Matrix mul;
					mul.data()[0] = cos(angle);
					mul.data()[1] = sin(angle);
					mul.data()[4] = -sin(angle);
					mul.data()[5] = cos(angle);
					
					m = m * mul;
					
					return m;
				}
				static Matrix &rotateByY(Matrix &m, float angle)
				{
					Matrix mul;
					mul.data()[0] = cos(angle);
					mul.data()[2] = -sin(angle);
					mul.data()[8] = sin(angle);
					mul.data()[10] = cos(angle);

					m = m * mul;

					return m;
				}
				static Matrix &translate(Matrix &m, float x, float y, float z)
				{
					Matrix mul;

					mul.data()[12] = x;
					mul.data()[13] = y;
					mul.data()[14] = z;

					m = m * mul;

					return m;
				}
			protected:
			private:
			};
		}
	}
}

#endif // RENDERVULKAN_MATH_HPP
