#include <gmlvector.h>
#include <gmlmatrix.h>
#include <gmlcolor.h>
#include <gmlutility.h>
#include <gmlrotation.h>
#include <gmlconversion.h>
#include <gmldualquat.h>

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

using namespace gml;

#define DECL(name) const char* Test##name##Title = "# test "#name" \n";void Test##name##Func();
#define USING(name) {OUTPUT <<Test##name##Title; Test##name##Func();  OUTPUT <<std::endl <<std::endl;}
#define IMPL(name) void Test##name##Func()

DECL(VectorSwizzle);
DECL(Matrix22);
DECL(Matrix33);
DECL(Matrix44);
DECL(Quaternion);
DECL(DualQuaternion);



#include <iomanip>

int main()
{
	USING(VectorSwizzle);
	USING(Matrix22);
	USING(Matrix33);
	USING(Matrix44);
	USING(Quaternion);
	USING(DualQuaternion);

#ifndef WRITE_TO_FILE
	getchar();
#else
	if (OUTPUT) OUTPUT.close();
#endif

	return 0;
}

IMPL(VectorSwizzle)
{
	vec2 a, v2(2.1f, 2.2f);
	vec3 b, v3(3.1f, 3.2f, 3.3f);
	vec4 c, v4(4.1f, 4.2f, 4.3f, 4.4f);

	OUTPUT << "\tvec2 = <" << v2.x << ", " << v2.y << ">\n";
	OUTPUT << "\tvec3 = <" << v3.x << ", " << v3.y << ", " << v3.z << ">\n";
	OUTPUT << "\tvec4 = <" << v4.x << ", " << v4.y << ", " << v4.z << ", " << v4.w << ">\n";

	//a = vec3;
	a = vec2(v3);

	a = swizzle<_Y, _X>(v2);
	OUTPUT << "\tvec2.yx = <" << a.x << ", " << a.y << ">\n";
	a = swizzle<_Y, _Z>(v3);
	OUTPUT << "\tvec3.yz = <" << a.x << ", " << a.y << ">\n";
	a = swizzle<_W, _W>(v4);
	OUTPUT << "\tvec4.ww = <" << a.x << ", " << a.y << ">\n\n";

	//b = vec4;
	b = vec3(v4);

	b = swizzle<_Y, _X, _Y>(v2);
	OUTPUT << "\tvec2.yxy = <" << b.x << ", " << b.y << ", " << b.z << ">\n";
	b = swizzle<_Y, _Z, _X>(v3);
	OUTPUT << "\tvec3.yzx = <" << b.x << ", " << b.y << ", " << b.z << ">\n";
	b = swizzle<_W, _W, _X>(v4);
	OUTPUT << "\tvec4.wwx = <" << b.x << ", " << b.y << ", " << b.z << ">\n\n";

	c = swizzle<_Y, _X, _X, _Y>(v2);
	OUTPUT << "\tvec2.yxxy = <" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ">\n";
	c = swizzle<_Y, _Z, _X, _Z>(v3);
	OUTPUT << "\tvec3.yzxz = <" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ">\n";
	c = swizzle<_Z, _Z, _W, _Y>(v4);
	OUTPUT << "\tvec4.zzwy = <" << c.x << ", " << c.y << ", " << c.z << ", " << c.w << ">\n\n";
}

IMPL(Matrix22)
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
		<< (a.can_invert() ? " " : " not ")
		<< "inverse.\n\n";

	a.inverse();
	OUTPUT << "  a.inv =\n  |"
		<< a[0] << "," << a[1] << "|\n  |"
		<< a[2] << "," << a[3] << "|\n\n";

	a = a * b;

	OUTPUT << "  a * b =\n"
		<< "  |"
		<< a[0] << "," << a[1] << "|\n  |"
		<< a[2] << "," << a[3] << "|\n\n";
}

IMPL(Matrix33)
{
	mat33 a(-4, -3, 3, 0, 2, -2, 1, 4, -1);
	mat33 b(a);

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "\n"
		<< a[3] << "," << a[4] << "," << a[5] << "\n"
		<< a[6] << "," << a[7] << "," << a[8] << "\n\n";

	//a.transpose();
	OUTPUT << "can inverse = " << a.can_invert() << "\n";

	a.inverse();
	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "\n"
		<< a[3] << "," << a[4] << "," << a[5] << "\n"
		<< a[6] << "," << a[7] << "," << a[8] << "\n\n";

	a = a * b;

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "\n"
		<< a[3] << "," << a[4] << "," << a[5] << "\n"
		<< a[6] << "," << a[7] << "," << a[8] << "\n\n";
}

