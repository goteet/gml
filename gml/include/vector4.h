#pragma once

namespace gml
{
	class vector3;
	class vector4
	{
	public:
		float x = 0.0f;
		float y = 0.0f;
		float z = 0.0f;
		float w = 0.0f;

		vector4(int) = delete;

		vector4();

		vector4(float x, float y, float z, float w);

		vector4(const vector4& rhs);

		vector4& operator=(const vector4& rhs);

		bool operator==(const vector4& other) const;

		bool operator!=(const vector4& other) const;

		//hack
		float& operator[](int index);

		const float& operator[](int index) const;

		explicit operator float*();

		vector4& set(float x, float y, float z, float w);

		vector4& replace(const vector3& vec);
	};

	float dot(const vector4& lhs, const vector4& rhs);
}