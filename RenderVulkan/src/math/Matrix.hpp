#ifndef RENDERVULKAN_MATRIX_HPP
#define RENDERVULKAN_MATRIX_HPP

#include <cstdint>
#include <cmath>
#include <string.h>

namespace CubA4
{
	namespace render
	{
		namespace math
		{
			class Matrix final
			{
			public:
				explicit Matrix()
				{
					data_ = new float[16];
					memset(data_, 0, sizeof(float) * 16);
					data_[0] = 1;
					data_[5] = 1;
					data_[10] = 1;
					data_[15] = 1;
				}
				Matrix(Matrix &&old)
				{
					data_ = old.data_;
					old.data_ = nullptr;
				}
				~Matrix()
				{
					delete [] data_;
				}

				float *data()
				{
					return data_;
				}
				const float *data() const
				{
					return data_;
				}
				Matrix * operator=(const Matrix &other)
				{
					memcpy(data_, other.data_, sizeof(float) * 16);
					return this;
				}
				friend Matrix operator*(const Matrix &one, const Matrix &two)
				{
					Matrix result;
					
					float *r = result.data_;
					const float *f = one.data_;
					const float *s = two.data_;

					r[0] = f[0] * s[0] + f[1] * s[4] + f[2] * s[8] + f[3] * s[12];
					r[1] = f[0] * s[1] + f[1] * s[5] + f[2] * s[9] + f[3] * s[13];
					r[2] = f[0] * s[2] + f[1] * s[6] + f[2] * s[10] + f[3] * s[14];
					r[3] = f[0] * s[3] + f[1] * s[7] + f[2] * s[11] + f[3] * s[15];


					r[4] = f[4] * s[0] + f[5] * s[4] + f[6] * s[8] + f[7] * s[12];
					r[5] = f[4] * s[1] + f[5] * s[5] + f[6] * s[9] + f[7] * s[13];
					r[6] = f[4] * s[2] + f[5] * s[6] + f[6] * s[10] + f[7] * s[14];
					r[7] = f[4] * s[3] + f[5] * s[7] + f[6] * s[11] + f[7] * s[15];


					r[8] = f[8] * s[0] + f[9] * s[4] + f[10] * s[8] + f[11] * s[12];
					r[9] = f[8] * s[1] + f[9] * s[5] + f[10] * s[9] + f[11] * s[13];
					r[10] = f[8] * s[2] + f[9] * s[6] + f[10] * s[10] + f[11] * s[14];
					r[11] = f[8] * s[3] + f[9] * s[7] + f[10] * s[11] + f[11] * s[15];


					r[12] = f[12] * s[0] + f[13] * s[4] + f[14] * s[8] + f[15] * s[12];
					r[13] = f[12] * s[1] + f[13] * s[5] + f[14] * s[9] + f[15] * s[13];
					r[14] = f[12] * s[2] + f[13] * s[6] + f[14] * s[10] + f[15] * s[14];
					r[15] = f[12] * s[3] + f[13] * s[7] + f[14] * s[11] + f[15] * s[15];

					return std::move(result);
				}
			protected:
				
			private:
				float *data_;
			};
		}
	}
}

#endif // RENDERVULKAN_MATRIX_HPP
