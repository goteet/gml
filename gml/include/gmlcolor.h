#pragma once

namespace gml
{
	class color3;
	class color4;
	class color4;

	class color3
	{
	public:
		static const color3 black;
		static const color3 gray;
		static const color3 white;
		static const color3 red;
		static const color3 green;
		static const color3 blue;
		static const color3 yellow;
		static const color3 cyan;
		static const color3 purple;
		static color3 random();

	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;

	public:
		color3();

		color3(float r, float g, float b);

		explicit color3(const color4& c4);

		color3(unsigned int _rgb);

		bool operator==(const color3& rhs) const;

		bool operator!=(const color3& rhs) const;

		color3 operator+(float value) const;

		color3 operator*(float value) const;

		color3 operator+(const color3& rhs) const;

		color3 operator*(const color3& rhs) const;

		color3& operator+=(float value);

		color3& operator*=(float value);

		color3& operator+=(const color3& rhs);

		color3& operator*=(const color3& rhs);

		//hack
		float& operator[](int index);

		const float& operator[](int index) const;

		explicit operator float*();

		color3& set(float r, float g, float b);

		color3& set(const color4& c4);

		color3& clamp();

		color3 clamped() const;

		unsigned int to_rgb();		
	};

	class color4
	{
	public:
		static const color4 black;
		static const color4 gray;
		static const color4 white;
		static const color4 red;
		static const color4 green;
		static const color4 blue;
		static const color4 yellow;
		static const color4 cyan;
		static const color4 purple;
		static color4 random();

	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

	public:
		color4();

		color4(float r, float g, float b, float a);

		color4(const color3& c, float a);

		color4(unsigned int _rgba);

		bool operator==(const color4& rhs) const;

		bool operator!=(const color4& rhs) const;

		color4 operator+(float value) const;

		color4 operator*(float value) const;

		color4 operator+(const color4& rhs) const;

		color4 operator*(const color4& rhs) const;

		color4& operator+=(float value);

		color4& operator*=(float value);

		color4& operator+=(const color4& rhs);

		color4& operator*=(const color4& rhs);

		//hack
		float& operator[](int index);

		const float& operator[](int index) const;

		explicit operator float*();

		color4& set(float r, float g, float b, float a);

		color4& replace(const color3& c3);

		color4& clamp();

		color4 clamped() const;

		unsigned int to_rgba();
	};

	color3 operator+(float value, const color3& rhs);

	color3 operator*(float value, const color3& rhs);

	float dot(const color3& lhs, const color3& rhs);

	color4 operator+(float value, const color4& rhs);

	color4 operator*(float value, const color4& rhs);

	float dot(const color4& lhs, const color4& rhs);

	//swizzle
	typedef enum SWIZZLE_COLOR
	{
		R = 0, G = 1, B = 2, A = 3,
	} SWIZZLE_COLOR;

	template<SWIZZLE_COLOR SWIZZLE_X, SWIZZLE_COLOR SWIZZLE_Y, SWIZZLE_COLOR SWIZZLE_Z>
	inline color3 swizzle(const color3& c3)
	{
		return color3(c3[SWIZZLE_X], c3[SWIZZLE_Y], c3[SWIZZLE_Z]);
	}

	template<SWIZZLE_COLOR SWIZZLE_X, SWIZZLE_COLOR SWIZZLE_Y, SWIZZLE_COLOR SWIZZLE_Z>
	inline color3 swizzle(const color4& c4)
	{
		return color3(c4[SWIZZLE_X], c4[SWIZZLE_Y], c4[SWIZZLE_Z]);
	}

	template<SWIZZLE_COLOR SWIZZLE_X, SWIZZLE_COLOR SWIZZLE_Y, SWIZZLE_COLOR SWIZZLE_Z, SWIZZLE_COLOR SWIZZLE_W>
	inline color4 swizzle(const color3& c3)
	{
		return color4(c3[SWIZZLE_X], c3[SWIZZLE_Y], c3[SWIZZLE_Z], c3[SWIZZLE_W]);
	}

	template<SWIZZLE_COLOR SWIZZLE_X, SWIZZLE_COLOR SWIZZLE_Y, SWIZZLE_COLOR SWIZZLE_Z, SWIZZLE_COLOR SWIZZLE_W>
	inline color4 swizzle(const color4& c4)
	{
		return color4(c4[SWIZZLE_X], c4[SWIZZLE_Y], c4[SWIZZLE_Z], c4[SWIZZLE_W]);
	}
}