IMPL(Matrix44)
{
	mat44 a(-4, -3, 3, 0, 0, 2, -2, 0, 1, 4, -1, 0, 1, 2, 50, 1);
	mat44 b(a);

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "\n"
		<< a[4] << "," << a[5] << "," << a[6] << "," << a[7] << "\n"
		<< a[8] << "," << a[9] << "," << a[10] << "," << a[11] << "\n"
		<< a[12] << "," << a[13] << "," << a[14] << "," << a[15] << "\n\n";

	//a.transpose();
	OUTPUT << "can inverse = " << a.can_invert() << "\n";

	a.inverse();
	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "\n"
		<< a[4] << "," << a[5] << "," << a[6] << "," << a[7] << "\n"
		<< a[8] << "," << a[9] << "," << a[10] << "," << a[11] << "\n"
		<< a[12] << "," << a[13] << "," << a[14] << "," << a[15] << "\n\n";

	a = a * b;

	OUTPUT << a[0] << "," << a[1] << "," << a[2] << "," << a[3] << "\n"
		<< a[4] << "," << a[5] << "," << a[6] << "," << a[7] << "\n"
		<< a[8] << "," << a[9] << "," << a[10] << "," << a[11] << "\n"
		<< a[12] << "," << a[13] << "," << a[14] << "," << a[15] << "\n\n";

	mat44 t = mat44::translate(1, 2, 3);
	vec3 p = transform_point(t, vec3::zero());
}


IMPL(Quaternion)
{
	gml::quat r1(vec3::right(), (gml::radian)gml::degree(90));
	gml::quat r2(vec3::left(), (gml::radian)gml::degree(90));
	gml::vec3 position(0, 0, 1);

	OUTPUT << "## slerp\n";
	for (int i = 0; i < 51; i++)
	{
		float k = i / 50.0f;
		gml::quat r = slerp(r1, r2, k);
		position = gml::rotate(r, vec3(0, 0, 1));
		OUTPUT << "k = " << k << " \t\t"
			<< "<" << position.x << ","
			<< position.y << ","
			<< position.z << "> \n";
	}

	OUTPUT << "\n## q1*q2 \n";
	r1 = quat(vec3::forward(), (gml::radian)gml::degree(90));
	r2 = quat(vec3::up(), (gml::radian)gml::degree(90));

	auto r = r1 * r2;
	position = gml::rotate(r, vec3(0, 0, 1));
	OUTPUT << "<" << position.x << ","
		<< position.y << ","
		<< position.z << "> \n";

	auto rmat = gml::to_mat44(r2);
	auto r2_ = gml::to_quat(rmat);
	position = transform_vector(rmat, vec3(0, 0, 1));
}

IMPL(DualQuaternion)
{
	gml::dquat trans(0, 1, 0);
	gml::dquat rot(vec3(0, 1, 0), (gml::radian)degree(180));
	gml::mat44 mTrans = to_mat44(trans);
	gml::mat44 mRotation = to_mat44(rot);

	auto rnt = trans*rot;
	auto tnr = rot*trans;

	gml::mat44 mTNR = to_mat44(tnr);
	gml::mat44 mRNT = to_mat44(rnt);
	gml::vec3 p(0, 0, 0);

	gml::vec3 tp = transform_point(mTrans, p);
	gml::vec3 rp = transform_point(mRotation, p);
	auto tret = gml::transform(trans, p);
	OUTPUT << "translate:<"
		<< tret.x << ","
		<< tret.y << ","
		<< tret.z << "> \n";


	tret = gml::transform(rot, p);
	OUTPUT << "rotate:<" << tret.x << ","
		<< tret.y << ","
		<< tret.z << "> \n";

	tret = gml::transform(rnt, p);
	OUTPUT << "rotate and translate:<" << tret.x << ","
		<< tret.y << ","
		<< tret.z << "> \n";
	tret = transform_point(mRNT, p);

	tret = gml::transform(tnr, p);
	OUTPUT << "translate and rotate:<" << tret.x << ","
		<< tret.y << ","
		<< tret.z << "> \n";
	tret = transform_point(mTNR, p);
}