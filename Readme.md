# gml

Short for Game Math Library, 'gml' is a simple, easy-to-use math library for game developing.

the library provides some useful classes and associated operations, such as 

* vector2, vector3, vector4.
* matrix2x2, matrix3x3, matrix3x2, matrix4x4.
* color3, color4
* eular, quaternion, dual quaternion.
* aabb3d, aabb2d
* int rect for 2d.
* ray for 3d.
* degree & radian.

so that people can use them with grapic API in their own program.

'gml' is written in c++, and take the advantage of c++ 11.
now the library is HEAD-ONLY, we are trying to keep the definition of each class in one singular head file.

next, we are considering supprting SIMD.
