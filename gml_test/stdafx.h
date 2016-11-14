// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

// 用于 CppUnitTest 的头文件
#include "CppUnitTest.h"

// TODO: 在此处引用程序需要的其他头文件
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