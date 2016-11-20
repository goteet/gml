#include "stdafx.h"

TEST_CLASS(QuaternionTest)
{
public:
	TEST_METHOD(QuaternionMultipleTest)
	{
		quat q1 = quat(vec3::forward(), (gml::radian)gml::degree(90));
		quat q2 = quat(vec3::up(), (gml::radian)gml::degree(90));

		auto r = q1 * q2;
		auto rt = gml::rotate(r, vec3(0, 0, 1));
		auto r2 = gml::rotate(q2, vec3(0, 0, 1));
		auto r1 = gml::rotate(q1, r2);

		GML_FEQUAL(1, r2.x);
		GML_FEQUAL(0, r2.y);
		GML_FEQUAL(0, r2.z);

		GML_FEQUAL(0, r1.x);
		GML_FEQUAL(1, r1.y);
		GML_FEQUAL(0, r1.z);

		GML_FEQUAL(r1.x, rt.x);
		GML_FEQUAL(r1.y, rt.y);
		GML_FEQUAL(r1.z, rt.z);
	}


	TEST_METHOD(QuaternionMatrixConversionTest)
	{
		quat q1 = quat(vec3::forward(), (gml::radian)gml::degree(90));
		quat q2 = quat(vec3::up(), (gml::radian)gml::degree(90));
		auto r = q1 * q2;

		auto matrixR = gml::to_mat44_from(r);

		auto rq = gml::rotate(r, vec3(0, 0, 1));
		auto rm = gml::transform_point(matrixR, vec3(0, 0, 1));
		GML_IS_TRUE(rm == rq);

		auto rinv = gml::to_quat_from(matrixR);
		GML_IS_TRUE(r == rinv);

		rq = gml::rotate(rinv, vec3(0, 0, 1));
		GML_IS_TRUE(rm == rq);
	}

	TEST_METHOD(QuaternionSlerpTest)
	{
		gml::quat r1(vec3::right(), (gml::radian)gml::degree(90));
		gml::quat r2(vec3::left(), (gml::radian)gml::degree(90));
		gml::vec3 position(0, 0, 1);

		//slerp
		constexpr int step = 50;
		for (int i = 0; i <= step; i++)
		{
			float k = (float)i / step;
			gml::quat r = slerp(r1, r2, k);
			position = gml::rotate(r, vec3(0, 0, 1));

			auto d = degree(lerp(-90.0f, 90.0f, k));
			auto cosd = gml::cos(d);
			auto sind = gml::sin(d);

			GML_IS_TRUE(vec3(0, sind, cosd) == position);
		}
	}
};