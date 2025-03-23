#pragma once

#include <iostream>

using namespace std;

struct punct3d
{
	float x, y, z;
};

struct punct2d
{
	float x, y;
};

struct mat3
{
	float info[3][3] = { 0 };
};

struct mat4
{
	float info[4][4] = { 0 };
};

struct Plane
{
	punct3d point;
	punct3d normal;
};

punct3d AddVector(punct3d input1, punct3d input2);

punct3d DifVector(punct3d input1, punct3d input2);

punct2d DifVector2d(punct2d input1, punct2d input2);

punct3d ProdVect_Const(punct3d vect, float scalar);

punct3d ProdVectMatrix(punct3d vect, mat3 matrix);

punct3d ProdVect4x4Matrix(punct3d vect, mat4 matrix);

mat3 ProdMat(mat3 input1, mat3 input2);

float DotProduct(punct3d input1, punct3d input2);

float LengthVector(punct3d input);

punct3d NormaliseVect(punct3d input);

punct3d CrossProduct(punct3d input1, punct3d input2);

float DistancePointPlane(Plane plane, punct3d point);

float DistanceTwoPoints(punct3d input1, punct3d input2);

punct3d IntersectionLinePlane(punct3d p, punct3d q, Plane plane);



