#include "../include/gmlmatrix.h"
#include "../include/gmlutility.h"
#include "inner_util.h"
#include <cassert>
#include <cmath>

namespace gml
{
	const mat22& mat22::I()
	{
		static mat22 i(
			1.0f, 0.0f,
			0.0f, 1.0f
			);
		return i;
	}

	mat22 mat22::rotate(const radian& r)
	{
		float cosr = gml::cos(r);
		float sinr = gml::sin(r);
		return mat22(
			cosr, -sinr,
			sinr, cosr);
	}

	mat22 mat22::mat22::scale(float scaler)
	{
		return mat22(
			scaler, 0,
			0, scaler);
	}

	mat22 mat22::mat22::scale(float sx, float sy)
	{
		return mat22(
			sx, 0,
			0, sy);
	}

	mat22 mat22::flip_x()
	{
		return mat22(
			-1, 0,
			0, 1);
	}

	mat22 mat22::flip_y()
	{
		return mat22(
			1, 0,
			0, -1);
	}

	mat22::mat22() {}

	mat22::mat22(float _00, float _01, float _10, float _11)
	{
		this->_00 = _00;	this->_01 = _01;
		this->_10 = _10;	this->_11 = _11;
	}

	mat22::mat22(const vec2& row1, const vec2& row2)
	{
		this->row[0] = row1;
		this->row[1] = row2;
	}

	mat22::mat22(const mat22& other)
	{
		*this = other;
	}

	mat22::mat22(const mat33& mat3)
	{
		row[0].set(mat3.row[0]);
		row[1].set(mat3.row[1]);

	}

	mat22::mat22(const mat44& mat4)
	{
		row[0].set(mat4.row[0]);
		row[1].set(mat4.row[1]);
	}

	mat22& mat22::operator=(const mat22& rhs)
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

	mat22 mat22::operator*(float scaler) const
	{
		mat22 result(*this);
		result *= scaler;
		return result;
	}

	mat22 mat22::operator*(const mat22& rhs) const
	{
		mat22 result(*this);
		result *= rhs;
		return result;
	}

	vec2 mat22::operator* (const vec2& rhs) const
	{
		vec2 result;
		for (int i = 0; i < 2; i++)
		{
			result[i] = dot(row[i], rhs);
		}
		return result;
	}

	mat22& mat22::operator*=(float scaler)
	{
		for (int i = 0; i < 4; i++)
		{
			(*this)[i] *= scaler;
		}
		return *this;
	}

	mat22& mat22::operator*=(const mat22& rhs)
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

	bool mat22::operator== (const mat22& rhs) const
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

	bool mat22::operator!= (const mat22& rhs) const
	{
		return !(*this == rhs);
	}

	float& mat22::operator[] (int index)
	{
		return const_cast<float&>(const_cast<const mat22*>(this)->operator[](index));
	}

	const float& mat22::operator[] (int index) const
	{
		assert(index >= 0 && index < 4);
		return *(&(m[0][0]) + index);
	}

	vec2 mat22::column(int index) const
	{
		assert(index >= 0 && index < 2);
		return vec2(m[0][index], m[1][index]);
	}

	void mat22::set_column(int index, vec2 v)
	{
		assert(index >= 0 && index < 2);
		for (int i = 0; i < 2; i++)
		{
			m[i][index] = v[i];
		}
	}



	void mat22::identity()
	{
		*this = I();
	}

	void mat22::transpose()
	{
		swap(this->_10, this->_01);
	}

	mat22 mat22::transposed() const
	{
		mat22 result(*this);
		result.transpose();
		return result;
	}

	bool mat22::can_invert() const
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

	void mat22::inverse()
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

	mat22 mat22::inversed() const
	{
		mat22 result(*this);
		result.inverse();
		return result;
	}

	bool mat22::is_orthogonal() const
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

	float mat22::determinant() const
	{
		return determinant_impl(
			_00, _01,
			_10, _11);
	}

	mat22 operator* (float scaler, const mat22& rhs)
	{
		return rhs * scaler;
	}

	vec2 operator* (const vec2& lhs, const mat22& rhs)
	{
		vec2 result;
		for (int i = 0; i < 2; i++)
		{
			result[i] = dot(lhs, rhs.column(i));
		}
		return result;
	}
}