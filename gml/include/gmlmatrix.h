#pragma once
#include <gmlvector.h>
#include <gmlutility.h>
#include <gmlangle.h>
#include <cassert>

namespace gml
{
	class mat22;
	class mat33;
	class mat44;
}

namespace gml
{
	class mat22
	{
	public:
		inline static const mat22& I()
		{
			static mat22 i(
				1.0f, 0.0f,
				0.0f, 1.0f
				);
			return i;
		}

		inline static mat22 rotate(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);
			return mat22(
				cosr, -sinr,
				sinr, cosr);
		}

		inline static mat22 scale(float scaler)
		{
			return mat22(
				scaler, 0,
				0, scaler);
		}

		inline static mat22 scale(float sx, float sy)
		{
			return mat22(
				sx, 0,
				0, sy);
		}

		inline static mat22 flip_x()
		{
			return mat22(
				-1, 0,
				0, 1);
		}

		inline static mat22 flip_y()
		{
			return mat22(
				1, 0,
				0, -1);
		}

	public:
		union
		{
			float m[2][2] = { 0,0,0,0 };
			struct { float _00, _01, _10, _11; };
			struct { vec2 row[2]; };
		};

		constexpr mat22() { }

		constexpr mat22(float _m00, float _m01, float _m10, float _m11)
			: _00(_m00), _01(_m01)
			, _10(_m10), _11(_m11) { }

		constexpr mat22(const vec2& row1, const vec2& row2)
			: _00(row1.x), _01(row1.y)
			, _10(row2.x), _11(row2.y) {}

		constexpr mat22(const mat22& m)
			: _00(m._00), _01(m._01)
			, _10(m._10), _11(m._11) { }

		constexpr explicit mat22(const mat33& m33);

		constexpr explicit mat22(const mat44& m44);

		inline mat22& operator=(const mat22& rhs)
		{
			if (&rhs != this)
			{
				for (int i = 0; i < 4; i++)
				{
					(*this)[i] = rhs[i];
				}
			}
			return *this;
		}

		inline mat22 operator* (float scaler) const
		{
			mat22 result(*this);
			result *= scaler;
			return result;
		}

		inline mat22 operator* (const mat22& rhs) const
		{
			mat22 result(*this);
			result *= rhs;
			return result;
		}

		inline vec2 operator* (const vec2& rhs) const
		{
			vec2 result;
			for (int i = 0; i < 2; i++)
			{
				result[i] = dot(row[i], rhs);
			}
			return result;
		}

		inline mat22& operator*= (float scaler)
		{
			for (int i = 0; i < 4; i++)
			{
				(*this)[i] *= scaler;
			}
			return *this;
		}

		inline mat22& operator*=(const mat22& rhs)
		{
			mat22 copy(*this);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 2; j++)
				{
					m[i][j] = dot(copy.row[i], rhs.column(j));
				}
			}
			return *this;
		}

		inline bool operator== (const mat22& rhs) const
		{
			if (&rhs != this)
			{
				for (int i = 0; i < 4; i++)
				{
					if ((*this)[i] != rhs[i])
						return false;
				}
			}
			return true;
		}

		inline bool operator!= (const mat22& rhs) const { return !(*this == rhs); }

		inline float& operator[] (int index)
		{
			return const_cast<float&>(const_cast<const mat22*>(this)->operator[](index));
		}

		inline const float& operator[] (int index) const
		{
			assert(index >= 0 && index < 4);
			return *(&(m[0][0]) + index);
		}

		inline vec2 column(int index) const
		{
			assert(index >= 0 && index < 2);
			return vec2(m[0][index], m[1][index]);
		}

		inline void set_column(int index, vec2 v)
		{
			assert(index >= 0 && index < 2);
			for (int i = 0; i < 2; i++)
			{
				m[i][index] = v[i];
			}
		}

		inline void identity() { *this = I(); }

		inline void transpose() { swap(this->_10, this->_01); }

		inline mat22 transposed() const
		{
			mat22 result(*this);
			result.transpose();
			return result;
		}

		inline bool can_invert() const
		{
			if (is_orthogonal())
			{
				return true;
			}
			else
			{
				float det = determinant();
				return !fequal(det, 0.0f);
			}
		}

		inline void inverse()
		{
			if (is_orthogonal())
			{
				transpose();
			}
			else
			{
				float det = determinant();
				if (!fequal(det, 0.0f))
				{
					//calc adjoint matrix 
					swap(this->m[0][0], this->m[1][1]);
					this->m[0][1] = -this->m[0][1];
					this->m[1][0] = -this->m[1][0];

					*this *= 1.0f / det;
				}
				else
				{
					//TODO:
					// can not invert here,
					// what should i do when this occur ?
				}
			}
		}

		inline mat22 inversed() const
		{
			mat22 result(*this);
			result.inverse();
			return result;
		}

		inline bool is_orthogonal() const
		{
			for (int i = 0; i < 2; i++)
			{
				if (!fequal(row[i].length_sqr(), 1.0f))
				{
					return false;
				}

				for (int j = i + 1; j < 2; j++)
				{
					if (!fequal(dot(row[i], row[j]), 0.0f))
						return false;
				}
			}
			return true;
		}

		inline float determinant() const
		{
			return gml_impl::determinant(
				_00, _01,
				_10, _11);
		}
	};

	inline mat22 operator* (float scaler, const mat22& rhs)
	{
		return rhs * scaler;
	}

	inline vec2 operator* (const vec2& lhs, const mat22& rhs)
	{
		vec2 result;
		for (int i = 0; i < 2; i++)
		{
			result[i] = dot(lhs, rhs.column(i));
		}
		return result;
	}
}

