cmake_minimum_required(VERSION 3.8)

set(GML_SOURCE_FILES
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlaabb.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlangle.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlcolor.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlconversion.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmldualquat.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlmatrix.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlray.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlrect.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlrotation.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlutility.h
	${CMAKE_CURRENT_SOURCE_DIR}/gml/gmlvector.h
)

add_library(gml INTERFACE)
target_include_directories(gml INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_sources(gml INTERFACE ${GML_SOURCE_FILES})