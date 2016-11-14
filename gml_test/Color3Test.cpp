#include "stdafx.h"

namespace gml
{
	TEST_CLASS(Color3Test)
	{
	public:

		TEST_METHOD(testColor3Initialization)
		{
			// color3()
			color3 c1;
			GML_FEQUAL(0.0f, c1.r);
			GML_FEQUAL(0.0f, c1.g);
			GML_FEQUAL(0.0f, c1.b);

			// color3(float, float, float)
			color3 c2(0.1f, 0.2f, 1.3f);
			GML_FEQUAL(0.1f, c2.r);
			GML_FEQUAL(0.2f, c2.g);
			GML_FEQUAL(1.3f, c2.b);

			// color3(color4)
			auto cccc = color4::red();
			color3 c3(cccc);
			GML_FEQUAL(1.0f, c3.r);
			GML_FEQUAL(0.0f, c3.g);
			GML_FEQUAL(0.0f, c3.b);

			// color3(unsigned int)
			color3 c4(0xFF00FFu);
			GML_FEQUAL(1.0f, c4.r);
			GML_FEQUAL(0.0f, c4.g);
			GML_FEQUAL(1.0f, c4.b);
		}

		TEST_METHOD(testColor3Constants)
		{
			const auto black = color3::black();
			GML_FEQUAL(0.0f, black.r);
			GML_FEQUAL(0.0f, black.g);
			GML_FEQUAL(0.0f, black.b);

			const auto gray = color3::gray();
			GML_FEQUAL(0.5f, gray.r);
			GML_FEQUAL(0.5f, gray.g);
			GML_FEQUAL(0.5f, gray.b);

			const auto white = color3::white();
			GML_FEQUAL(1.0f, white.r);
			GML_FEQUAL(1.0f, white.g);
			GML_FEQUAL(1.0f, white.b);

			const auto red = color3::red();
			GML_FEQUAL(1.0f, red.r);
			GML_FEQUAL(0.0f, red.g);
			GML_FEQUAL(0.0f, red.b);

			const auto green = color3::green();
			GML_FEQUAL(0.0f, green.r);
			GML_FEQUAL(1.0f, green.g);
			GML_FEQUAL(0.0f, green.b);

			const auto blue = color3::blue();
			GML_FEQUAL(0.0f, blue.r);
			GML_FEQUAL(0.0f, blue.g);
			GML_FEQUAL(1.0f, blue.b);

			const auto yellow = color3::yellow();
			GML_FEQUAL(1.0f, yellow.r);
			GML_FEQUAL(1.0f, yellow.g);
			GML_FEQUAL(0.0f, yellow.b);

			const auto cyan = color3::cyan();
			GML_FEQUAL(0.0f, cyan.r);
			GML_FEQUAL(1.0f, cyan.g);
			GML_FEQUAL(1.0f, cyan.b);

			const auto purple = color3::purple();
			GML_FEQUAL(1.0f, purple.r);
			GML_FEQUAL(0.0f, purple.g);
			GML_FEQUAL(1.0f, purple.b);
		}

		TEST_METHOD(testColor3Random)
		{
			auto c1 = color3::random();
			auto c2 = color3::random();

			GML_IS_FALSE(c1 == c2);
		}

		TEST_METHOD(testColor3Compare)
		{
			color3 c1(0.1f, 0.2f, 1.0f);
			color3 c2(0.1f, 0.2f, 1.0f);
			auto c3 = c1;
			color3 c4(0.1f, 0.1f, 0.1f);

			// operator==
			GML_IS_TRUE(c1 == c1);
			GML_IS_TRUE(c1 == c2);
			GML_IS_TRUE(c1 == c3);

			// opeartor!=
			GML_IS_TRUE(c1 != c4);
		}

		TEST_METHOD(testColor3Add)
		{
			color3 c1(0.1f, 0.1f, 0.1f);
			color3 c2(0.2f, 0.2f, 1.2f);
			float f = 0.5f;

			// operator+(float)
			auto a = c1 + f;
			GML_FEQUAL(0.6f, a.r);
			GML_FEQUAL(0.6f, a.g);
			GML_FEQUAL(0.6f, a.b);

			// operator+(color3)
			auto b = c1 + c2;
			GML_FEQUAL(0.3f, b.r);
			GML_FEQUAL(0.3f, b.g);
			GML_FEQUAL(1.3f, b.b);

			// operator+=(float)
			auto c = c1;
			c += f;
			GML_FEQUAL(0.6f, c.r);
			GML_FEQUAL(0.6f, c.g);
			GML_FEQUAL(0.6f, c.b);

			// operator+=(color3)
			auto d = c1;
			d += c2;
			GML_FEQUAL(0.3f, d.r);
			GML_FEQUAL(0.3f, d.g);
			GML_FEQUAL(1.3f, d.b);
		}

		TEST_METHOD(testColor3Multiply)
		{
			color3 c1(0.1f, 0.1f, 0.1f);
			color3 c2(0.2f, 0.2f, 1.2f);
			float f = 0.5f;

			// operator*(float)
			auto a = c1 * f;
			GML_FEQUAL(0.05f, a.r);
			GML_FEQUAL(0.05f, a.g);
			GML_FEQUAL(0.05f, a.b);

			// operator*(color3)
			auto b = c1 * c2;
			GML_FEQUAL(0.02f, b.r);
			GML_FEQUAL(0.02f, b.g);
			GML_FEQUAL(0.12f, b.b);

			// operator*=(float)
			auto c = c1;
			c *= f;
			GML_FEQUAL(0.05f, c.r);
			GML_FEQUAL(0.05f, c.g);
			GML_FEQUAL(0.05f, c.b);

			// operator*=(color3)
			auto d = c1;
			d *= c2;
			GML_FEQUAL(0.02f, d.r);
			GML_FEQUAL(0.02f, d.g);
			GML_FEQUAL(0.12f, d.b);
		}

		TEST_METHOD(testColor3Index)
		{
			// operator[]
			color3 c;
			c[0] = 0.2f;
			c[1] = 0.3f;
			c[2] = 0.5f;
			GML_FEQUAL(0.2f, c.r);
			GML_FEQUAL(c[0], c.r);
			GML_FEQUAL(0.3f, c.g);
			GML_FEQUAL(c[1], c.g);
			GML_FEQUAL(0.5f, c.b);
			GML_FEQUAL(c[2], c.b);
		}

		TEST_METHOD(testColor3ToPointer)
		{
			// float*
			color3 c(0.1f, 0.2f, 0.3f);
			float *fv = (float *)c;
			GML_FEQUAL(0.1f, fv[0]);
			GML_FEQUAL(0.2f, fv[1]);
			GML_FEQUAL(0.3f, fv[2]);
		}

		TEST_METHOD(testColor3Set)
		{
			color3 c1, c2;
			color4 cccc(0.1f, 0.2f, 0.3f, 0.4f);

			// set(float, float, float)
			c1.set(0.1f, 0.2f, 0.3f);
			GML_FEQUAL(0.1f, c1.r);
			GML_FEQUAL(0.2f, c1.g);
			GML_FEQUAL(0.3f, c1.b);

			// set(color4)
			c2.set(cccc);
			GML_FEQUAL(0.1f, c2.r);
			GML_FEQUAL(0.2f, c2.g);
			GML_FEQUAL(0.3f, c2.b);
		}

		TEST_METHOD(testColor3Rgba)
		{
			auto c1 = color3::red();
			auto c2 = color3::white();
			auto c3 = color3::black();

			GML_IEQUAL(0xFFFF0000u, c1.rgba());
			GML_IEQUAL(0xFFFFFFFFu, c2.rgba());
			GML_IEQUAL(0xFF000000u, c3.rgba());
		}

		TEST_METHOD(testColor3Bgra)
		{
			auto c1 = color3::red();
			auto c2 = color3::white();
			auto c3 = color3::black();

			GML_IEQUAL(0xFF0000FFu, c1.bgra());
			GML_IEQUAL(0xFFFFFFFFu, c2.rgba());
			GML_IEQUAL(0xFF000000u, c3.rgba());
		}
	};
}