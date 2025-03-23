#include "ObjTransform.h"

void translateSelectedObj(Engine& currentEngine, punct3d translation)
{
	int selectedObj = currentEngine.eSelectedObj;
	int nrOfPts = currentEngine.eObjects[selectedObj].nrOfPoints;

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x += translation.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y += translation.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z += translation.z;
	}

	currentEngine.eObjects[selectedObj].objOrigin.x += translation.x;
	currentEngine.eObjects[selectedObj].objOrigin.y += translation.y;
	currentEngine.eObjects[selectedObj].objOrigin.z += translation.z;
}

void xRotateSelectedObj(Engine& currentEngine, float angle)
{
	int selectedObj = currentEngine.eSelectedObj;
	int nrOfPts = currentEngine.eObjects[selectedObj].nrOfPoints;
	punct3d origin = currentEngine.eObjects[selectedObj].objOrigin;

	mat3 xRotMat;
	xRotMat.info[0][0] = 1;
	xRotMat.info[1][1] = cos(angle);
	xRotMat.info[1][2] = -sin(angle);
	xRotMat.info[2][1] = sin(angle);
	xRotMat.info[2][2] = cos(angle);

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x -= origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y -= origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z -= origin.z;
	}

	for (int i = 0; i < nrOfPts; i++)
		currentEngine.eObjects[selectedObj].worldViewPoints[i] = ProdVectMatrix(currentEngine.eObjects[selectedObj].worldViewPoints[i], xRotMat);

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x += origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y += origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z += origin.z;
	}
}

void yRotateSelectedObj(Engine& currentEngine, float angle)
{
	int selectedObj = currentEngine.eSelectedObj;
	int nrOfPts = currentEngine.eObjects[selectedObj].nrOfPoints;
	punct3d origin = currentEngine.eObjects[selectedObj].objOrigin;

	mat3 yRotMat;
	yRotMat.info[0][0] = cos(angle);
	yRotMat.info[0][2] = sin(angle);
	yRotMat.info[1][1] = 1;
	yRotMat.info[2][0] = -sin(angle);
	yRotMat.info[2][2] = cos(angle);

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x -= origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y -= origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z -= origin.z;
	}

	for (int i = 0; i < nrOfPts; i++)
		currentEngine.eObjects[selectedObj].worldViewPoints[i] = ProdVectMatrix(currentEngine.eObjects[selectedObj].worldViewPoints[i], yRotMat);

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x += origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y += origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z += origin.z;
	}
}

void zRotateSelectedObj(Engine& currentEngine, float angle)
{
	int selectedObj = currentEngine.eSelectedObj;
	int nrOfPts = currentEngine.eObjects[selectedObj].nrOfPoints;
	punct3d origin = currentEngine.eObjects[selectedObj].objOrigin;

	mat3 zRotMat;
	zRotMat.info[0][0] = cos(angle);
	zRotMat.info[0][1] = -sin(angle);
	zRotMat.info[1][0] = sin(angle);
	zRotMat.info[1][1] = cos(angle);
	zRotMat.info[2][2] = 1;

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x -= origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y -= origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z -= origin.z;
	}

	for (int i = 0; i < nrOfPts; i++)
		currentEngine.eObjects[selectedObj].worldViewPoints[i] = ProdVectMatrix(currentEngine.eObjects[selectedObj].worldViewPoints[i], zRotMat);

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x += origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y += origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z += origin.z;
	}
}

void resizeSelectedObj(Engine& currentEngine, float factor)
{
	int selectedObj = currentEngine.eSelectedObj;
	int nrOfPts = currentEngine.eObjects[selectedObj].nrOfPoints;
	punct3d origin = currentEngine.eObjects[selectedObj].objOrigin;

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x -= origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y -= origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z -= origin.z;
	}

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x *= factor;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y *= factor;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z *= factor;
	}

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[selectedObj].worldViewPoints[i].x += origin.x;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].y += origin.y;
		currentEngine.eObjects[selectedObj].worldViewPoints[i].z += origin.z;
	}
}

punct3d axisRotate(punct3d input, float angle, punct3d axis)
{
	punct3d rezultat;

	mat3 RotMat;
	RotMat.info[0][0] = cos(angle) + axis.x * axis.x * (1 - cos(angle));
	RotMat.info[0][1] = axis.x * axis.y * (1 - cos(angle)) - axis.z * sin(angle);
	RotMat.info[0][2] = axis.x * axis.z * (1 - cos(angle)) + axis.y * sin(angle);
	RotMat.info[1][0] = axis.y * axis.x * (1 - cos(angle)) + axis.z * sin(angle);
	RotMat.info[1][1] = cos(angle) + axis.y * axis.y * (1 - cos(angle));
	RotMat.info[1][2] = axis.y * axis.z * (1 - cos(angle)) - axis.x * sin(angle);
	RotMat.info[2][0] = axis.z * axis.x * (1 - cos(angle)) - axis.y * sin(angle);
	RotMat.info[2][1] = axis.z * axis.y * (1 - cos(angle)) + axis.x * sin(angle);
	RotMat.info[2][2] = cos(angle) + axis.z * axis.z * (1 - cos(angle));

	rezultat = ProdVectMatrix(input, RotMat);

	return rezultat;
}

void translateObj(Engine& currentEngine, unsigned index, punct3d translation)
{
	int nrOfPts = currentEngine.eObjects[index].nrOfPoints;

	for (int i = 0; i < nrOfPts; i++)
	{
		currentEngine.eObjects[index].worldViewPoints[i].x += translation.x;
		currentEngine.eObjects[index].worldViewPoints[i].y += translation.y;
		currentEngine.eObjects[index].worldViewPoints[i].z += translation.z;
	}

	currentEngine.eObjects[index].objOrigin.x += translation.x;
	currentEngine.eObjects[index].objOrigin.y += translation.y;
	currentEngine.eObjects[index].objOrigin.z += translation.z;

}

void rotateObj(Engine& currentEngine, unsigned index, float angle, punct3d axis)
{
	int nrOfPts = currentEngine.eObjects[index].nrOfPoints;
	for (int i = 0; i < nrOfPts; i++)
		currentEngine.eObjects[index].worldViewPoints[i] = axisRotate(currentEngine.eObjects[index].worldViewPoints[i], angle, axis);

	currentEngine.eObjects[index].objOrigin = axisRotate(currentEngine.eObjects[index].objOrigin, angle, axis);
}
