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
};