namespace gml
{
	class mat32
	{
	public:
		inline static const mat32& I()
		{
			static mat32 i(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f
				);
			return i;
		}

		inline static mat32 rotate(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);
			return mat32(
				cosr, -sinr, 0,
				sinr, cosr, 0);
		}

		inline static mat32 scale(float scaler)
		{
			return mat32(
				scaler, 0, 0,
				0, scaler, 0);
		}

		inline static mat32 scale(float sx, float sy)
		{
			return mat32(
				sx, 0, 0,
				0, sy, 0);
		}

		inline static mat32 translate(float x, float y)
		{
			return mat32(
				1, 0, x,
				0, 1, y);
		}

		inline static mat32 flip_x()
		{
			return mat32(
				-1, 0, 0,
				0, 1, 0);
		}

		inline static mat32 flip_y()
		{
			return mat32(
				1, 0, 0,
				0, -1, 0);
		}

		inline static mat32 inv_trs(const vec2& translate, const radian& rotation, const vec2& scale)
		{
			/*
			sx,0,0 * +cos,sin,0 * 1,0,-tx
			0,sy,0   -sin,cos,0   0,1,-ty

			=   sx,0,0 * +cos,sin,-cos*tx-sin*ty
			0,sy,0	 -sin,cos,+sin*tx-cos*ty

			=   +sx*cos, sx*sin, -sx*(cos*tx+sin*ty)
			-sy*sin, sy*cos, +sy*(sin*tx-cos*ty)
			*/
			float cosr = cos(rotation);
			float sinr = sin(rotation);

			return mat32(
				+scale.x*cosr, scale.x*sinr, -scale.x*(cosr*translate.x - sinr*translate.y),
				-scale.y*sinr, scale.y*cosr, +scale.y*(sinr*translate.x - cosr*translate.y)
				);
		}

		inline static mat32 trs(const vec2& translate, const radian& rotation, const vec2& scale)
		{
			/*
			1,0,tx * cos,-sin,0 * sx,0,0
			0,1,ty   sin, cos,0   0,sy,0

			=   cos,-sin,tx * sx,0,0
			sin,+cos,ty   0,sy,0

			=   cos*sx,-sin*sy, tx
			sin*sx, cos*sy, ty
			*/
			float cosr = cos(rotation);
			float sinr = sin(rotation);

			return mat32(
				cosr*scale.x, -sinr*scale.y, translate.x,
				sinr*scale.x, +cosr*scale.y, translate.y
				);
		}

