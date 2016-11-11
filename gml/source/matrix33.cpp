#include "../include/gmlmatrix.h"
#include "../include/gmlutility.h"
#include "inner_util.h"
#include <cassert>
#include <cmath>

namespace gml
{
	const mat33& mat33::I()
	{
		static mat33 i(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 1.0f
			);
		return i;
	}

	mat33 mat33::rotate_x(const radian& r)
	{
		float cosr = gml::cos(r);
		float sinr = gml::sin(r);

		return mat33(
			1, 0, 0,
			0, cosr, -sinr,
			0, sinr, cosr
			);
	}

	mat33 mat33::rotate_y(const radian& r)
	{
		float cosr = gml::cos(r);
		float sinr = gml::sin(r);

		return mat33(
			cosr, 0, -sinr,
			0, 1, 0,
			sinr, 0, cosr
			);
	}

	mat33 mat33::rotate_z(const radian& r)
	{
		float cosr = gml::cos(r);
		float sinr = gml::sin(r);

		return mat33(
			cosr, -sinr, 0,
			sinr, cosr, 0,
			0, 0, 1
			);
	}

	mat33 mat33::scale(float scale)
	{
		return mat33(
			scale, 0, 0,
			0, scale, 0,
			0, 0, scale
			);
	}

	mat33 mat33::scale(float sx, float sy, float sz)
	{
		return mat33(
			sx, 0, 0,
			0, sy, 0,
			0, 0, sz
			);
	}

	mat33 mat33::flip_x()
	{
		return mat33(
			-1, 0, 0,
			0, 1, 0,
			0, 0, 1
			);
	}

	mat33 mat33::flip_y()
	{
		return mat33(
			1, 0, 0,
			0, -1, 0,
			0, 0, 1
			);
	}

	mat33 mat33::flip_z()
	{
		return mat33(
			1, 0, 0,
			0, 1, 0,
			0, 0, -1
			);
	}

	mat33::mat33() {}

	mat33::mat33(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22)
	{
		this->_00 = _00;	this->_01 = _01;	this->_02 = _02;
		this->_10 = _10;	this->_11 = _11;	this->_12 = _12;
		this->_20 = _20;	this->_21 = _21;	this->_22 = _22;
	}

	mat33::mat33(const vec3& row1, const vec3& row2, const vec3& row3)
	{
		this->row[0] = row1;
		this->row[1] = row2;
		this->row[2] = row3;
	}

	mat33::mat33(const mat33& other)
	{
		*this = other;
	}

	mat33::mat33(const mat22& mat2)
	{
		row[0].set(mat2.row[0], 0);
		row[1].set(mat2.row[1], 0);
		row[2].set(0, 0, 1);
	}

	mat33::mat33(const mat44& mat4)
	{
		row[0].set(mat4.row[0]);
		row[1].set(mat4.row[1]);
		row[2].set(mat4.row[2]);
	}

	mat33& mat33::operator=(const mat33& rhs)
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

	mat33 mat33::operator*(float scaler) const
	{
		mat33 result(*this);
		result *= scaler;
		return result;
	}

	mat33 mat33::operator*(const mat33& rhs) const
	{
		mat33 result(*this);
		result *= rhs;
		return result;
	}

	vec3 mat33::operator* (const vec3& rhs) const
	{
		vec3 result;
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(row[i], rhs);
		}
		return result;
	}

	mat33& mat33::operator*=(float scaler)
	{
		for (int i = 0; i < 4; i++)
		{
			(*this)[i] *= scaler;
		}
		return *this;
	}

	mat33& mat33::operator*=(const mat33& rhs)
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

	bool mat33::operator== (const mat33& rhs) const
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

	bool mat33::operator!= (const mat33& rhs) const
	{
		return !(*this == rhs);
	}

	float& mat33::operator[] (int index)
	{
		return const_cast<float&>(const_cast<const mat33*>(this)->operator[](index));
	}

	const float& mat33::operator[] (int index) const
	{
		assert(index >= 0 && index < 9);
		return *(&(m[0][0]) + index);
	}

	vec3 mat33::column(int index) const
	{
		assert(index >= 0 && index < 3);
		return vec3(m[0][index], m[1][index], row[2][index]);
	}

	void mat33::set_column(int index, vec3 v)
	{
		assert(index >= 0 && index < 3);
		for (int i = 0; i < 3; i++)
		{
			m[i][index] = v[i];
		}
	}

	void mat33::identity()
	{
		*this = I();
	}

	void mat33::transpose()
	{
		swap(this->_10, this->_01);
		swap(this->_20, this->_02);

		swap(this->_21, this->_12);
	}

	mat33 mat33::transposed() const
	{
		mat33 result(*this);
		result.transpose();
		return result;
	}
	
	bool mat33::can_invert() const
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

	void mat33::inverse()
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
				m[0][0] = +determinant_impl(copy._11, copy._12, copy._21, copy._22) * det;
				m[1][0] = -determinant_impl(copy._10, copy._12, copy._20, copy._22) * det;
				m[2][0] = +determinant_impl(copy._10, copy._11, copy._20, copy._21) * det;

				m[0][1] = -determinant_impl(copy._01, copy._02, copy._21, copy._22) * det;
				m[1][1] = +determinant_impl(copy._00, copy._02, copy._20, copy._22) * det;
				m[2][1] = -determinant_impl(copy._00, copy._01, copy._20, copy._21) * det;

				m[0][2] = +determinant_impl(copy._01, copy._02, copy._11, copy._12) * det;
				m[1][2] = -determinant_impl(copy._00, copy._02, copy._10, copy._12) * det;
				m[2][2] = +determinant_impl(copy._00, copy._01, copy._10, copy._11) * det;
			}
			else
			{
				//TODO:
				// can not invert here,
				// what should i do when this occur ?
			}
		}
	}

	mat33 mat33::inversed() const
	{
		mat33 result(*this);
		result.inverse();
		return result;
	}

	bool mat33::is_orthogonal() const
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

	float mat33::determinant() const
	{
		return determinant_impl(
			_00, _01, _02,
			_10, _11, _12,
			_20, _21, _22);
	}

	mat33 operator* (float scaler, const mat33& rhs)
	{
		return rhs * scaler;
	}

	vec3 operator* (const vec3& lhs, const mat33& rhs)
	{
		vec3 result;
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs, rhs.column(i));
		}
		return result;
	}

	vec2 transform_vector(const mat33& lhs, const vec2& rhs)
	{
		vec2 result;
		vec3 rhs3(rhs, 0);
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs.row[i], rhs3);
		}
		return result;
	}

	vec2 transform_point(const mat33& lhs, const vec2& rhs)
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