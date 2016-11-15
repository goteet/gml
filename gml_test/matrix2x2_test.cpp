#include "stdafx.h"

TEST_CLASS(Matrix2x2Test)
{
public:
	TEST_METHOD(Matrix2x2GenericTest)
	{
		GML_IEQUALM(sizeof(float) * 4, sizeof(mat22), "the struct of matrix2x2 is not the same as expected.");
	}

	mat22 memberByList = { 1,2,3,4 };
	mat22 memberByStaticFunc = mat22::scale(5.0f, 10.0f);

	TEST_METHOD(Matrix2x2IntializationTest)
	{
		GML_FEQUALM(5.0f, memberByStaticFunc._00, "member init by static function");
		GML_FEQUALM(10.0f, memberByStaticFunc._11, "member init by static function");
		GML_FEQUAL(0.0f, memberByStaticFunc._01);
		GML_FEQUAL(0.0f, memberByStaticFunc._10);

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
};