		inline static mat32 trsp(const vec2& translate, const radian& rotation, const vec2& scale, const vec2& pivot)
		{
			/*
			1,0,tx * cos,-sin,0 * sx,0,0 * 1,0,-px
			0,1,ty   sin, cos,0   0,sy,0   0,1,-py

			= cos,-sin,tx * sx,0,-sx*px
			sin,+cos,ty   0,sy,-sy*py

			= cos*sx,-sin*sy, -cos*sx*px+sin*sy*px + tx
			sin*sx, cos*sy, -sin*sx*px-cos*sy*py + ty
			*/
			float cosr = cos(rotation);
			float sinr = sin(rotation);
			float spx = -scale.x*pivot.x;
			float spy = -scale.y*pivot.y;

			return mat32(
				cosr*scale.x, -sinr*scale.y, cosr*spx - sinr*spy + translate.x,
				sinr*scale.x, +cosr*scale.y, sinr*spx + cosr*spy + translate.y
				);
		}

		inline static mat32 trps(const vec2& translate, const radian& rotation, const vec2& pivot, const vec2& scale)
		{
			/*
			1,0,tx * cos,-sin,0 * 1,0,-px * sx,0,0
			0,1,ty   sin, cos,0   0,1,-px   0,sy,0

			= cos,-sin,ty * sx,0,-px
			sin, cos,ty   0,sy,-px

			= cos*sx,-sin*sy, -cos*px+sin*px + tx
			sin*sx,+cos*sy, -sin*px-cos*py + ty
			*/
			float cosr = cos(rotation);
			float sinr = sin(rotation);

			return mat32(
				cosr*scale.x, -sinr*scale.y, -cosr*pivot.x + sinr*pivot.y + translate.x,
				sinr*scale.x, +cosr*scale.y, -sinr*pivot.x - cosr*pivot.y + translate.y
				);
		}

	public:
		union
		{
			// special for GPU constant buffer layout.
			float m[2][4] = { 0,0,0,0,0,0,0,0 };
			struct { float _00, _01, _02, _dummy_0, _10, _11, _12, _dummy_1; };
			struct { vec3 r; float _dummy_2; } rows[2];
		};

		constexpr mat32() { }

		constexpr mat32(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12)
			: _00(_m00), _01(_m01), _02(_m02)
			, _10(_m10), _11(_m11), _12(_m12) { }

		constexpr mat32(const vec3& row1, const vec3& row2)
			: _00(row1.x), _01(row1.y), _02(row1.z)
			, _10(row2.x), _11(row2.y), _12(row2.z) { }

		constexpr mat32(const mat32& m)
			: _00(m._00), _01(m._01), _02(m._02)
			, _10(m._10), _11(m._11), _12(m._12) { }

		constexpr explicit mat32(const mat22& m)
			: _00(m._00), _01(m._01)
			, _10(m._10), _11(m._11) { }

		inline mat32& operator=(const mat32& rhs)
		{
			if (&rhs != this)
			{
				row(0) = rhs.row(0);
				row(1) = rhs.row(1);
			}
			return *this;
		}

		inline mat32 operator* (const mat32& rhs) const
		{
			mat32 result(*this);
			result *= rhs;
			return result;
		}

		inline mat32& operator*=(const mat32& rhs)
		{
			mat32 copy(*this);
			for (int i = 0; i < 2; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m[i][j] = dot(copy.rows[i].r, vec3(rhs.column(j), ((j == 2) ? 1.0f : 0.0f)));
				}
			}
			return *this;
		}

		inline bool operator== (const mat32& rhs) const
		{
			if (&rhs != this)
			{
				rows[0].r == rhs.rows[0].r;
				rows[1].r == rhs.rows[1].r;
			}
			return true;
		}

		inline bool operator!= (const mat32& rhs) const { return !(*this == rhs); }

		inline float& operator[] (unsigned int index)
		{
			return const_cast<float&>(const_cast<const mat32*>(this)->operator[](index));
		}

		inline const float& operator[] (unsigned int index) const
		{
			assert(index >= 0 && index < 6);
			if (index > 2) index++;
			return *(&(m[0][0]) + index);
		}

		inline vec3& row(unsigned int index)
		{
			return const_cast<vec3&>(const_cast<const mat32*>(this)->row(index));
		}

		inline const vec3& row(unsigned int index) const
		{
			assert(index >= 0 && index < 2);
			return rows[index].r;
		}

		inline vec2 column(unsigned int index) const
		{
			assert(index >= 0 && index < 3);
			return vec2(m[0][index], m[1][index]);
		}

		inline void set_column(unsigned int index, vec2 v)
		{
			assert(index >= 0 && index < 2);
			for (int i = 0; i < 2; i++)
			{
				m[i][index] = v[i];
			}
		}

		inline void identity() { *this = I(); }
	};


	//matrix32
	inline vec2 transform_vector(const mat32& lhs, const vec2& rhs)
	{
		vec2 result;
		vec3 rhs3(rhs, 0);
		for (int i = 0; i < 2; i++)
		{
			result[i] = dot(lhs.rows[i].r, rhs3);
		}
		return result;
	}

	inline vec2 transform_point(const mat32& lhs, const vec2& rhs)
	{
		vec2 result;
		vec3 rhs3(rhs, 1);
		for (int i = 0; i < 2; i++)
		{
			result[i] = dot(lhs.rows[i].r, rhs3);
		}
		return result;
	}

}

