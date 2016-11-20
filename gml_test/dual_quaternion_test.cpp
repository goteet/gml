#include "stdafx.h"

TEST_CLASS(DualQuaternionTest)
{
public:
	TEST_METHOD(DualQuaternionGenericTest)
	{
		gml::dquat DualQualT(1, 0, 0);
		gml::dquat DualQuatR(vec3(0, 1, 0), (gml::radian)degree(90));
		gml::mat44 MatrixT = to_mat44_from(DualQualT);
		gml::mat44 MatrixR = to_mat44_from(DualQuatR);

		auto T_R = DualQualT * DualQuatR;
		auto R_T = DualQuatR * DualQualT;

		gml::mat44 MatrixR_T = to_mat44_from(R_T);
		gml::mat44 MatrixT_R = to_mat44_from(T_R);
		gml::vec3 p(0, 0, 0);

		gml::vec3 tp = transform_point(MatrixT, p);
		GML_FEQUAL(1, tp.x);
		GML_FEQUAL(0, tp.y);
		GML_FEQUAL(0, tp.z);

		auto tret = gml::transform(DualQualT, p);
		GML_FEQUAL(1, tret.x);
		GML_FEQUAL(0, tret.y);
		GML_FEQUAL(0, tret.z);

		gml::vec3 rp = transform_point(MatrixR, tp);
		GML_FEQUAL(0, rp.x);
		GML_FEQUAL(0, rp.y);
		GML_FEQUAL(-1, rp.z);

		tret = gml::transform(DualQuatR, tp);
		GML_FEQUAL(0, tret.x);
		GML_FEQUAL(0, tret.y);
		GML_FEQUAL(-1, tret.z);

		tret = gml::transform(T_R, p);
		GML_FEQUAL(1, tret.x);
		GML_FEQUAL(0, tret.y);
		GML_FEQUAL(0, tret.z);

		auto tretm = transform_point(MatrixT_R, p);
		GML_FEQUAL(tret.x, tretm.x);
		GML_FEQUAL(tret.y, tretm.y);
		GML_FEQUAL(tret.z, tretm.z);

		tret = gml::transform(R_T, p);
		GML_FEQUAL(0, tret.x);
		GML_FEQUAL(0, tret.y);
		GML_FEQUAL(-1, tret.z);

		tretm = transform_point(MatrixR_T, p);
		GML_FEQUAL(tret.x, tretm.x);
		GML_FEQUAL(tret.y, tretm.y);
		GML_FEQUAL(tret.z, tretm.z);
	}
};