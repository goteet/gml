#include <gmlvector.h>
#include <gmlmatrix.h>
#include <gmlcolor.h>
#include <gmlutility.h>


#pragma comment(lib, "gml.lib")
using namespace gml;

void TestVector2();
void TestVector3();
void TestVector4();
void TestVeoctorSwizzle();
void TestMatrix22();
void TestMatrix33();
void TestMatrix44();
void TestColor();
void TestStructure();

//#define WRITE_TO_FILE
#ifndef WRITE_TO_FILE
#include <iostream>
#define OUTPUT std::cout
#else
#define WRITE_LOG_FILENAME "test_output.txt"
#include <fstream>
std::ofstream outFile(WRITE_LOG_FILENAME, std::ios_base::trunc);
#define OUTPUT outFile
#endif

#include <iomanip>

int main()
{
	OUTPUT << "# test structure \n";
	TestStructure();

	OUTPUT << "# test vector2 \n";
	TestVector2();

	OUTPUT << "# test vector3 \n";
	TestVector3();

	OUTPUT << "# test vector4 \n";
	TestVector4();

	OUTPUT << "# test vector swizzle \n";
	TestVeoctorSwizzle();

	OUTPUT << "# test matrix22 \n";
	TestMatrix22();

	OUTPUT << "# test matrix33 \n";
	TestMatrix33();

	OUTPUT << "# test matrix44 \n";
	TestMatrix44();

	OUTPUT << "# test color\n";
	TestColor();

#ifndef WRITE_TO_FILE
	getchar();
#else
	if (OUTPUT) OUTPUT.close();
#endif

	return 0;
}

void TestVector2()
{
	OUTPUT << "## constructor:" << std::endl;

	vec2 a;
	vec2 b(3, 4);
	vec2 c(vec2::one);
	vec2 d = vec2::left;

	OUTPUT << "\tvec2 a;              a=<" << a.x << "," << a.y << ">\n";
	OUTPUT << "\tvec2 b(3,4);         b=<" << b[0] << "," << b[1] << ">\n";
	OUTPUT << "\tvec2 c(vec2::one);   c=<" << c[0] << "," << c[1] << ">\n";
	OUTPUT << "\tvec2 d = vec2::left; d=<" << d.x << "," << d.y << ">\n" << std::endl;

	OUTPUT << "## operators override :" << std::endl;

	OUTPUT << "\t-b=<" << (-b)[0] << "," << (-b)[1] << ">\n";

	a = -b;
	OUTPUT << "\ta=b; a=<" << a[0] << "," << a[1] << ">\n";

	bool isEqual = (-d == vec2::right);
	OUTPUT << "\t(-d == vec2::right) is " << (isEqual ? "true" : "false") << "\n";

	isEqual = (-vec2::up != vec2::down);
	OUTPUT << "\t(-vec2::up != vec2::down) is " << (isEqual ? "true" : "false") << "\n";

	a = vec2::right + vec2::down;
	OUTPUT << "\tvec2::right + vec2::down = <" << a[0] << "," << a[1] << ">\n";

	OUTPUT << "## method:" << std::endl;

	OUTPUT << "  c = <" << c.x << "," << c.y << ">\n"
		<< "  b.length = " << b.length() << "\n"
		<< "  b.lengthsquare = " << b.length_sqr() << "\n";

	b.normalize();
	OUTPUT << "  normalized: " << b.length() << "\n\n";

	c = b.normalized() * 3.4f;
	b *= 3.4f;
	OUTPUT << "  b == c is " << ((c == b) ? "" : "not ") << "equal \n"
		<< "  b == vec2::one is " << ((vec2::one == b) ? "" : "not ") << "equal \n\n";


	a = vec2::one + vec2::left;
	OUTPUT << "  one + left = <" << a.x << "," << a.y << ">\n";
	a += vec2::one * vec2::right;
	OUTPUT << "  result += one * right = <" << a.x << "," << a.y << ">\n";

	a = b.inversed();
	OUTPUT << "  b = <" << a.x << "," << a.y << ">\n";

	OUTPUT << "  cross(b,b) = <" << cross(b, c) << ">\n";
	OUTPUT << "  cross(b,vec2::one) = <"
		<< cross(b, vec2::one) << ">\n"
		<< "  dot(b,c) = " << dot(b, c) << "\n\n";

	a = lerp(b, vec2::one, 0.5f);
	OUTPUT << "  lerp(b,vec2::one, 0.5f) = <" << a[0] << "," << a[1] << ">\n";
	a = lerp(b, vec2::one, 0.0f);
	OUTPUT << "  lerp(b,vec2::one, 0.0f) = <" << a[0] << "," << a[1] << ">\n";
	a = lerp(b, vec2::one, 1.0f);
	OUTPUT << "  lerp(b,vec2::one, 1.0f) = <" << a[0] << "," << a[1] << ">\n\n";


	a = max_combine(vec2(1, 2), vec2(3, 1));
	OUTPUT << "  max_combine(<1,2,3>, <3,2,1>) = <" << a[0] << "," << a[1] << ">\n\n";

	a = min_combine(vec2(1, 3), vec2(3, 2));
	OUTPUT << "  minx_combine(b,vec2::one, 1.0f) = <" << a[0] << "," << a[1] << ">\n\n";
}