namespace gml
{

	class mat33
	{
	public:
		inline static const mat33& I()
		{
			static mat33 i(
				1.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 1.0f
				);
			return i;
		}

		inline static mat33 rotate_x(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);

			return mat33(
				1, 0, 0,
				0, cosr, -sinr,
				0, sinr, cosr
				);
		}

		inline static mat33 rotate_y(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);

			return mat33(
				cosr, 0, -sinr,
				0, 1, 0,
				sinr, 0, cosr
				);
		}

		inline static mat33 rotate_z(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);

			return mat33(
				cosr, -sinr, 0,
				sinr, cosr, 0,
				0, 0, 1
				);
		}

		inline static mat33 scale(float scaler)
		{
			return mat33(
				scaler, 0, 0,
				0, scaler, 0,
				0, 0, scaler
				);
		}

		inline static mat33 scale(float sx, float sy, float sz)
		{
			return mat33(
				sx, 0, 0,
				0, sy, 0,
				0, 0, sz
				);
		}

		inline static mat33 flip_x()
		{
			return mat33(
				-1, 0, 0,
				0, 1, 0,
				0, 0, 1
				);
		}

		inline static mat33 flip_y()
		{
			return mat33(
				1, 0, 0,
				0, -1, 0,
				0, 0, 1
				);
		}

		inline static mat33 flip_z()
		{
			return mat33(
				1, 0, 0,
				0, 1, 0,
				0, 0, -1
				);
		}

	public:
		union
		{
			float m[3][3] = { 0,0,0,0,0,0,0,0,0 };
			struct { float _00, _01, _02, _10, _11, _12, _20, _21, _22; };
			struct { vec3 row[3]; };
		};

		constexpr mat33() { }

		constexpr mat33(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12, float _m20, float _m21, float _m22)
			: _00(_m00), _01(_m01), _02(_m02)
			, _10(_m10), _11(_m11), _12(_m12)
			, _20(_m20), _21(_m21), _22(_m22) { }

		constexpr mat33(const vec3& row1, const vec3& row2, const vec3& row3)
			: _00(row1.x), _01(row1.y), _02(row1.z)
			, _10(row2.x), _11(row2.y), _12(row2.z)
			, _20(row3.x), _21(row3.y), _22(row3.z) { }

		constexpr mat33(const mat33& m)
			: _00(m._00), _01(m._01), _02(m._02)
			, _10(m._10), _11(m._11), _12(m._12)
			, _20(m._20), _21(m._21), _22(m._22) { }

		constexpr explicit mat33(const mat22& m)
			: _00(m._00), _01(m._01)
			, _10(m._10), _11(m._11) { }

		constexpr explicit mat33(const mat44& m);

		inline mat33& operator=(const mat33& rhs)
		{
			if (&rhs != this)
			{
				for (int i = 0; i < 9; i++)
				{
					(*this)[i] = rhs[i];
				}
			}
			return *this;
		}

		inline mat33 operator* (float scaler) const
		{
			mat33 result(*this);
			result *= scaler;
			return result;
		}

		inline mat33 operator* (const mat33& rhs) const
		{
			mat33 result(*this);
			result *= rhs;
			return result;
		}

		inline vec3 operator* (const vec3& rhs) const
		{
			vec3 result;
			for (int i = 0; i < 3; i++)
			{
				result[i] = dot(row[i], rhs);
			}
			return result;
		}

		inline mat33& operator*= (float scaler)
		{
			for (int i = 0; i < 4; i++)
			{
				(*this)[i] *= scaler;
			}
			return *this;
		}

		inline mat33& operator*=(const mat33& rhs)
		{
			mat33 copy(*this);
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					m[i][j] = dot(copy.row[i], rhs.column(j));
				}
			}
			return *this;
		}

		inline bool operator== (const mat33& rhs) const
		{
			if (&rhs != this)
			{
				for (int i = 0; i < 4; i++)
				{
					if ((*this)[i] != rhs[i])
						return false;
				}
			}
			return true;
		}

		inline bool operator!= (const mat33& rhs) const { return !(*this == rhs); }

		inline float& operator[] (int index)
		{
			return const_cast<float&>(const_cast<const mat33*>(this)->operator[](index));
		}

		inline const float& operator[] (int index) const
		{
			assert(index >= 0 && index < 9);
			return *(&(m[0][0]) + index);
		}

		inline vec3 column(int index) const
		{
			assert(index >= 0 && index < 3);
			return vec3(m[0][index], m[1][index], row[2][index]);
		}

		inline void set_column(int index, vec3 v)
		{
			assert(index >= 0 && index < 3);
			for (int i = 0; i < 3; i++)
			{
				m[i][index] = v[i];
			}
		}

		inline void identity() { *this = I(); }

		inline void transpose()
		{
			swap(this->_10, this->_01);
			swap(this->_20, this->_02);

			swap(this->_21, this->_12);
		}

		inline mat33 transposed() const
		{
			mat33 result(*this);
			result.transpose();
			return result;
		}

		inline bool can_invert() const
		{
			if (is_orthogonal())
			{
				return true;
			}
			else
			{
				float det = determinant();
				return !fequal(det, 0.0f);
			}
		}

		inline void inverse()
		{
			if (is_orthogonal())
			{
				transpose();
			}
			else
			{
				float det = determinant();
				if (!fequal(det, 0.0f))
				{
					det = 1.0f / det;
					mat33 copy(*this);

					//to-do det_impl is calculated above in determinant().
					//try to gcd
					m[0][0] = +gml_impl::determinant(copy._11, copy._12, copy._21, copy._22) * det;
					m[1][0] = -gml_impl::determinant(copy._10, copy._12, copy._20, copy._22) * det;
					m[2][0] = +gml_impl::determinant(copy._10, copy._11, copy._20, copy._21) * det;

					m[0][1] = -gml_impl::determinant(copy._01, copy._02, copy._21, copy._22) * det;
					m[1][1] = +gml_impl::determinant(copy._00, copy._02, copy._20, copy._22) * det;
					m[2][1] = -gml_impl::determinant(copy._00, copy._01, copy._20, copy._21) * det;

					m[0][2] = +gml_impl::determinant(copy._01, copy._02, copy._11, copy._12) * det;
					m[1][2] = -gml_impl::determinant(copy._00, copy._02, copy._10, copy._12) * det;
					m[2][2] = +gml_impl::determinant(copy._00, copy._01, copy._10, copy._11) * det;
				}
				else
				{
					//TODO:
					// can not invert here,
					// what should i do when this occur ?
				}
			}
		}

		inline mat33 inversed() const
		{
			mat33 result(*this);
			result.inverse();
			return result;
		}

		inline bool is_orthogonal() const
		{
			for (int i = 0; i < 3; i++)
			{
				if (!fequal(row[i].length_sqr(), 1.0f))
				{
					return false;
				}

				for (int j = i + 1; j < 3; j++)
				{
					if (!fequal(dot(row[i], row[j]), 0.0f))
						return false;
				}
			}
			return false;
		}

		inline float determinant() const
		{
			return gml_impl::determinant(
				_00, _01, _02,
				_10, _11, _12,
				_20, _21, _22);
		}
	};

	//matrix33
	inline mat33 operator* (float scaler, const mat33& rhs)
	{
		return rhs * scaler;
	}

	inline vec3 operator* (const vec3& lhs, const mat33& rhs)
	{
		vec3 result;
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs, rhs.column(i));
		}
		return result;
	}

	inline vec2 transform_vector(const mat33& lhs, const vec2& rhs)
	{
		vec2 result;
		vec3 rhs3(rhs, 0);
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs.row[i], rhs3);
		}
		return result;
	}

	inline vec2 transform_point(const mat33& lhs, const vec2& rhs)
	{
		vec2 result;
		vec3 rhs3(rhs, 1);
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs.row[i], rhs3);
		}
		return result;
	}

}

