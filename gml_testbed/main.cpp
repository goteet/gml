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

DECL(Matrix22);
DECL(Matrix33);
DECL(Matrix44);
DECL(Quaternion);



#include <iomanip>

int main()
{
	USING(Matrix22);
	USING(Matrix33);
	USING(Matrix44);
	USING(Quaternion);

#ifndef WRITE_TO_FILE
	getchar();
#else
	if (OUTPUT) OUTPUT.close();
#endif

	return 0;
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