#pragma once


namespace // for swizzle
{
	struct _X { constexpr static const int SwizzleIndex = 0; };
	struct _Y { constexpr static const int SwizzleIndex = 1; };
	struct _Z { constexpr static const int SwizzleIndex = 2; };
	struct _W { constexpr static const int SwizzleIndex = 3; };
}
namespace gml
{
	class vec2;
	class vec3;
	class vec4;

	class vec2
	{
	public:
		static const vec2& zero();
		static const vec2& one();
		static const vec2& left();
		static const vec2& right();
		static const vec2& up();
		static const vec2& down();

	public:
		float x = 0.0f;
		float y = 0.0f;

	public:
		vec2();

		vec2(float x, float y);

		explicit vec2(const vec3& v3);

		explicit vec2(const vec4& v4);

		vec2 operator-() const;

		bool operator==(const vec2& rhs) const;

		bool operator!=(const vec2& rhs) const;

		vec2 operator+(float value) const;

		vec2 operator-(float value) const;

		vec2 operator*(float value) const;

		vec2 operator+(const vec2& rhs) const;

		vec2 operator-(const vec2& rhs) const;

		vec2 operator*(const vec2& rhs) const;

		vec2& operator+=(float value);

		vec2& operator-=(float value);

		vec2& operator*=(float value);

		vec2& operator+=(const vec2& rhs);

		vec2& operator-=(const vec2& rhs);

		vec2& operator*=(const vec2& rhs);

		//hack
		float& operator[](int index);

		const float& operator[](int index) const;

		explicit operator float*();

		vec2& set(float x, float y);

		vec2& set(const vec3& v3);

		vec2& set(const vec4& v4);

		vec2 normalized() const;

		vec2& normalize();

		vec2& inverse();

		vec2 inversed() const;

		float length() const;

		float length_sqr() const;
	};

	class vec3
	{
	public:
		static const vec3& zero();
		static const vec3& one();
		static const vec3& left();
		static const vec3& right();
		static const vec3& up();
		static const vec3& down();
		static const vec3& forward();
		static const vec3& backward();

	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;

	public:
		vec3();

		vec3(float x, float y, float z);

		vec3(const vec2& v2, float z);

		explicit vec3(const vec4& v4);

		vec3 operator-() const;

		bool operator==(const vec3& rhs) const;

		bool operator!=(const vec3& rhs) const;

		vec3 operator+(float value) const;

		vec3 operator-(float value) const;

		vec3 operator*(float value) const;

		vec3 operator+(const vec3& rhs) const;

		vec3 operator-(const vec3& rhs) const;

		vec3 operator*(const vec3& rhs) const;

		vec3& operator+=(float value);

		vec3& operator-=(float value);

		vec3& operator*=(float value);

		vec3& operator+=(const vec3& rhs);

		vec3& operator-=(const vec3& rhs);

		vec3& operator*=(const vec3& rhs);

		//hack
		float& operator[](int index);

		const float& operator[](int index) const;

		explicit operator float*();

		vec3& set(const vec2& v2, float z);

		vec3& set(float x, float y, float z);

		vec3& set(const vec4& v4);

		vec3& replace(const vec2& v2);

		vec3 normalized() const;

		vec3& normalize();

		vec3& inverse();

		vec3 inversed() const;

		float length() const;

		float length_sqr() const;
	};

	class vec4
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

	public:
		vec4();

		vec4(float x, float y, float z, float w);

		vec4(const vec2& v2, float z, float w);

		vec4(const vec3& v3, float w);

		bool operator==(const vec4& rhs) const;

		bool operator!=(const vec4& rhs) const;

		vec4 operator+(float value) const;

		vec4 operator-(float value) const;

		vec4 operator*(float value) const;

		vec4 operator+(const vec4& rhs) const;

		vec4 operator-(const vec4& rhs) const;

		vec4 operator*(const vec4& rhs) const;

		vec4& operator+=(float value);

		vec4& operator-=(float value);

		vec4& operator*=(float value);

		vec4& operator+=(const vec4& rhs);

		vec4& operator-=(const vec4& rhs);

		vec4& operator*=(const vec4& rhs);

		//hack
		float& operator[](int index);