namespace gml {

	class mat44
	{
	public:
		inline static const mat44& I()
		{
			static mat44 i(
				1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
				);
			return i;
		}

		inline static mat44 rotate_x(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);

			return mat44(
				1, 0, 0, 0,
				0, cosr, -sinr, 0,
				0, sinr, cosr, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 rotate_y(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);

			return mat44(
				cosr, 0, -sinr, 0,
				0, 1, 0, 0,
				sinr, 0, cosr, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 rotate_z(const radian& r)
		{
			float cosr = gml::cos(r);
			float sinr = gml::sin(r);

			return mat44(
				cosr, -sinr, 0, 0,
				sinr, cosr, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 scale(float scale)
		{
			return mat44(
				scale, 0, 0, 0,
				0, scale, 0, 0,
				0, 0, scale, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 scale(float sx, float sy, float sz)
		{
			return mat44(
				sx, 0, 0, 0,
				0, sy, 0, 0,
				0, 0, sz, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 translate(float x, float y, float z)
		{
			return mat44(
				1, 0, 0, x,
				0, 1, 0, y,
				0, 0, 1, z,
				0, 0, 0, 1
				);
		}

		inline static mat44 flip_x()

		{
			return mat44(
				-1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 flip_y()
		{
			return mat44(
				1, 0, 0, 0,
				0, -1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 flip_z()
		{
			return mat44(
				1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, -1, 0,
				0, 0, 0, 1
				);
		}

		inline static mat44 look_at(const vec3& eye, const vec3& look, const vec3& up)
		{
			vec3 forward = (look - eye).normalized();
			vec3 real_up = (up - forward * dot(forward, up.normalized())).normalized();
			vec3 right = cross(real_up, forward).normalized();
			mat44 rst(
				vec4(right, -dot(eye, right)),
				vec4(real_up, -dot(eye, real_up)),
				vec4(forward, -dot(eye, forward)),
				vec4(0, 0, 0, 1)
				);

			return rst;
			//return rst.transpose();
		}

		inline static mat44 perspective_lh(float fov, float aspect, float near, float far)
		{
			float near_top = tanf(fov * 0.5f);
			float near_right = near_top * aspect;

			float z_range = near - far;
			mat44 rst(
				1.0f / near_right, 0, 0, 0,
				0, 1.0f / near_top, 0, 0,
				0, 0, -far / z_range, far * near / z_range,
				0, 0, 1, 0);


			return rst;
		}

		inline static mat44 center_ortho_lh(float width, float height, float near, float far)
		{
			float z_range = far - near;
			mat44 rst(
				2.0f / width, 0, 0, 0,
				0, -2.0f / height, 0, 0,
				0, 0, 1.0f / z_range, -near / z_range,
				0, 0, 0, 1);
			return rst;
		}

		inline static mat44 ortho2d_lh(float width, float height, float near, float far)
		{
			float z_range = far - near;
			mat44 rst(
				2.0f / width, 0, 0, -1,
				0, -2.0f / height, 0, 1,
				0, 0, 1.0f / z_range, -near / z_range,
				0, 0, 0, 1);
			return rst;
		}

	public:
		union
		{
			float m[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
			struct { float _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33; };
			struct { vec4 row[4]; };
		};

		constexpr mat44(){}

		inline mat44(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33)
		{
			this->_00 = _00;	this->_01 = _01;	this->_02 = _02;	this->_03 = _03;
			this->_10 = _10;	this->_11 = _11;	this->_12 = _12;	this->_13 = _13;
			this->_20 = _20;	this->_21 = _21;	this->_22 = _22;	this->_23 = _23;
			this->_30 = _30;	this->_31 = _31;	this->_32 = _32;	this->_33 = _33;
		}

		inline mat44(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4)
		{
			this->row[0] = row1;
			this->row[1] = row2;
			this->row[2] = row3;
			this->row[3] = row4;
		}

		inline mat44(const mat44& other)
		{
			*this = other;
		}

		inline explicit mat44(const mat22& mat2)
		{
			row[0].set(mat2.row[0], 0, 0);
			row[1].set(mat2.row[1], 0, 0);
			row[2].set(0, 0, 1, 0);
			row[3].set(0, 0, 0, 1);
		}

		inline explicit mat44(const mat33& mat3)
		{
			row[0].set(mat3.row[0], 0);
			row[1].set(mat3.row[1], 0);
			row[2].set(mat3.row[2], 0);
			row[3].set(0, 0, 0, 1);
		}

		inline mat44& operator=(const mat44& rhs)
		{
			for (int i = 0; i < 16; i++)
			{
				(*this)[i] = rhs[i];
			}
			return *this;
		}

		inline mat44 operator* (float scaler) const
		{
			mat44 result(*this);
			result *= scaler;
			return result;
		}

		inline mat44 operator* (const mat44& rhs) const
		{
			mat44 result(*this);
			result *= rhs;
			return result;
		}

		inline vec4 operator* (const vec4& rhs) const
		{
			vec4 result;
			for (int i = 0; i < 4; i++)
			{
				result[i] = dot(row[i], rhs);
			}
			return result;
		}

		inline mat44& operator*= (float scaler)
		{
			for (int i = 0; i < 4; i++)
			{
				(*this)[i] *= scaler;
			}
			return *this;
		}

		inline mat44& operator*=(const mat44& rhs)
		{
			mat44 copy(*this);
			for (int i = 0; i < 4; i++)
			{
				for (int j = 0; j < 4; j++)
				{
					m[i][j] = dot(copy.row[i], rhs.column(j));
				}
			}
			return *this;
		}

		inline bool operator== (const mat44& rhs) const
		{
			if (&rhs != this)
			{
				for (int i = 0; i < 4; i++)
				{
					if ((*this)[i] != rhs[i])
						return false;
				}
			}
			return true;
		}

		inline bool operator!= (const mat44& rhs) const
		{
			return !(*this == rhs);
		}

		inline float& operator[] (int index)
		{
			return const_cast<float&>(const_cast<const mat44*>(this)->operator[](index));
		}

		inline const float& operator[] (int index) const
		{
			assert(index >= 0 && index < 16);
			return *(&(m[0][0]) + index);
		}

		inline vec4 column(int index) const
		{
			assert(index >= 0 && index < 4);
			return vec4(m[0][index], m[1][index], m[2][index], m[3][index]);
		}

		inline void set_column(int index, vec4 v)
		{
			assert(index >= 0 && index < 4);
			for (int i = 0; i < 4; i++)
			{
				m[i][index] = v[i];
			}
		}

		inline void identity() { *this = I(); }

		inline void transpose()
		{
			swap(this->_10, this->_01);
			swap(this->_20, this->_02);
			swap(this->_30, this->_03);

			swap(this->_21, this->_12);
			swap(this->_31, this->_13);

			swap(this->_32, this->_23);
		}

		inline mat44 transposed() const
		{
			mat44 result(*this);
			result.transpose();
			return result;
		}

		inline bool can_invert() const
		{
			if (is_orthogonal())
			{
				return true;
			}
			else
			{
				float det = determinant();
				return !fequal(det, 0.0f);
			}
		}

		inline void inverse()
		{
			if (is_orthogonal())
			{
				transpose();
			}
			else
			{
				float det = determinant();
				if (!fequal(det, 0.0f))
				{
					det = 1.0f / det;
					mat44 copy(*this);

					//to-do det_impl is calculated above in determinant().
					//try to gcd
					m[0][0] = +gml_impl::determinant(copy._11, copy._12, copy._13, copy._21, copy._22, copy._23, copy._31, copy._32, copy._33) * det;
					m[1][0] = -gml_impl::determinant(copy._10, copy._12, copy._13, copy._20, copy._22, copy._23, copy._30, copy._32, copy._33) * det;
					m[2][0] = +gml_impl::determinant(copy._10, copy._11, copy._13, copy._20, copy._21, copy._23, copy._30, copy._31, copy._33) * det;
					m[3][0] = -gml_impl::determinant(copy._10, copy._11, copy._12, copy._20, copy._21, copy._22, copy._30, copy._31, copy._32) * det;

					m[0][1] = -gml_impl::determinant(copy._01, copy._02, copy._03, copy._21, copy._22, copy._23, copy._31, copy._32, copy._33) * det;
					m[1][1] = +gml_impl::determinant(copy._00, copy._02, copy._03, copy._20, copy._22, copy._23, copy._30, copy._32, copy._33) * det;
					m[2][1] = -gml_impl::determinant(copy._00, copy._01, copy._03, copy._20, copy._21, copy._23, copy._30, copy._31, copy._33) * det;
					m[3][1] = +gml_impl::determinant(copy._00, copy._01, copy._02, copy._20, copy._21, copy._22, copy._30, copy._31, copy._32) * det;

					m[0][2] = +gml_impl::determinant(copy._01, copy._02, copy._03, copy._11, copy._12, copy._13, copy._31, copy._32, copy._33) * det;
					m[1][2] = -gml_impl::determinant(copy._00, copy._02, copy._03, copy._10, copy._12, copy._13, copy._30, copy._32, copy._33) * det;
					m[2][2] = +gml_impl::determinant(copy._00, copy._01, copy._03, copy._10, copy._11, copy._13, copy._30, copy._31, copy._33) * det;
					m[3][2] = -gml_impl::determinant(copy._00, copy._01, copy._02, copy._10, copy._11, copy._12, copy._30, copy._31, copy._32) * det;

					m[0][3] = -gml_impl::determinant(copy._01, copy._02, copy._03, copy._11, copy._12, copy._13, copy._21, copy._22, copy._23) * det;
					m[1][3] = +gml_impl::determinant(copy._00, copy._02, copy._03, copy._10, copy._12, copy._13, copy._20, copy._22, copy._23) * det;
					m[2][3] = -gml_impl::determinant(copy._00, copy._01, copy._03, copy._10, copy._11, copy._13, copy._20, copy._21, copy._23) * det;
					m[3][3] = +gml_impl::determinant(copy._00, copy._01, copy._02, copy._10, copy._11, copy._12, copy._20, copy._21, copy._22) * det;
				}
				else
				{
					//TODO:
					// can not invert here,
					// what should i do when this occur ?
				}
			}
		}

		inline mat44 inversed() const
		{
			mat44 result(*this);
			result.inverse();
			return result;
		}

		inline bool is_orthogonal() const
		{
			for (int i = 0; i < 4; i++)
			{
				if (!fequal(row[i].length_sqr(), 1.0f))
				{
					return false;
				}

				for (int j = i + 1; j < 4; j++)
				{
					if (!fequal(dot(row[i], row[j]), 0.0f))
						return false;
				}
			}
			return false;
		}

		inline float determinant() const
		{
			return gml_impl::determinant(
				_00, _01, _02, _03,
				_10, _11, _12, _13,
				_20, _21, _22, _23,
				_30, _31, _32, _33);
		}
	};

	//matrix44
	inline mat44 operator* (float scaler, const mat44& rhs)
	{
		return rhs * scaler;
	}

	inline vec4 operator* (const vec4& lhs, const mat44& rhs)
	{
		vec4 result;
		for (int i = 0; i < 4; i++)
		{
			result[i] = dot(lhs, rhs.column(i));
		}
		return result;
	}

	inline vec3 transform_vector(const mat44& lhs, const vec3& rhs)
	{
		vec3 result;
		vec4 rhs4(rhs, 0);
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs.row[i], rhs4);
		}
		return result;
	}

	inline vec3 transform_point(const mat44& lhs, const vec3& rhs)
	{
		vec3 result;
		vec4 rhs4(rhs, 1);
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs.row[i], rhs4);
		}
		return result;
	}
}

namespace gml
{
	constexpr mat22::mat22(const mat33& m33)
		: _00(m33._00), _01(m33._01)
		, _10(m33._10), _11(m33._11) {}

	constexpr mat22::mat22(const mat44& m44)
		: _00(m44._00), _01(m44._01)
		, _10(m44._10), _11(m44._11) {}

	constexpr mat33::mat33(const mat44& m44)
		: _00(m44._00), _01(m44._01), _02(m44._02)
		, _10(m44._10), _11(m44._11), _12(m44._12)
		, _20(m44._20), _21(m44._21), _22(m44._22) { }
}