#pragma once
#include <gmlvector.h>
#include <gmlutility.h>

namespace gml
{
	class mat22;
	class mat33;
	class mat44;

	class mat22
	{
	public:
		static const mat22& I();

		static mat22 rotate(const radian& r);

		static mat22 scale(float scale);

		static mat22 scale(float sx, float sy);

		static mat22 flip_x();

		static mat22 flip_y();

	public:
		union
		{
			float m[2][2] = { 0,0,0,0 };
			struct { float _00, _01, _10, _11; };
			struct { vec2 row[2]; };
		};

		mat22();

		mat22(float _00, float _01, float _10, float _11);

		mat22(const vec2& row1, const vec2& row2);

		mat22(const mat22& other);

		explicit mat22(const mat33&);

		explicit mat22(const mat44&);

		mat22& operator=(const mat22& rhs);

		mat22 operator* (float scaler) const;

		mat22 operator* (const mat22& rhs) const;

		vec2 operator* (const vec2& rhs) const;

		mat22& operator*= (float scaler);

		mat22& operator*=(const mat22& rhs);

		bool operator== (const mat22& rhs) const;

		bool operator!= (const mat22& rhs) const;

		float& operator[] (int index);

		const float& operator[] (int index) const;

		vec2 column(int index) const;

		mat22& set_column(int index, vec2);

		mat22& identity();

		mat22& transpose();

		mat22 transposed() const;

		bool can_invert() const;

		mat22& inverse();

		mat22 inversed() const;

		bool is_orthogonal() const;

		float determinant() const;
	};

	class mat32
	{
	public:
		static const mat32& I();

		static mat32 rotate(const radian& r);

		static mat32 scale(float scale);

		static mat32 scale(float sx, float sy);

		static mat32 translate(float x, float y);

		static mat32 flip_x();

		static mat32 flip_y();

		static mat32 inv_trs(const vec2& translate, const radian& r, const vec2& scale);

		static mat32 trs(const vec2& translate, const radian& r, const vec2& scale);

		static mat32 trsp(const vec2& translate, const radian& r, const vec2& scale, const vec2& pivot);

		static mat32 trps(const vec2& translate, const radian& r, const vec2& pivot, const vec2& scale);

	public:
		union
		{
			// special for GPU constant buffer layout.
			float m[2][4] = { 0,0,0,0,0,0,0,0 };
			struct { float _00, _01, _02, _dummy_0, _10, _11, _12, _dummy_1; };
			struct { vec3 r; float _dummy_2; } rows[2];
		};

		mat32();

		mat32(float _00, float _01, float _02, float _10, float _11, float _12);

		mat32(const vec3& row1, const vec3& row2);

		mat32(const mat32& other);

		explicit mat32(const mat22&);

		mat32& operator=(const mat32& rhs);

		mat32 operator* (const mat32& rhs) const;

		mat32& operator*=(const mat32& rhs);

		bool operator== (const mat32& rhs) const;

		bool operator!= (const mat32& rhs) const;

		float& operator[] (unsigned int index);

		const float& operator[] (unsigned int index) const;

		vec3& row(unsigned int index);

		const vec3& row(unsigned int index) const;

		vec2 column(unsigned int index) const;

		mat32& set_column(unsigned int index, vec2);

		mat32& identity();
	};

	class mat33
	{
	public:
		static const mat33& I();

		static mat33 rotate_x(const radian& r);

		static mat33 rotate_y(const radian& r);

		static mat33 rotate_z(const radian& r);

		static mat33 scale(float scale);

		static mat33 scale(float sx, float sy, float sz);

		static mat33 flip_x();

		static mat33 flip_y();

		static mat33 flip_z();
	public:
		union
		{
			float m[3][3] = { 0,0,0,0,0,0,0,0,0 };
			struct { float _00, _01, _02, _10, _11, _12, _20, _21, _22; };
			struct { vec3 row[3]; };
		};

		mat33();