void TestVector3()
{
	vec3 a = vec3::one;
	vec3 b(3, 4, 5);
	vec3 c;

	OUTPUT << "  c = <" << c.x << "," << c.y << "," << c.z << ">\n"
		<< "  b.length = " << b.length() << "\n"
		<< "  b.lengthsquare = " << b.length_sqr() << "\n";

	b.normalize();
	OUTPUT << "  normalized: " << b.length() << "\n\n";


	c = b.normalized() * 3.4f;
	b *= 3.4f;
	OUTPUT << "  b == c is " << ((c == b) ? "" : "not ") << "equal \n"
		<< "  b == vec3::one is " << ((vec3::one == b) ? "" : "not ") << "equal \n\n";

	a = vec3::one + vec3::left;
	OUTPUT << "  one + left = <" << a.x << "," << a.y << "," << a.z << ">\n";
	a += vec3::one * vec3::right;
	OUTPUT << "  result += one * right = <" << a.x << "," << a.y << "," << a.z << ">\n";

	a = b.inversed();
	OUTPUT << "  b = <" << a.x << "," << a.y << "," << a.z << ">\n";

	a = cross(b, c);
	OUTPUT << "  cross(b,b) = <" << a.x << "," << a.y << "," << a.z << ">\n";
	a = cross(b, vec3::one);
	OUTPUT << "  cross(b,vec3::one) = <" << a[0] << "," << a[1] << "," << a[2] << ">\n"
		<< "  dot(b,c) = " << dot(b, c) << "\n\n";

	a = lerp(b, vec3::one, 0.5f);
	OUTPUT << "  lerp(b,vec3::one, 0.5f) = <" << a[0] << "," << a[1] << "," << a[2] << ">\n";
	a = lerp(b, vec3::one, 0.0f);
	OUTPUT << "  lerp(b,vec3::one, 0.0f) = <" << a[0] << "," << a[1] << "," << a[2] << ">\n";
	a = lerp(b, vec3::one, 1.0f);
	OUTPUT << "  lerp(b,vec3::one, 1.0f) = <" << a[0] << "," << a[1] << "," << a[2] << ">\n\n";


	a = max_combine(vec3(1, 2, 3), vec3(3, 2, 1));
	OUTPUT << "  max_combine(<1,2,3>, <3,2,1>) = <" << a[0] << "," << a[1] << "," << a[2] << ">\n\n";

	a = min_combine(vec3(1, 2, 3), vec3(3, 2, 1));
	OUTPUT << "  minx_combine(b,vec3::one, 1.0f) = <" << a[0] << "," << a[1] << "," << a[2] << ">\n\n";
}

void TestVector4()
{

}

void TestVeoctorSwizzle()
{
	vec2 a, v2(2.1f, 2.2f);
	vec3 b, v3(3.1f, 3.2f, 3.3f);
	vec4 c, v4(4.1f, 4.2f, 4.3f, 4.4f);

	OUTPUT << "\tvec2 = <" << v2.x << ", " << v2.y << ">\n";
	OUTPUT << "\tvec3 = <" << v3.x << ", " << v3.y << ", " << v3.z << ">\n";
	OUTPUT << "\tvec4 = <" << v4.x << ", " << v4.y << ", " << v4.z << ", " << v4.w << ">\n";

	//a = vec3;
	a = vec2(v3);

	a = swizzle<Y, X>(v2);
	OUTPUT << "\tvec2.yx = <" << a.x << ", " << a.y << ">\n";
	a = swizzle<Y, Z>(v3);
	OUTPUT << "\tvec3.yz = <" << a.x << ", " << a.y << ">\n";
	a = swizzle<W, W>(v4);
	OUTPUT << "\tvec4.ww = <" << a.x << ", " << a.y << ">\n\n";

	//b = vec4;
	b = vec3(v4);

	b = swizzle<Y, X, Y>(v2);
	OUTPUT << "\tvec2.yxy = <" << b.x << ", " << b.y << ", " << b.z << ">\n";
	b = swizzle<Y, Z, X>(v3);
	OUTPUT << "\tvec3.yzx = <" << b.x << ", " << b.y << ", " << b.z << ">\n";
	b = swizzle<W, W, X>(v4);
	OUTPUT << "\tvec4.wwx = <" << b.x << ", " << b.y << ", " << b.z << ">\n\n";

	c = swizzle<Y, X, X, Y>(v2);
	OUTPUT << "\tvec2.yxxy = <" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ">\n";
	c = swizzle<Y, Z, X, Z>(v3);
	OUTPUT << "\tvec3.yzxz = <" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ">\n";
	c = swizzle<Z, Z, W, Y>(v4);
	OUTPUT << "\tvec4.zzwy = <" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ">\n\n";
}

