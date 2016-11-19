#include "stdafx.h"

TEST_CLASS(Matrix3x2Test)
{
public:
	TEST_METHOD(Matrix3x2GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 3 * 2, sizeof(mat32));

		mat32 m32;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 3; j++)
			{
				GML_FEQUAL(0.0f, m32.m[i][j]);
			}
		}
	}

	mat32 memberByStaticFunc = mat32::identity();
	mat32 memberByList = { 1,2,3,4,5,6 };

	TEST_METHOD(Matrix3x2IntializationTest)
	{
		GML_FEQUALM(1.0f, memberByStaticFunc._00, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._01, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._02, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._10, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._11, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._12, "member init by static function");

		GML_FEQUALM(1.0f, memberByList._00, "member init by init-list");
		GML_FEQUALM(2.0f, memberByList._01, "member init by init-list");
		GML_FEQUALM(3.0f, memberByList._02, "member init by init-list");
		GML_FEQUALM(4.0f, memberByList._10, "member init by init-list");
		GML_FEQUALM(5.0f, memberByList._11, "member init by init-list");
		GML_FEQUALM(6.0f, memberByList._12, "member init by init-list");

		mat32 local = { 1,2,3,4,5,6 };
		GML_FEQUALM(1.0f, local._00, "local init by init-list");
		GML_FEQUALM(2.0f, local._01, "local init by init-list");
		GML_FEQUALM(3.0f, local._02, "local init by init-list");
		GML_FEQUALM(4.0f, local._10, "local init by init-list");
		GML_FEQUALM(5.0f, local._11, "local init by init-list");
		GML_FEQUALM(6.0f, local._12, "local init by init-list");

		mat32 m3(mat22(1, 2, 3, 4));
		GML_FEQUAL(1.0f, m3._00);
		GML_FEQUAL(2.0f, m3._01);
		GML_FEQUAL(0.0f, m3._02);
		GML_FEQUAL(3.0f, m3._10);
		GML_FEQUAL(4.0f, m3._11);
		GML_FEQUAL(0.0f, m3._12);
	}

	TEST_METHOD(Matrix3x2AccessTest)
	{
		mat32 v = { 1, 2, 3, 4, 5, 6 };
		GML_FEQUAL(v._00, v[0]);
		GML_FEQUAL(v._01, v[1]);
		GML_FEQUAL(v._02, v[2]);
		GML_FEQUAL(v._10, v[3]);
		GML_FEQUAL(v._11, v[4]);
		GML_FEQUAL(v._12, v[5]);

		GML_FEQUAL(v._00, v.row[0].x);
		GML_FEQUAL(v._01, v.row[0].y);
		GML_FEQUAL(v._02, v.row[0].z);
		GML_FEQUAL(v._10, v.row[1].x);
		GML_FEQUAL(v._11, v.row[1].y);
		GML_FEQUAL(v._12, v.row[1].z);
	}

	TEST_METHOD(Matrix3x2TransformTest)
	{
		vec2 p(1, 0);

		auto pt = transform_point(mat32::scale(2), p);
		GML_IS_TRUE(vec2(2, 0) == pt);

		pt = transform_point(mat32::flip_x(), pt);
		GML_IS_TRUE(vec2(-2, 0) == pt);

		pt = transform_point(mat32::rotate(degree(90)), pt);
		GML_IS_TRUE(vec2(0, -2) == pt);

		pt = transform_point(mat32::flip_y(), pt);
		GML_IS_TRUE(vec2(0, 2) == pt);
		pt.x = 2;

		pt = transform_point(mat32::scale(0.5, 0.5), pt);
		GML_IS_TRUE(vec2(1, 1) == pt);
	}
};