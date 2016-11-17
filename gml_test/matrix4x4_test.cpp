#include "stdafx.h"

TEST_CLASS(Matrix4x4Test)
{
public:
	TEST_METHOD(Matrix4x4GenericTest)
	{
		GML_IEQUAL(sizeof(float) * 4 * 4, sizeof(mat44));
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
	}
};