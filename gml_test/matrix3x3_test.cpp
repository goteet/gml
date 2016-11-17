#include "stdafx.h"

TEST_CLASS(Matrix3x3Test)
{
public:
	TEST_METHOD(Matrix3x3GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 3 * 3, sizeof(mat33));
	}

	mat33 memberByStaticFunc = mat33::identity();
	mat33 memberByList = { 1,2,3,4,5,6,7,8,9 };

	TEST_METHOD(Matrix3x3IntializationTest)
	{
		GML_FEQUALM(1.0f, memberByStaticFunc._00, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._01, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._02, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._10, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._11, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._12, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._20, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._21, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._22, "member init by static function");

		GML_FEQUALM(1.0f, memberByList._00, "member init by init-list");
		GML_FEQUALM(2.0f, memberByList._01, "member init by init-list");
		GML_FEQUALM(3.0f, memberByList._02, "member init by init-list");
		GML_FEQUALM(4.0f, memberByList._10, "member init by init-list");
		GML_FEQUALM(5.0f, memberByList._11, "member init by init-list");
		GML_FEQUALM(6.0f, memberByList._12, "member init by init-list");
		GML_FEQUALM(7.0f, memberByList._20, "member init by init-list");
		GML_FEQUALM(8.0f, memberByList._21, "member init by init-list");
		GML_FEQUALM(9.0f, memberByList._22, "member init by init-list");

		mat33 local = { 1,2,3,4,5,6,7,8,9 };
		GML_FEQUALM(1.0f, local._00, "local init by init-list");
		GML_FEQUALM(2.0f, local._01, "local init by init-list");
		GML_FEQUALM(3.0f, local._02, "local init by init-list");
		GML_FEQUALM(4.0f, local._10, "local init by init-list");
		GML_FEQUALM(5.0f, local._11, "local init by init-list");
		GML_FEQUALM(6.0f, local._12, "local init by init-list");
		GML_FEQUALM(7.0f, local._20, "local init by init-list");
		GML_FEQUALM(8.0f, local._21, "local init by init-list");
		GML_FEQUALM(9.0f, local._22, "local init by init-list");
	}

	TEST_METHOD(Matrix3x3AccessTest)
	{
		mat33 v = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
		GML_FEQUAL(v._00, v[0]);
		GML_FEQUAL(v._01, v[1]);
		GML_FEQUAL(v._02, v[2]);
		GML_FEQUAL(v._10, v[3]);
		GML_FEQUAL(v._11, v[4]);
		GML_FEQUAL(v._12, v[5]);
		GML_FEQUAL(v._20, v[6]);
		GML_FEQUAL(v._21, v[7]);
		GML_FEQUAL(v._22, v[8]);

		GML_FEQUAL(v._00, v.row[0].x);
		GML_FEQUAL(v._01, v.row[0].y);
		GML_FEQUAL(v._02, v.row[0].z);
		GML_FEQUAL(v._10, v.row[1].x);
		GML_FEQUAL(v._11, v.row[1].y);
		GML_FEQUAL(v._12, v.row[1].z);
		GML_FEQUAL(v._20, v.row[2].x);
		GML_FEQUAL(v._21, v.row[2].y);
		GML_FEQUAL(v._22, v.row[2].z);
	}

	TEST_METHOD(Matrix3x3Orothogonal)
	{
		mat33 a = mat33::rotate_x(radian(0.5f));

		GML_IS_TRUE(a.is_orthogonal());
		GML_IS_TRUE(a.can_invert());

		a._11 += 20.0f;
		GML_IS_FALSE(a.is_orthogonal());
	}

	TEST_METHOD(Matrix3x3TransformTest)
	{
		vec3 p(1, 1, 1);

		auto pt = mat33::scale(2) * p;
		GML_IS_TRUE(vec3(2, 2, 2) == pt);

		pt = mat33::flip_x() * pt;
		GML_IS_TRUE(vec3(-2, 2, 2) == pt);

		pt = mat33::rotate_y(degree(180)) * pt;
		GML_IS_TRUE(vec3(2, 2, -2) == pt);

		pt = mat33::flip_y() * pt;
		GML_IS_TRUE(vec3(2, -2, -2) == pt);

		pt = mat33::scale(0.5, 0.5, -0.5) * pt;
		GML_IS_TRUE(vec3(1, -1, 1) == pt);

		pt = mat33::flip_y() * pt;
		GML_IS_TRUE(vec3::one() == pt);
	}
};