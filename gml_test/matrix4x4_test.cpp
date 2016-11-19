#include "stdafx.h"

TEST_CLASS(Matrix4x4Test)
{
public:
	TEST_METHOD(Matrix4x4GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 4 * 4, sizeof(mat44));

		mat44 m44;
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 4; j++)
			{
				GML_FEQUAL(0.0f, m44.m[i][j]);
			}
		}
	}

	mat44 memberByStaticFunc = mat44::identity();
	mat44 memberByList = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };

	TEST_METHOD(Matrix4x4IntializationTest)
	{
		GML_FEQUALM(1.0f, memberByStaticFunc._00, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._01, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._02, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._03, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._10, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._11, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._12, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._13, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._20, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._21, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._22, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._23, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._30, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._31, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._32, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._33, "member init by static function");

		GML_FEQUALM(1.0f, memberByList._00, "member init by init-list");
		GML_FEQUALM(2.0f, memberByList._01, "member init by init-list");
		GML_FEQUALM(3.0f, memberByList._02, "member init by init-list");
		GML_FEQUALM(4.0f, memberByList._03, "member init by init-list");
		GML_FEQUALM(5.0f, memberByList._10, "member init by init-list");
		GML_FEQUALM(6.0f, memberByList._11, "member init by init-list");
		GML_FEQUALM(7.0f, memberByList._12, "member init by init-list");
		GML_FEQUALM(8.0f, memberByList._13, "member init by init-list");
		GML_FEQUALM(9.0f, memberByList._20, "member init by init-list");
		GML_FEQUALM(10.0f, memberByList._21, "member init by init-list");
		GML_FEQUALM(11.0f, memberByList._22, "member init by init-list");
		GML_FEQUALM(12.0f, memberByList._23, "member init by init-list");
		GML_FEQUALM(13.0f, memberByList._30, "member init by init-list");
		GML_FEQUALM(14.0f, memberByList._31, "member init by init-list");
		GML_FEQUALM(15.0f, memberByList._32, "member init by init-list");
		GML_FEQUALM(16.0f, memberByList._33, "member init by init-list");

		mat44 local = { 1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16 };
		GML_FEQUALM(1.0f, local._00, "local init by init-list");
		GML_FEQUALM(2.0f, local._01, "local init by init-list");
		GML_FEQUALM(3.0f, local._02, "local init by init-list");
		GML_FEQUALM(4.0f, local._03, "local init by init-list");
		GML_FEQUALM(5.0f, local._10, "local init by init-list");
		GML_FEQUALM(6.0f, local._11, "local init by init-list");
		GML_FEQUALM(7.0f, local._12, "local init by init-list");
		GML_FEQUALM(8.0f, local._13, "local init by init-list");
		GML_FEQUALM(9.0f, local._20, "local init by init-list");
		GML_FEQUALM(10.0f, local._21, "local init by init-list");
		GML_FEQUALM(11.0f, local._22, "local init by init-list");
		GML_FEQUALM(12.0f, local._23, "local init by init-list");
		GML_FEQUALM(13.0f, local._30, "local init by init-list");
		GML_FEQUALM(14.0f, local._31, "local init by init-list");
		GML_FEQUALM(15.0f, local._32, "local init by init-list");
		GML_FEQUALM(16.0f, local._33, "local init by init-list");

		mat44 m422(mat22(1, 2, 3, 4));
		GML_FEQUAL(1.0f, m422._00);
		GML_FEQUAL(2.0f, m422._01);
		GML_FEQUAL(0.0f, m422._02);
		GML_FEQUAL(0.0f, m422._03);
		GML_FEQUAL(3.0f, m422._10);
		GML_FEQUAL(4.0f, m422._11);
		GML_FEQUAL(0.0f, m422._12);
		GML_FEQUAL(0.0f, m422._13);
		GML_FEQUAL(0.0f, m422._20);
		GML_FEQUAL(0.0f, m422._21);
		GML_FEQUAL(1.0f, m422._22);
		GML_FEQUAL(0.0f, m422._23);
		GML_FEQUAL(0.0f, m422._30);
		GML_FEQUAL(0.0f, m422._31);
		GML_FEQUAL(0.0f, m422._32);
		GML_FEQUAL(1.0f, m422._33);

		mat44 m432(mat32(1, 2, 3, 4, 5, 6));
		GML_FEQUAL(1.0f, m432._00);
		GML_FEQUAL(2.0f, m432._01);
		GML_FEQUAL(0.0f, m432._02);
		GML_FEQUAL(3.0f, m432._03);
		GML_FEQUAL(4.0f, m432._10);
		GML_FEQUAL(5.0f, m432._11);
		GML_FEQUAL(0.0f, m432._12);
		GML_FEQUAL(6.0f, m432._13);
		GML_FEQUAL(0.0f, m432._20);
		GML_FEQUAL(0.0f, m432._21);
		GML_FEQUAL(1.0f, m432._22);
		GML_FEQUAL(0.0f, m432._23);
		GML_FEQUAL(0.0f, m432._30);
		GML_FEQUAL(0.0f, m432._31);
		GML_FEQUAL(0.0f, m432._32);
		GML_FEQUAL(1.0f, m432._33);

		mat44 m433(mat33(1, 2, 3, 4, 5, 6, 7, 8, 9));
		GML_FEQUAL(1.0f, m433._00);
		GML_FEQUAL(2.0f, m433._01);
		GML_FEQUAL(3.0f, m433._02);
		GML_FEQUAL(0.0f, m433._03);
		GML_FEQUAL(4.0f, m433._10);
		GML_FEQUAL(5.0f, m433._11);
		GML_FEQUAL(6.0f, m433._12);
		GML_FEQUAL(0.0f, m433._13);
		GML_FEQUAL(7.0f, m433._20);
		GML_FEQUAL(8.0f, m433._21);
		GML_FEQUAL(9.0f, m433._22);
		GML_FEQUAL(0.0f, m433._23);
		GML_FEQUAL(0.0f, m433._30);
		GML_FEQUAL(0.0f, m433._31);
		GML_FEQUAL(0.0f, m433._32);
		GML_FEQUAL(1.0f, m433._33);
	}

	TEST_METHOD(Matrix4x4AccessTest)
	{
		mat44 v = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
		GML_FEQUAL(v._00, memberByList[0]);
		GML_FEQUAL(v._01, memberByList[1]);
		GML_FEQUAL(v._02, memberByList[2]);
		GML_FEQUAL(v._03, memberByList[3]);
		GML_FEQUAL(v._10, memberByList[4]);
		GML_FEQUAL(v._11, memberByList[5]);
		GML_FEQUAL(v._12, memberByList[6]);
		GML_FEQUAL(v._13, memberByList[7]);
		GML_FEQUAL(v._20, memberByList[8]);
		GML_FEQUAL(v._21, memberByList[9]);
		GML_FEQUAL(v._22, memberByList[10]);
		GML_FEQUAL(v._23, memberByList[11]);
		GML_FEQUAL(v._30, memberByList[12]);
		GML_FEQUAL(v._31, memberByList[13]);
		GML_FEQUAL(v._32, memberByList[14]);
		GML_FEQUAL(v._33, memberByList[15]);

		GML_FEQUAL(v._00, v.row[0].x);
		GML_FEQUAL(v._01, v.row[0].y);
		GML_FEQUAL(v._02, v.row[0].z);
		GML_FEQUAL(v._03, v.row[0].w);
		GML_FEQUAL(v._10, v.row[1].x);
		GML_FEQUAL(v._11, v.row[1].y);
		GML_FEQUAL(v._12, v.row[1].z);
		GML_FEQUAL(v._13, v.row[1].w);
		GML_FEQUAL(v._20, v.row[2].x);
		GML_FEQUAL(v._21, v.row[2].y);
		GML_FEQUAL(v._22, v.row[2].z);
		GML_FEQUAL(v._23, v.row[2].w);
		GML_FEQUAL(v._30, v.row[3].x);
		GML_FEQUAL(v._31, v.row[3].y);
		GML_FEQUAL(v._32, v.row[3].z);
		GML_FEQUAL(v._33, v.row[3].w);
	}

	TEST_METHOD(Matrix4x4Orothogonal)
	{
		mat44 a = mat44::rotate_x(radian(0.5f));

		GML_IS_TRUE(a.is_orthogonal());
		GML_IS_TRUE(a.can_invert());

		a._11 += 20.0f;
		GML_IS_FALSE(a.is_orthogonal());
	}

	TEST_METHOD(Matrix4x4TransformTest)
	{
		vec3 p(1, 1, 1);

		auto pt = transform_point(mat44::scale(2), p);
		GML_IS_TRUE(vec3(2, 2, 2) == pt);

		pt = transform_point(mat44::flip_x(), pt);
		GML_IS_TRUE(vec3(-2, 2, 2) == pt);

		pt = transform_point(mat44::rotate_y(degree(180)), pt);
		GML_IS_TRUE(vec3(2, 2, -2) == pt);

		pt = transform_point(mat44::flip_y(), pt);
		GML_IS_TRUE(vec3(2, -2, -2) == pt);

		pt = transform_point(mat44::scale(0.5, 0.5, -0.5), pt);
		GML_IS_TRUE(vec3(1, -1, 1) == pt);

		pt = transform_point(mat44::flip_y(), pt);
		GML_IS_TRUE(vec3::one() == pt);

		pt = transform_point(mat44::translate(-1, -1, -1), pt);
		GML_IS_TRUE(vec3::zero() == pt);
	}
};