#include "stdafx.h"

TEST_CLASS(Matrix2x2Test)
{
public:
	TEST_METHOD(Matrix2x2GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 2 * 2, sizeof(mat22));

		mat22 m22;
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				GML_FEQUAL(0.0f, m22.m[i][j]);
			}
		}
	}

	mat22 memberByStaticFunc = mat22::identity();
	mat22 memberByList = { 1,2,3,4 };

	TEST_METHOD(Matrix2x2IntializationTest)
	{
		GML_FEQUALM(1.0f, memberByStaticFunc._00, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._01, "member init by static function");
		GML_FEQUALM(0.0f, memberByStaticFunc._10, "member init by static function");
		GML_FEQUALM(1.0f, memberByStaticFunc._11, "member init by static function");

		GML_FEQUALM(1.0f, memberByList._00, "member init by init-list");
		GML_FEQUALM(2.0f, memberByList._01, "member init by init-list");
		GML_FEQUALM(3.0f, memberByList._10, "member init by init-list");
		GML_FEQUALM(4.0f, memberByList._11, "member init by init-list");

		mat22 local = { 5,6,7,8 };
		GML_FEQUALM(5.0f, local._00, "local init by init-list");
		GML_FEQUALM(6.0f, local._01, "local init by init-list");
		GML_FEQUALM(7.0f, local._10, "local init by init-list");
		GML_FEQUALM(8.0f, local._11, "local init by init-list");
	}

	TEST_METHOD(Matrix2x2AccessTest)
	{
		mat22 v = { 1, 2, 3, 4 };
		GML_FEQUAL(v._00, v[0]);
		GML_FEQUAL(v._01, v[1]);
		GML_FEQUAL(v._10, v[2]);
		GML_FEQUAL(v._11, v[3]);

		GML_FEQUAL(v._00, v.row[0].x);
		GML_FEQUAL(v._01, v.row[0].y);
		GML_FEQUAL(v._10, v.row[1].x);
		GML_FEQUAL(v._11, v.row[1].y);
	}

	TEST_METHOD(Matrix2x2OpeartionsTest)
	{
		auto rotMatrixP = mat22::rotate((radian)degree(90));
		auto rotMatrixN = mat22::rotate((radian)degree(-90));
		vec2 v(1.0f, 0.0f);
		vec2 vtp = rotMatrixP * v;
		vec2 vtn = rotMatrixN * v;

		GML_FEQUALM(0.0f, vtp.x, "mat22::rotation is wrong");
		GML_FEQUALM(1.0f, vtp.y, "mat22::rotation is wrong");

		GML_FEQUALM(0.0f, vtn.x, "mat22::rotation is wrong");
		GML_FEQUALM(-1.0f, vtn.y, "mat22::rotation is wrong");
	}

	TEST_METHOD(Matrix2x2Orothogonal)
	{
		mat22 a = mat22::rotate(radian(0.5f));

		GML_IS_TRUE(a.is_orthogonal());
		GML_IS_TRUE(a.can_invert());

		a._11 += 20.0f;
		GML_IS_FALSE(a.is_orthogonal());


		//a._11 = 0.0f;
		//GML_IS_FALSE(a.can_invert());
		//radian r(0.5f);
		//mat22::rotate(r);
		//a = a * b;
		//a.inverse();
	}

	TEST_METHOD(Matrix2x2TransformTest)
	{
		vec2 p(1, 0);

		auto pt = mat22::scale(2) * p;
		GML_IS_TRUE(vec2(2, 0) == pt);

		pt = mat22::flip_x() * pt;
		GML_IS_TRUE(vec2(-2, 0) == pt);

		pt = mat22::rotate(degree(90)) * pt;
		GML_IS_TRUE(vec2(0, -2) == pt);

		pt = mat22::flip_y() * pt;
		GML_IS_TRUE(vec2(0, 2) == pt);
		pt.x = 2;

		pt = mat22::scale(0.5, 0.5) * pt;
		GML_IS_TRUE(vec2(1, 1) == pt);
	}
};