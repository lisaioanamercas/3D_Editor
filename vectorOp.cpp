#include "VectorOp.h"

punct3d AddVector(punct3d input1, punct3d input2)
{
	punct3d rezultat;
	rezultat.x = input1.x + input2.x;
	rezultat.y = input1.y + input2.y;
	rezultat.z = input1.z + input2.z;

	return rezultat;
}

punct3d DifVector(punct3d input1, punct3d input2)
{
	punct3d rezultat;
	rezultat.x = input1.x - input2.x;
	rezultat.y = input1.y - input2.y;
	rezultat.z = input1.z - input2.z;

	return rezultat;
}

punct2d DifVector2d(punct2d input1, punct2d input2)
{
	punct2d rezultat;
	rezultat.x = input1.x - input2.x;
	rezultat.y = input1.y - input2.y;

	return rezultat;
}

punct3d ProdVect_Const(punct3d vect, float scalar)
{
	punct3d rezultat;
	rezultat.x = vect.x * scalar;
	rezultat.y = vect.y * scalar;
	rezultat.z = vect.z * scalar;

	return rezultat;
}

punct3d ProdVectMatrix(punct3d vect, mat3 matrix)
{
	punct3d rezultat;
	rezultat.x = vect.x * matrix.info[0][0] + vect.y * matrix.info[1][0] + vect.z * matrix.info[2][0];
	rezultat.y = vect.x * matrix.info[0][1] + vect.y * matrix.info[1][1] + vect.z * matrix.info[2][1];
	rezultat.z = vect.x * matrix.info[0][2] + vect.y * matrix.info[1][2] + vect.z * matrix.info[2][2];

	return rezultat;
}

mat3 ProdMat(mat3 input1, mat3 input2)
{
	mat3 rezultat = { 0 };

	for (int i = 0; i < 3; i++)
		for (int j = 0; j < 3; j++)
			for (int k = 0; k < 3; k++)
				rezultat.info[i][j] += input1.info[i][k] * input2.info[k][j];

	return rezultat;
}

float DotProduct(punct3d input1, punct3d input2)
{
	float rezultat = 0;

	rezultat = input1.x * input2.x + input1.y * input2.y + input1.z * input2.z;

	return rezultat;
}

float LengthVector(punct3d input)
{
	float rezultat;
	rezultat = sqrtf(DotProduct(input, input));

	return rezultat;
}

punct3d NormaliseVect(punct3d input)
{
	float coeff = LengthVector(input);
	punct3d rezultat;

	rezultat = input;
	rezultat.x /= coeff;
	rezultat.y /= coeff;
	rezultat.z /= coeff;

	return rezultat;
}

punct3d CrossProduct(punct3d input1, punct3d input2)
{
	punct3d rezultat;

	rezultat.x = input1.y * input2.z - input1.z * input2.y;
	rezultat.y = input1.z * input2.x - input1.x * input2.z;
	rezultat.z = input1.x * input2.y - input1.y * input2.x;

	return rezultat;
}

punct3d ProdVect4x4Matrix(punct3d vect, mat4 matrix)
{
	punct3d rezultat;

	rezultat.x = vect.x * matrix.info[0][0] + vect.y * matrix.info[1][0] + vect.z * matrix.info[2][0] + 1 * matrix.info[3][0];
	rezultat.y = vect.x * matrix.info[0][1] + vect.y * matrix.info[1][1] + vect.z * matrix.info[2][1] + 1 * matrix.info[3][1];
	rezultat.z = vect.x * matrix.info[0][2] + vect.y * matrix.info[1][2] + vect.z * matrix.info[2][2] + 1 * matrix.info[3][2];

	return rezultat;

}

float DistanceTwoPoints(punct3d input1, punct3d input2)
{
	float rezultat;

	rezultat = sqrtf((input2.x - input1.x) * (input2.x - input1.x) + (input2.y - input1.y) * (input2.y - input1.y) + (input2.z - input1.z) * (input2.z - input1.z));

	return rezultat;
}

float DistancePointPlane(Plane plane, punct3d point)
{
	float rezultat = DotProduct(plane.normal, DifVector(point, plane.point));

	return rezultat;
}

punct3d IntersectionLinePlane(punct3d p, punct3d q, Plane plane)
{
	plane.normal = NormaliseVect(plane.normal);

	float pd = -DotProduct(plane.normal, plane.point);
	float ad = DotProduct(p, plane.normal);
	float bd = DotProduct(q, plane.normal);

	float t = (-pd - ad) / (bd - ad);
	punct3d line = DifVector(q, p);
	punct3d intersect = ProdVect_Const(line, t);

	return AddVector(p, intersect);
}
