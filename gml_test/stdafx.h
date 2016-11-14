// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

// ���� CppUnitTest ��ͷ�ļ�
#include "CppUnitTest.h"

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
#include <gmlvector.h>
#include <gmlmatrix.h>
#include <gmlrect.h>
#include <gmlcolor.h>
#include <gmlutility.h>
#include <gmlrotation.h>
#include <gmlconversion.h>
#include <gmldualquat.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace gml
{
	static const float EPSILON = std::numeric_limits<float>::epsilon();

	// Integer Equal Assert
#define GML_IEQUAL(expected, actual) \
	Assert::AreEqual(expected, actual, nullptr, LINE_INFO())

	// Float Equal Assert
#define GML_FEQUAL(expected, actual) \
	Assert::AreEqual((expected), (actual), EPSILON, nullptr, LINE_INFO())

	// True Assert
#define GML_IS_TRUE(cond) \
	Assert::IsTrue((cond), nullptr, LINE_INFO())

	// False Assert
#define GML_IS_FALSE(cond) \
	Assert::IsFalse((cond), nullptr, LINE_INFO());
}