void TestMatrix22()
{
	const float r = 0.5f;
	mat22 a(cos(r), -sin(r), sin(r), cos(r));
	mat22 b(a);

	OUTPUT << "  a = \n  |"
		<< a[0] << "," << a[1] << "|\n  |"
		<< a[2] << "," << a[3] << "| is"
		<< (a.is_orthogonal() ? " " : " not ")
		<< "orthogonal\n\n";

	a._11 += 20.0f;
	OUTPUT << "  a = \n  |"
		<< a[0] << "," << a[1] << "|\n  |"
		<< a[2] << "," << a[3] << "| is"
		<< (a.is_orthogonal() ? " " : " not ")
		<< "orthogonal\n\n";

	b = a;
	OUTPUT << "  a can"
		<< (a.invert() ? " " : " not ")
		<< "inverse.\n\n";


	OUTPUT << "  a.inv =\n  |"
		<< a[0] << "," << a[1] << "|\n  |"
		<< a[2] << "," << a[3] << "|\n\n";

	a = a * b;

	OUTPUT << "  a * b =\n"
		<< "  |"
		<< a[0] << "," << a[1] << "|\n  |"
		<< a[2] << "," << a[3] << "|\n\n";
}

void TestMatrix33()
{
	mat33 a(-4, -3, 3, 0, 2, -2, 1, 4, -1);
	mat33 b(a);

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "\n"
		<< a[3] << "," << a[4] << "," << a[5] << "\n"
		<< a[6] << "," << a[7] << "," << a[8] << "\n\n";

	//a.transpose();
	OUTPUT << "can inverse = " << a.invert() << "\n";

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "\n"
		<< a[3] << "," << a[4] << "," << a[5] << "\n"
		<< a[6] << "," << a[7] << "," << a[8] << "\n\n";

	a = a * b;

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "\n"
		<< a[3] << "," << a[4] << "," << a[5] << "\n"
		<< a[6] << "," << a[7] << "," << a[8] << "\n\n";
}

void TestMatrix44()
{
	mat44 a(-4, -3, 3, 0, 0, 2, -2, 0, 1, 4, -1, 0, 1, 2, 50, 1);
	mat44 b(a);

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "\n"
		<< a[4] << "," << a[5] << "," << a[6] << "," << a[7] << "\n"
		<< a[8] << "," << a[9] << "," << a[10] << "," << a[11] << "\n"
		<< a[12] << "," << a[13] << "," << a[14] << "," << a[15] << "\n\n";

	//a.transpose();
	OUTPUT << "can inverse = " << a.invert() << "\n";

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "\n"
		<< a[4] << "," << a[5] << "," << a[6] << "," << a[7] << "\n"
		<< a[8] << "," << a[9] << "," << a[10] << "," << a[11] << "\n"
		<< a[12] << "," << a[13] << "," << a[14] << "," << a[15] << "\n\n";

	a = a * b;

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "\n"
		<< a[4] << "," << a[5] << "," << a[6] << "," << a[7] << "\n"
		<< a[8] << "," << a[9] << "," << a[10] << "," << a[11] << "\n"
		<< a[12] << "," << a[13] << "," << a[14] << "," << a[15] << "\n\n";
}

