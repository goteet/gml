// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
//
#pragma once

// ���� SDKDDKVer.h ��������õ���߰汾�� Windows ƽ̨��

// ���ҪΪ��ǰ�� Windows ƽ̨����Ӧ�ó�������� WinSDKVer.h������
// �� _WIN32_WINNT ������ΪҪ֧�ֵ�ƽ̨��Ȼ���ٰ��� SDKDDKVer.h��
#include <SDKDDKVer.h>

// ���� CppUnitTest ��ͷ�ļ�
#include <CppUnitTest.h>
using namespace Microsoft::VisualStudio::CppUnitTestFramework;


#include <gml/gmlaabb.h>
#include <gml/gmlangle.h>
#include <gml/gmlcolor.h>
#include <gml/gmlconversion.h>
#include <gml/gmldualquat.h>
#include <gml/gmlmatrix.h>
#include <gml/gmlray.h>
#include <gml/gmlrect.h>
#include <gml/gmlrotation.h>
#include <gml/gmlutility.h>
#include <gml/gmlvector.h>
using namespace gml;

static const float EPSILON = std::numeric_limits<float>::epsilon();

// Integer Equal Assert
#define GML_IEQUAL(expected, actual) \
	Assert::AreEqual(expected, actual, nullptr, LINE_INFO())
#define GML_IEQUALM(expected, actual, message) \
	Assert::AreEqual(expected, actual, L#message, LINE_INFO())

// Float Equal Assert
#define GML_FEQUAL(expected, actual) \
	Assert::AreEqual((expected), (actual), EPSILON, nullptr, LINE_INFO())
#define GML_FEQUALM(expected, actual, message) \
	Assert::AreEqual((expected), (actual), EPSILON, L#message, LINE_INFO())

// AB Assert
#define GML_IS_TRUE(cond) \
	Assert::IsTrue((cond), nullptr, LINE_INFO())
#define GML_IS_FALSE(cond) \
	Assert::IsFalse((cond), nullptr, LINE_INFO());
#define GML_IS_TRUEM(cond, message) \
	Assert::IsTrue((cond), L#message, LINE_INFO())
#define GML_IS_FALSEM(cond, message) \
	Assert::IsFalse((cond), L#message, LINE_INFO());