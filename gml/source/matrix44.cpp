#include "../include/gmlmatrix.h"
#include "../include/gmlutility.h"
#include <cassert>
#include <cmath>

namespace gml
{
	const mat44& mat44::I()
	{
		static mat44 i(
			1.0f, 0.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f, 0.0f,
			0.0f, 0.0f, 1.0f, 0.0f,
			0.0f, 0.0f, 0.0f, 1.0f
			);
		return i;
	}

	mat44 mat44::rotate_x(const radian& r)
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

	mat44 mat44::rotate_y(const radian& r)
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

	mat44 mat44::rotate_z(const radian& r)
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

	mat44 mat44::scale(float scale)
	{
		return mat44(
			scale, 0, 0, 0,
			0, scale, 0, 0,
			0, 0, scale, 0,
			0, 0, 0, 1
			);
	}

	mat44 mat44::scale(float sx, float sy, float sz)
	{
		return mat44(
			sx, 0, 0, 0,
			0, sy, 0, 0,
			0, 0, sz, 0,
			0, 0, 0, 1
			);
	}

	mat44 mat44::translate(float x, float y, float z)
	{
		return mat44(
			1, 0, 0, x,
			0, 1, 0, y,
			0, 0, 1, z,
			0, 0, 0, 1
			);
	}

	mat44 mat44::flip_x()
	{
		return mat44(
			-1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
			);
	}

	mat44 mat44::flip_y()
	{
		return mat44(
			1, 0, 0, 0,
			0, -1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
			);
	}

	mat44 mat44::flip_z()
	{
		return mat44(
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, -1, 0,
			0, 0, 0, 1
			);
	}

	mat44 mat44::look_at(const vec3& eye, const vec3& look, const vec3& up)
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

	mat44 mat44::perspective_lh(float fov, float aspect, float near, float far)
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

	mat44 mat44::center_ortho_lh(float width, float height, float near, float far)
	{
		float z_range = far - near;
		mat44 rst(
			2.0f / width, 0, 0, 0,
			0, -2.0f / height, 0, 0,
			0, 0, 1.0f / z_range, -near / z_range,
			0, 0, 0, 1);
		return rst;
	}

	mat44 mat44::ortho2d_lh(float width, float height, float near, float far)
	{
		float z_range = far - near;
		mat44 rst(
			2.0f / width, 0, 0, -1,
			0, -2.0f / height, 0, 1,
			0, 0, 1.0f / z_range, -near / z_range,
			0, 0, 0, 1);
		return rst;
	}

	mat44::mat44() {}

	mat44::mat44(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33)
	{
		this->_00 = _00;	this->_01 = _01;	this->_02 = _02;	this->_03 = _03;
		this->_10 = _10;	this->_11 = _11;	this->_12 = _12;	this->_13 = _13;
		this->_20 = _20;	this->_21 = _21;	this->_22 = _22;	this->_23 = _23;
		this->_30 = _30;	this->_31 = _31;	this->_32 = _32;	this->_33 = _33;
	}

	mat44::mat44(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4)
	{
		this->row[0] = row1;
		this->row[1] = row2;
		this->row[2] = row3;
		this->row[3] = row4;
	}

	mat44::mat44(const mat44& other)
	{
		*this = other;
	}

	mat44::mat44(const mat22& mat2)
	{
		row[0].set(mat2.row[0], 0, 0);
		row[1].set(mat2.row[1], 0, 0);
		row[2].set(0, 0, 1, 0);
		row[3].set(0, 0, 0, 1);
	}

	mat44::mat44(const mat33& mat3)
	{
		row[0].set(mat3.row[0], 0);
		row[1].set(mat3.row[1], 0);
		row[2].set(mat3.row[2], 0);
		row[3].set(0, 0, 0, 1);
	}

	mat44& mat44::operator=(const mat44& other)
	{
		for (int i = 0; i < 16; i++)
		{
			(*this)[i] = other[i];
		}
		return *this;
	}

	mat44 mat44::operator*(float scaler) const
	{
		mat44 result(*this);
		result *= scaler;
		return result;
	}

	mat44 mat44::operator*(const mat44& rhs) const
	{
		mat44 result(*this);
		result *= rhs;
		return result;
	}

	vec4 mat44::operator* (const vec4& rhs) const
	{
		vec4 result;
		for (int i = 0; i < 4; i++)
		{
			result[i] = dot(row[i], rhs);
		}
		return result;
	}

	mat44& mat44::operator*=(float scaler)
	{
		for (int i = 0; i < 4; i++)
		{
			(*this)[i] *= scaler;
		}
		return *this;
	}

	mat44& mat44::operator*=(const mat44& rhs)
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

	bool mat44::operator== (const mat44& other) const
	{
		if (&other != this)
		{
			for (int i = 0; i < 4; i++)
			{
				if ((*this)[i] != other[i])
					return false;
			}
		}
		return true;
	}

	bool mat44::operator!= (const mat44& other) const
	{
		return !(*this == other);
	}

	float& mat44::operator[] (int index)
	{
		return const_cast<float&>(const_cast<const mat44*>(this)->operator[](index));
	}

	const float& mat44::operator[] (int index) const
	{
		assert(index >= 0 && index < 16);
		return *(&(m[0][0]) + index);
	}

	vec4 mat44::column(int index) const
	{
		assert(index >= 0 && index < 4);
		return vec4(m[0][index], m[1][index], m[2][index], m[3][index]);
	}

	void mat44::set_column(int index, vec4 v)
	{
		assert(index >= 0 && index < 4);
		for (int i = 0; i < 4; i++)
		{
			m[i][index] = v[i];
		}
	}

	void mat44::identity()
	{
		*this = I();
	}

	void mat44::transpose()
	{
		swap(this->_10, this->_01);
		swap(this->_20, this->_02);
		swap(this->_30, this->_03);

		swap(this->_21, this->_12);
		swap(this->_31, this->_13);

		swap(this->_32, this->_23);
	}

	mat44 mat44::transposed() const
	{
		mat44 result(*this);
		result.transpose();
		return result;
	}

	bool mat44::can_invert() const
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

	void mat44::inverse()
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

	mat44 mat44::inversed() const
	{
		mat44 result(*this);
		result.inverse();
		return result;
	}

	bool mat44::is_orthogonal() const
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

	float mat44::determinant() const
	{
		return gml_impl::determinant(
			_00, _01, _02, _03,
			_10, _11, _12, _13,
			_20, _21, _22, _23,
			_30, _31, _32, _33);
	}

	mat44 operator* (float scaler, const mat44& rhs)
	{
		return rhs * scaler;
	}

	vec4 operator* (const vec4& lhs, const mat44& rhs)
	{
		vec4 result;
		for (int i = 0; i < 4; i++)
		{
			result[i] = dot(lhs, rhs.column(i));
		}
		return result;
	}

	vec3 transform_vector(const mat44& lhs, const vec3& rhs)
	{
		vec3 result;
		vec4 rhs4(rhs, 0);
		for (int i = 0; i < 3; i++)
		{
			result[i] = dot(lhs.row[i], rhs4);
		}
		return result;
	}

	vec3 transform_point(const mat44& lhs, const vec3& rhs)
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