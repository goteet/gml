// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//

#pragma once

#include "targetver.h"

// ���� CppUnitTest ��ͷ�ļ�
#include <CppUnitTest.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#include <gmlaabb.h>
#include <gmlangle.h>
#include <gmlcolor.h>
#include <gmlconversion.h>
#include <gmldualquat.h>
#include <gmlmatrix.h>
//#include <gmlray.h>
#include <gmlrect.h>
#include <gmlrotation.h>
#include <gmlutility.h>
#include <gmlvector.h>
using namespace gml;

static const float EPSILON = std::numeric_limits<float>::epsilon();

// Integer Equal Assert
#define GML_IEQUAL(expected, actual) \
	Assert::AreEqual(expected, actual, nullptr, LINE_INFO())
#define GML_IEQUALM(expected, actual, message) \
	Assert::AreEqual(expected, actual, #message, LINE_INFO())

// Float Equal Assert
#define GML_FEQUAL(expected, actual) \
	Assert::AreEqual((expected), (actual), EPSILON, nullptr, LINE_INFO())
#define GML_FEQUALM(expected, actual, message) \
	Assert::AreEqual((expected), (actual), EPSILON, #message, LINE_INFO())

// AB Assert
#define GML_IS_TRUE(cond) \
	Assert::IsTrue((cond), nullptr, LINE_INFO())
#define GML_IS_FALSE(cond) \
	Assert::IsFalse((cond), nullptr, LINE_INFO());
#define GML_IS_TRUEM(cond, message) \
	Assert::IsTrue((cond), #message, LINE_INFO())
#define GML_IS_FALSEM(cond, message) \
	Assert::IsFalse((cond), #message, LINE_INFO());