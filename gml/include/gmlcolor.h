#pragma once

namespace
{
	struct _R { constexpr static int SwizzleIndex = 0; };
	struct _G { constexpr static int SwizzleIndex = 1; };
	struct _B { constexpr static int SwizzleIndex = 2; };
	struct _A { constexpr static int SwizzleIndex = 3; };
}
namespace gml
{
	class color3;
	class color4;

	class color3
	{
	public:
		static const color3& black();
		static const color3& gray();
		static const color3& white();
		static const color3& red();
		static const color3& green();
		static const color3& blue();
		static const color3& yellow();
		static const color3& cyan();
		static const color3& purple();
		static color3 random();

	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;

	public:
		color3() = default;

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

		void set(float r, float g, float b);

		void set(const color4& c4);

		unsigned int rgba();

		unsigned int bgra();
	};

	class color4
	{
	public:
		static const color4& black();
		static const color4& gray();
		static const color4& white();
		static const color4& red();
		static const color4& green();
		static const color4& blue();
		static const color4& yellow();
		static const color4& cyan();
		static const color4& purple();
		static color4 random();

	public:
		float r = 0.0f;
		float g = 0.0f;
		float b = 0.0f;
		float a = 1.0f;

	public:
		color4() = default;

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

		void set(float r, float g, float b, float a);

		void replace(const color3& c3);

		unsigned int rgba();

		unsigned int bgra();
	};

	color3 operator+(float value, const color3& rhs);

	color3 operator*(float value, const color3& rhs);

	float dot(const color3& lhs, const color3& rhs);

	color4 operator+(float value, const color4& rhs);

	color4 operator*(float value, const color4& rhs);

	float dot(const color4& lhs, const color4& rhs);

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB>
	inline color3 swizzle(const color3& c3)
	{
		return color3(c3[SwizzleR::SwizzleIndex], c3[SwizzleG::SwizzleIndex], c3[SwizzleB::SwizzleIndex]);
	}

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB>
	inline color3 swizzle(const color4& c4)
	{
		return color3(c4[SwizzleR::SwizzleIndex], c4[SwizzleG::SwizzleIndex], c4[SwizzleB::SwizzleIndex]);
	}

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB, typename SwizzleA>
	inline color4 swizzle(const color3& c3)
	{
		return color4(c3[SwizzleR::SwizzleIndex], c3[SwizzleG::SwizzleIndex], c3[SwizzleB::SwizzleIndex], c3[SwizzleA::SwizzleIndex]);
	}

	template<typename SwizzleR, typename SwizzleG, typename SwizzleB, typename SwizzleA>
	inline color4 swizzle(const color4& c4)
	{
		return color4(c4[SwizzleR::SwizzleIndex], c4[SwizzleG::SwizzleIndex], c4[SwizzleB::SwizzleIndex], c4[SwizzleA::SwizzleIndex]);
	}
}