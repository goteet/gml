// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//
#pragma once

// 包括 SDKDDKVer.h 将定义可用的最高版本的 Windows 平台。

// 如果要为以前的 Windows 平台生成应用程序，请包括 WinSDKVer.h，并将
// 将 _WIN32_WINNT 宏设置为要支持的平台，然后再包括 SDKDDKVer.h。
#include <SDKDDKVer.h>

// 用于 CppUnitTest 的头文件
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