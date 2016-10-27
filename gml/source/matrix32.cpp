#include "../include/gmlmatrix.h"
#include "../include/gmlutility.h"
#include "inner_util.h"
#include <cassert>
#include <cmath>

namespace gml
{
	const mat32& mat32::I()
	{
		static mat32 i(
			1.0f, 0.0f, 0.0f,
			0.0f, 1.0f, 0.0f
			);
		return i;
	}

	mat32 mat32::rotate(float radian)
	{
		float cosr = cosf(radian);
		float sinr = sinf(radian);
		return mat32(
			cosr, -sinr, 0,
			sinr, cosr, 0);
	}

	mat32 mat32::mat32::scale(float scaler)
	{
		return mat32(
			scaler, 0, 0,
			0, scaler, 0);
	}

	mat32 mat32::mat32::scale(float sx, float sy)
	{
		return mat32(
			sx, 0, 0,
			0, sy, 0);
	}
	mat32 mat32::translate(float x, float y)
	{
		return mat32(
			1, 0, x,
			0, 1, y);
	}

	mat32 mat32::flip_x()
	{
		return mat32(
			-1, 0, 0,
			0, 1, 0);
	}

	mat32 mat32::flip_y()
	{
		return mat32(
			1, 0, 0,
			0, -1, 0);
	}

	mat32 mat32::trsp(const vec2& translate, float rotation_radian, const vec2& scale, const vec2& pivot)
	{
		/*
			  1,0,tx * cos,-sin,0 * sx,0,0 * 1,0,-px
			  0,1,ty   sin, cos,0   0,sy,0   0,1,-py

			= cos,-sin,tx * sx,0,-sx*px
			  sin,+cos,ty   0,sy,-sy*py

			= cos*sx,-sin*sy, -cos*sx*px+sin*sy*px + tx
			  sin*sx, cos*sy, -sin*sx*px-cos*sy*py + ty
		*/
		float cosr = cos(rotation_radian);
		float sinr = sin(rotation_radian);
		float spx = -scale.x*pivot.x;
		float spy = -scale.y*pivot.y;

		return mat32(
			cosr*scale.x, -sinr*scale.y, cosr*spx - sinr*spy + translate.x,
			sinr*scale.x, +cosr*scale.y, sinr*spx + cosr*spy + translate.y
			);
	}

	mat32 mat32::trps(const vec2& translate, float rotation_radian, const vec2& pivot, const vec2& scale)
	{
		/*
			1,0,tx * cos,-sin,0 * 1,0,-px * sx,0,0
			0,1,ty   sin, cos,0   0,1,-px   0,sy,0

		  = cos,-sin,ty * sx,0,-px
			sin, cos,ty   0,sy,-px

		  = cos*sx,-sin*sy, -cos*px+sin*px + tx
			sin*sx,+cos*sy, -sin*px-cos*py + ty
		*/
		float cosr = cos(rotation_radian);
		float sinr = sin(rotation_radian);

		return mat32(
			cosr*scale.x, -sinr*scale.y, -cosr*pivot.x + sinr*pivot.y + translate.x,
			sinr*scale.x, +cosr*scale.y, -sinr*pivot.x - cosr*pivot.y + translate.y
			);
	}

	mat32::mat32() {}

	mat32::mat32(float _00, float _01, float _02, float _10, float _11, float _12)
	{
		this->_00 = _00;	this->_01 = _01;	this->_02 = _02;
		this->_10 = _10;	this->_11 = _11;	this->_12 = _12;
	}

	mat32::mat32(const vec3& row1, const vec3& row2)
	{
		this->rows[0].r = row1;
		this->rows[1].r = row2;
	}

	mat32::mat32(const mat32& other)
	{
		*this = other;
	}

	mat32::mat32(const mat22& mat2)
	{
		rows[0].r.set(mat2.row[0], 0);
		rows[1].r.set(mat2.row[1], 0);
	}

	mat32& mat32::operator=(const mat32& rhs)
	{
		if (&rhs != this)
		{
			for (int i = 0; i < 6; i++)
			{
				(*this)[i] = rhs[i];
			}
		}
		return *this;
	}

	mat32 mat32::operator*(const mat32& rhs) const
	{
		mat32 result(*this);
		result *= rhs;
		return result;
	}

	mat32& mat32::operator*=(const mat32& rhs)
	{
		mat32 copy(*this);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				m[i][j] = dot(copy.rows[i].r, vec3(rhs.column(j), 0));
			}
		}
		return *this;
	}

	bool mat32::operator== (const mat32& rhs) const
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

	bool mat32::operator!= (const mat32& rhs) const
	{
		return !(*this == rhs);
	}

	float& mat32::operator[] (int index)
	{
		return const_cast<float&>(const_cast<const mat32*>(this)->operator[](index));
	}

	const float& mat32::operator[] (int index) const
	{
		assert(index >= 0 && index < 6);
		if (index > 2) index++;
		return *(&(m[0][0]) + index);
	}

	vec3& mat32::row(int index)
	{
		return const_cast<vec3&>(const_cast<const mat32*>(this)->row(index));
	}

	const vec3& mat32::row(int index) const
	{
		assert(index >= 0 && index < 2);
		return rows[index].r;
	}

	vec2 mat32::column(int index) const
	{
		assert(index >= 0 && index < 3);
		return vec2(m[0][index], m[1][index]);
	}

	mat32& mat32::set_column(int index, vec2 v)
	{
		assert(index >= 0 && index < 3);
		for (int i = 0; i < 3; i++)
		{
			m[i][index] = v[i];
		}
		return *this;
	}

	mat32& mat32::identity()
	{
		return *this = I();
	}

	vec2 transform_vector(const mat32& lhs, const vec2& rhs)
	{
		vec2 result;
		vec3 rhs3(rhs, 0);
		for (int i = 0; i < 2; i++)
		{
			result[i] = dot(lhs.rows[i].r, rhs3);
		}
		return result;
	}

	vec2 transform_point(const mat32& lhs, const vec2& rhs)
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