		const float& operator[](int index) const;

		explicit operator float*();

		vec4& set(const vec2& v2, float z, float w);

		vec4& set(const vec3& v3, float w);

		vec4& set(float x, float y, float z, float w);

		vec4& replace(const vec2& v2);

		vec4& replace(const vec3& v3);

		float length() const;

		float length_sqr() const;
	};

	//vec2
	vec2 operator+(float value, const vec2& rhs);

	vec2 operator-(float value, const vec2& rhs);

	vec2 operator*(float value, const vec2& rhs);

	float dot(const vec2& lhs, const vec2& rhs);

	float cross(const vec2& lhs, const vec2& rhs);

	vec2 min_combine(const vec2& lhs, const vec2& rhs);

	vec2 max_combine(const vec2& lhs, const vec2& rhs);

	float det22(const gml::vec2& row1, const gml::vec2& row2);

	float det22_t(const gml::vec2& row1, const gml::vec2& row2);

	//vec3
	vec3 operator+(float value, const vec3& rhs);

	vec3 operator-(float value, const vec3& rhs);

	vec3 operator*(float value, const vec3& rhs);

	float dot(const vec3& lhs, const vec3& rhs);

	vec3 cross(const vec3& lhs, const vec3& rhs);

	vec3 min_combine(const vec3& lhs, const vec3& rhs);

	vec3 max_combine(const vec3& lhs, const vec3& rhs);

	float det33(const gml::vec3& row1, const gml::vec3& row2, const gml::vec3& row3);

	float det33_t(const gml::vec3& row1, const gml::vec3& row2, const gml::vec3& row3);

	//vec4
	float dot(const vec4& lhs, const vec4& rhs);

	float det44(const gml::vec4& row1, const gml::vec4& row2, const gml::vec4& row3, const gml::vec4& row4);

	float det44_t(const gml::vec4& row1, const gml::vec4& row2, const gml::vec4& row3, const gml::vec4& row4);

	template<typename SwizzleX, typename SwizzleY>
	inline vec2 swizzle(const vec2& v2)
	{
		return vec2(v2[SwizzleX::SwizzleIndex], v2[SwizzleY::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY>
	inline vec2 swizzle(const vec3& v3)
	{
		return vec2(v3[SwizzleX::SwizzleIndex], v3[SwizzleY::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY>
	inline vec2 swizzle(const vec4& v4)
	{
		return vec2(v4[SwizzleX::SwizzleIndex], v4[SwizzleY::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SeizzleZ>
	inline vec3 swizzle(const vec2& v2)
	{
		return vec3(v2[SwizzleX::SwizzleIndex], v2[SwizzleY::SwizzleIndex], v2[SeizzleZ::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SeizzleZ>
	inline vec3 swizzle(const vec3& v3)
	{
		return vec3(v3[SwizzleX::SwizzleIndex], v3[SwizzleY::SwizzleIndex], v3[SeizzleZ::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SeizzleZ>
	inline vec3 swizzle(const vec4& v4)
	{
		return vec3(v4[SwizzleX::SwizzleIndex], v4[SwizzleY::SwizzleIndex], v4[SeizzleZ::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SeizzleZ, typename SwizzleW>
	inline vec4 swizzle(const vec2& v2)
	{
		return vec4(v2[SwizzleX::SwizzleIndex], v2[SwizzleY::SwizzleIndex], v2[SeizzleZ::SwizzleIndex], v2[SwizzleW::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SeizzleZ, typename SwizzleW>
	inline vec4 swizzle(const vec3& v3)
	{
		return vec4(v3[SwizzleX::SwizzleIndex], v3[SwizzleY::SwizzleIndex], v3[SeizzleZ::SwizzleIndex], v3[SwizzleW::SwizzleIndex]);
	}

	template<typename SwizzleX, typename SwizzleY, typename SeizzleZ, typename SwizzleW>
	inline vec4 swizzle(const vec4& v4)
	{
		return vec4(v4[SwizzleX::SwizzleIndex], v4[SwizzleY::SwizzleIndex], v4[SeizzleZ::SwizzleIndex], v4[SwizzleW::SwizzleIndex]);
	}
}