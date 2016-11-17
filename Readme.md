# gml
---
Short for Game Math Library, 'gml' is a simple, easy-to-use math library for game developing.
it provides most conceptural structures, such as 

* vector2, vector3, vector4.
* matrix2x2, matrix3x3, matrix3x2, matrix4x4.
* color3, color4
* eular, quaternion, dual quaternion.
* aabb3d, aabb2d
* int rect for 2d.
* ray for 3d.
* degree & radian.

and associated operations.

# HEADER-ONLY
---
'gml' is written in c++, and take advantage of c++ 11.
we are trying to keep the definition of each struct in singular files, so that gml can be easily copy and paste anywhere.

we are considering adding SIMD supported, and/or rewrite these classes in c++ temlate.