		mat33(float _00, float _01, float _02, float _10, float _11, float _12, float _20, float _21, float _22);

		mat33(const vec3& row1, const vec3& row2, const vec3& row3);

		mat33(const mat33& other);

		explicit mat33(const mat22&);

		explicit mat33(const mat44&);

		mat33& operator=(const mat33& rhs);

		mat33 operator* (float scaler) const;

		mat33 operator* (const mat33& rhs) const;

		vec3 operator* (const vec3& rhs) const;

		mat33& operator*= (float scaler);

		mat33& operator*=(const mat33& rhs);

		bool operator== (const mat33& rhs) const;

		bool operator!= (const mat33& rhs) const;

		float& operator[] (int index);

		const float& operator[] (int index) const;

		vec3 column(int index) const;

		mat33& set_column(int index, vec3);

		mat33& identity();

		mat33& transpose();

		mat33 transposed() const;

		bool can_invert() const;

		mat33& inverse();

		mat33 inversed() const;

		bool is_orthogonal() const;

		float determinant() const;
	};

	class mat44
	{
	public:
		static const mat44& I();

		static mat44 rotate_x(const radian& r);

		static mat44 rotate_y(const radian& r);

		static mat44 rotate_z(const radian& r);

		static mat44 scale(float scale);

		static mat44 scale(float sx, float sy, float sz);

		static mat44 translate(float x, float y, float z);

		static mat44 flip_x();

		static mat44 flip_y();

		static mat44 flip_z();

		static mat44 look_at(const vec3& eye, const vec3& look, const vec3& up);

		static mat44 perspective_lh(float fov, float aspect, float near, float far);

		static mat44 center_ortho_lh(float width, float height, float near, float far);

		static mat44 ortho2d_lh(float width, float height, float near, float far);

	public:
		union
		{
			float m[4][4] = { 0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 };
			struct { float _00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33; };
			struct { vec4 row[4]; };
		};

		mat44();

		mat44(float _00, float _01, float _02, float _03, float _10, float _11, float _12, float _13, float _20, float _21, float _22, float _23, float _30, float _31, float _32, float _33);

		mat44(const vec4& row1, const vec4& row2, const vec4& row3, const vec4& row4);

		mat44(const mat44& other);

		explicit mat44(const mat22&);

		explicit mat44(const mat33&);

		mat44& operator=(const mat44& rhs);

		mat44 operator* (float scaler) const;

		mat44 operator* (const mat44& rhs) const;

		vec4 operator* (const vec4& rhs) const;

		mat44& operator*= (float scaler);

		mat44& operator*=(const mat44& rhs);

		bool operator== (const mat44& rhs) const;

		bool operator!= (const mat44& rhs) const;

		float& operator[] (int index);

		const float& operator[] (int index) const;

		vec4 column(int index) const;

		mat44& set_column(int index, vec4);

		mat44& identity();

		mat44& transpose();

		mat44 transposed() const;

		bool can_invert() const;

		mat44& inverse();

		mat44 inversed() const;

		bool is_orthogonal() const;

		float determinant() const;
	};

	//matrix22
	mat22 operator* (float scaler, const mat22& rhs);

	vec2 operator* (const vec2& lhs, const mat22& rhs);

	//matrix32
	vec2 transform_vector(const mat32& lhs, const vec2& rhs);

	vec2 transform_point(const mat32& lhs, const vec2& rhs);

	//matrix33
	mat33 operator* (float scaler, const mat33& rhs);

	vec3 operator* (const vec3& lhs, const mat33& rhs);

	vec2 transform_vector(const mat33& lhs, const vec2& rhs);

	vec2 transform_point(const mat33& lhs, const vec2& rhs);

	//matrix44
	mat44 operator* (float scaler, const mat44& rhs);

	vec4 operator* (const vec4& lhs, const mat44& rhs);

	vec3 transform_vector(const mat44& lhs, const vec3& rhs);

	vec3 transform_point(const mat44& lhs, const vec3& rhs);
}
