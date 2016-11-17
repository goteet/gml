#include "stdafx.h"

TEST_CLASS(Matrix3x2Test)
{
public:
	TEST_METHOD(Matrix3x2GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 3 * 2, sizeof(mat32));
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
	}
};