void TestStructure()
{
	OUTPUT << "## structure size validation \n";
	OUTPUT << "\tsizeof(float)  = " << sizeof(float) << std::endl;
	OUTPUT << "\tsizeof(vec2)   = " << sizeof(vec2) << std::endl;
	OUTPUT << "\tsizeof(vec3)   = " << sizeof(vec3) << std::endl;
	OUTPUT << "\tsizeof(vec4)   = " << sizeof(vec4) << std::endl;
	OUTPUT << "\tsizeof(mat22)  = " << sizeof(mat22) << std::endl;
	OUTPUT << "\tsizeof(mat33)  = " << sizeof(mat33) << std::endl;
	OUTPUT << "\tsizeof(mat44)  = " << sizeof(mat44) << std::endl;
	OUTPUT << "\tsizeof(color_rgb)  = " << sizeof(color3) << std::endl;
	OUTPUT << "\tsizeof(color_rgba) = " << sizeof(color4) << std::endl << std::endl;

	OUTPUT << "## list initializer & union data validation" << std::endl;

	vec2 v2({ 1,2 });
	OUTPUT << "\tv2({1,2})    = <" << v2.x << "," << v2.y << ">" << std::endl;
	OUTPUT << "\tv2({1,2})    = <" << v2[0] << "," << v2[1] << ">" << std::endl;

	vec3 v3 = { 1,2,3 };
	OUTPUT << "\tv3={1,2,3}   = <" << v3.x << "," << v3.y << "," << v3.z << ">" << std::endl;
	OUTPUT << "\tv3={1,2,3}   = <" << v3[0] << "," << v3[1] << "," << v3[2] << ">" << std::endl;

	vec4 v4 = { 1,2,3,4 };
	OUTPUT << "\tv4={1,2,3,4} = <" << v4.x << "," << v4.y << "," << v4.z << "," << v4.w << ">" << std::endl;
	OUTPUT << "\tv4={1,2,3,4} = <" << v4[0] << "," << v4[1] << "," << v4[2] << "," << v4[3] << ">" << std::endl;

	mat22 m2 = { 1,2,3,4 };
	OUTPUT << "\tm2={1,2,3,4} = |" << m2._00 << "," << m2._01 << "," << m2._10 << "," << m2._11 << "|" << std::endl;
	OUTPUT << "\tm2={1,2,3,4} = |" << m2[0] << "," << m2[1] << "," << m2[2] << "," << m2[3] << "|" << std::endl;
	OUTPUT << "\tm2={1,2,3,4} = |" << m2.row[0].x << "," << m2.row[0].y << "," << m2.row[1].x << "," << m2.row[0].y << "|" << std::endl;

	mat33 m3 = { 1,2,3,4,5,6,7,8,9 };
	OUTPUT << "\tm3={ 1,2,3,4,5,6,7,8,9 } = |"
		<< m3._00 << "," << m3._01 << "," << m3._02 << ","
		<< m3._10 << "," << m3._11 << "," << m3._12 << ","
		<< m3._20 << "," << m3._21 << "," << m3._22 << "|"
		<< std::endl;
	OUTPUT << "\tm3={ 1,2,3,4,5,6,7,8,9 } = |"
		<< m3[0] << "," << m3[1] << "," << m3[2] << ","
		<< m3[3] << "," << m3[4] << "," << m3[5] << ","
		<< m3[6] << "," << m3[7] << "," << m3[8] << "|"
		<< std::endl;
	OUTPUT << "\tm3={ 1,2,3,4,5,6,7,8,9 } = |"
		<< m3.row[0].x << "," << m3.row[0][1] << "," << m3.row[0][2] << ","
		<< m3.row[1].x << "," << m3.row[1].y << "," << m3.row[1].z << ","
		<< m3.row[2].x << "," << m3.row[2].y << "," << m3.row[2].z << "|"
		<< std::endl;

	mat44 m4({ 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 });
	OUTPUT << "\tm4({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}) = |"
		<< m4._00 << "," << m4._01 << "," << m4._02 << "," << m4._03 << ","
		<< m4._10 << "," << m4._11 << "," << m4._12 << "," << m4._13 << ","
		<< m4._20 << "," << m4._21 << "," << m4._22 << "," << m4._23 << ","
		<< m4._30 << "," << m4._31 << "," << m4._32 << "," << m4._33 << "|"
		<< std::endl;
	OUTPUT << "\tm4({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}) = |"
		<< m4[0] << "," << m4[1] << "," << m4[2] << "," << m4[3] << ","
		<< m4[4] << "," << m4[5] << "," << m4[6] << "," << m4[7] << ","
		<< m4[8] << "," << m4[9] << "," << m4[10] << "," << m4[11] << ","
		<< m4[12] << "," << m4[13] << "," << m4[14] << "," << m4[15] << "|"
		<< std::endl;
	OUTPUT << "\tm4({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16}) = |"
		<< m4.row[0].x << "," << m4.row[0][1] << "," << m4.row[0][2] << "," << m4.row[0][3] << ","
		<< m4.row[1].x << "," << m4.row[1].y << "," << m4.row[1].z << "," << m4.row[1].w << ","
		<< m4.row[2].x << "," << m4.row[2].y << "," << m4.row[2].z << "," << m4.row[2].w << ","
		<< m4.row[3].x << "," << m4.row[3].y << "," << m4.row[3].z << "," << m4.row[3].w << "|"
		<< std::endl << std::endl;
}

void TestColor()
{
	color4 b = { color3::white, 1.0 };
}