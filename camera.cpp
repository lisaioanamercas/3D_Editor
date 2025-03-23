#include "Camera.h"

mat4 matPointAt(punct3d position, punct3d target, punct3d up)
{
	punct3d currentForward = DifVector(target, position);
	currentForward = NormaliseVect(currentForward);

	punct3d currentRight = CrossProduct(currentForward, up);
	currentRight = NormaliseVect(currentRight);

	punct3d currentUp = CrossProduct(currentRight, currentForward);
	currentUp = NormaliseVect(currentUp);

	/*punct3d temp = ProdVect_Const(currentForward, DotProduct(up, currentForward));
	punct3d	currentUp = DifVector(up, temp);
	currentUp = NormaliseVect(currentUp);

	punct3d currentRight = CrossProduct(currentUp, currentForward);*/

	mat4 rezultat;

	rezultat.info[0][0] = currentRight.x;
	rezultat.info[0][1] = currentRight.y;
	rezultat.info[0][2] = currentRight.z;
	rezultat.info[0][3] = 0;

	rezultat.info[1][0] = currentUp.x;
	rezultat.info[1][1] = currentUp.y;
	rezultat.info[1][2] = currentUp.z;
	rezultat.info[1][3] = 0;

	rezultat.info[2][0] = currentForward.x;
	rezultat.info[2][1] = currentForward.y;
	rezultat.info[2][2] = currentForward.z;
	rezultat.info[2][3] = 0;

	rezultat.info[3][0] = position.x;
	rezultat.info[3][1] = position.y;
	rezultat.info[3][2] = position.z;
	rezultat.info[3][3] = 1;

	return rezultat;
}

mat4 matLookAt(mat4 matrix)
{
	mat4 rezultat;

	rezultat.info[0][0] = matrix.info[0][0]; rezultat.info[0][1] = matrix.info[1][0]; rezultat.info[0][2] = matrix.info[2][0]; rezultat.info[0][3] = 0;
	rezultat.info[1][0] = matrix.info[0][1]; rezultat.info[1][1] = matrix.info[1][1]; rezultat.info[1][2] = matrix.info[2][1]; rezultat.info[1][3] = 0;
	rezultat.info[2][0] = matrix.info[0][2]; rezultat.info[2][1] = matrix.info[1][2]; rezultat.info[2][2] = matrix.info[2][2]; rezultat.info[2][3] = 0;
	rezultat.info[3][0] = -(matrix.info[3][0] * rezultat.info[0][0] + matrix.info[3][1] * rezultat.info[1][0] + matrix.info[3][2] * rezultat.info[2][0]);
	rezultat.info[3][1] = -(matrix.info[3][0] * rezultat.info[0][1] + matrix.info[3][1] * rezultat.info[1][1] + matrix.info[3][2] * rezultat.info[2][1]);
	rezultat.info[3][2] = -(matrix.info[3][0] * rezultat.info[0][2] + matrix.info[3][1] * rezultat.info[1][2] + matrix.info[3][2] * rezultat.info[2][2]);
	rezultat.info[3][3] = 1;

	return rezultat;
}

bool isInsideView(Engine& currentEngine, punct3d point)
{
	for (int i = 0; i < 5; i++)
	{
		Plane currentPlane = currentEngine.eClippingPlanes[i];
		if (DistancePointPlane(currentPlane, point) < 0)
			return false;
	}

	return true;
}

punct3d clipAgainstPlanes(Engine& currentEngine, punct3d p, punct3d q)
{
	punct3d rezultat = p;
	for (int i = 0; i < 5; i++)
	{
		Plane currentPlane = currentEngine.eClippingPlanes[i];
		if (DistancePointPlane(currentPlane, rezultat) < 0)
			rezultat = IntersectionLinePlane(rezultat, q, currentPlane);
	}

	return rezultat;
}

unsigned getNextIndex(vector<punct3d>& listOfPts, unsigned index)
{
	while (index < listOfPts.size())
	{
		if (listOfPts[index].x == INT32_MAX)
			return index;

		index++;
	}

	return -1;
}

void clipPoints(Engine& currentEngine, unsigned index)
{
	unsigned nrOfPts = currentEngine.eObjects[index].nrOfPoints;
	queue<unsigned> PtsToProccess;

	for (int i = 0; i < nrOfPts; i++)
	{
		punct3d currentPoint = currentEngine.eObjects[index].cameraViewPoints[i];

		//Initializeaza lista de vecini pentru punctul curent
		Lista tempL;
		listaVida(tempL);
		currentEngine.eObjects[index].clippedEdges.push_back(tempL);

		//Nu se stie daca punctul va fi proiectat sau nu
		//Pune un punct care nu se poate afla in niciun obiect
		punct3d outOfBoundsPt;
		outOfBoundsPt.x = outsideRange;
		outOfBoundsPt.y = outsideRange;
		outOfBoundsPt.z = outsideRange;
		currentEngine.eObjects[index].clippedPoints.push_back(outOfBoundsPt);

		if (isInsideView(currentEngine, currentPoint))
		{
			//Daca punctul se poate vedea este pus in vector
			currentEngine.eObjects[index].clippedPoints[i] = currentPoint;

			nod* temp = currentEngine.eObjects[index].objEdges[i].prim;
			while (temp != nullptr)
			{
				punct3d tempPoint = currentEngine.eObjects[index].cameraViewPoints[temp->info];
				//Daca vecinul se poate vedea se va afla la aceeasi pozitie
				//Poate fi pus in lista de vecini
				if (isInsideView(currentEngine, tempPoint))
					insereazaLista(currentEngine.eObjects[index].clippedEdges[i], 0, temp->info);

				temp = temp->next;
			}
		}
		else
		{
			//Verifica daca punctul trebuie prelucrat mai departe	
			bool isNeighborInside = false;
			nod* temp = currentEngine.eObjects[index].objEdges[i].prim;
			while (temp != nullptr)
			{
				punct3d tempPoint = currentEngine.eObjects[index].cameraViewPoints[temp->info];
				if (isInsideView(currentEngine, tempPoint))
				{
					isNeighborInside = true;
					break;
				}

				temp = temp->next;
			}

			//Daca exista cel putin un vecin 
			//Punctul va trebui sa devina intersectia
			//Dintre (linia formata de el si vecin) SI (plan)
			if (isNeighborInside == true)
				PtsToProccess.push(i);

		}
	}

	unsigned nextIndex = 0;
	while (!PtsToProccess.empty())
	{
		unsigned currentPtIndex = PtsToProccess.front();
		PtsToProccess.pop();

		punct3d currentPoint = currentEngine.eObjects[index].cameraViewPoints[currentPtIndex];

		nod* temp = currentEngine.eObjects[index].objEdges[currentPtIndex].prim;
		punct3d tempPoint;
		while (temp != nullptr)
		{
			tempPoint = currentEngine.eObjects[index].cameraViewPoints[temp->info];
			if (isInsideView(currentEngine, tempPoint))
			{
				nextIndex = getNextIndex(currentEngine.eObjects[index].clippedPoints, nextIndex);

				if (nextIndex != -1)
					currentEngine.eObjects[index].clippedPoints[nextIndex] =
					clipAgainstPlanes(currentEngine, currentPoint, tempPoint);
				else
				{
					currentEngine.eObjects[index].clippedPoints.push_back(clipAgainstPlanes(currentEngine, currentPoint, tempPoint));
					Lista tempL;
					listaVida(tempL);
					currentEngine.eObjects[index].clippedEdges.push_back(tempL);
					nextIndex = currentEngine.eObjects[index].clippedPoints.size() - 1;

					currentEngine.eObjects[index].nrOfClippedPoints++;
				}

				insereazaLista(currentEngine.eObjects[index].clippedEdges[nextIndex], 0, temp->info);
				insereazaLista(currentEngine.eObjects[index].clippedEdges[temp->info], 0, nextIndex);
			}

			temp = temp->next;
		}
	}
}

void transformCameraView(Engine& currentEngine, unsigned index)
{

	mat4 matCamera = matPointAt(currentEngine.eCamera.cPosition, currentEngine.eCamera.cTarget,
		currentEngine.eCamera.cUp);
	mat4 matView = matLookAt(matCamera);

	int nrOfPts = currentEngine.eObjects[index].nrOfPoints;
	for (int i = 0; i < nrOfPts; i++)
		currentEngine.eObjects[index].cameraViewPoints[i] = ProdVect4x4Matrix(currentEngine.eObjects[index].worldViewPoints[i], matView);
	//currentEngine.eObjects[index].objOrigin = ProdVect4x4Matrix(currentEngine.eObjects[index].objOrigin, matView); - DE STERS

	clipPoints(currentEngine, index);
}

void transformAllCameraView(Engine& currentEngine)
{
	unsigned nrOfObj = currentEngine.nrOfObjects;
	for (int i = 0; i < nrOfObj; i++)
		transformCameraView(currentEngine, i);
}

void rotateCamera(Engine& currentEngine, punct2d rotation)
{
	punct3d pos = currentEngine.eCamera.cPosition;
	punct3d target = currentEngine.eCamera.cTarget;
	target = DifVector(target, pos);
	target = NormaliseVect(target);

	punct3d xaxis;
	xaxis = NormaliseVect(target);
	xaxis = CrossProduct(xaxis, currentEngine.eCamera.cUp);
	xaxis = NormaliseVect(xaxis);

	punct3d yaxis;
	yaxis = NormaliseVect(target);
	yaxis = CrossProduct(xaxis, yaxis);
	yaxis = NormaliseVect(yaxis);

	//Roteste camera fata de target

	pos = currentEngine.eCamera.cPosition;
	target = currentEngine.eCamera.cTarget;

	pos = DifVector(pos, target);

	float coefficient = pi / 512;

	pos = axisRotate(pos, rotation.y * coefficient, xaxis);
	pos = axisRotate(pos, -rotation.x * coefficient, yaxis);

	pos = AddVector(pos, target);

	//Verifica daca target si up sunt pe aceeasi axa
	target = DifVector(target, pos);
	target = NormaliseVect(target);

	if (abs(target.y) < 0.99)
		currentEngine.eCamera.cPosition = pos;

}

void moveCamera(Engine& currentEngine, punct2d move)
{
	punct3d pos = currentEngine.eCamera.cPosition;
	punct3d target = currentEngine.eCamera.cTarget;
	target = DifVector(target, pos);
	target = NormaliseVect(target);

	punct3d xaxis;
	xaxis = NormaliseVect(target);
	xaxis = CrossProduct(xaxis, currentEngine.eCamera.cUp);
	xaxis = NormaliseVect(xaxis);

	punct3d yaxis;
	yaxis = NormaliseVect(target);
	yaxis = CrossProduct(xaxis, yaxis);
	yaxis = NormaliseVect(yaxis);

	//Calculeaza translatia
	xaxis = ProdVect_Const(xaxis, 0.01 * move.x);
	yaxis = ProdVect_Const(yaxis, 0.01 * move.y);

	//Translateaza camera
	pos = currentEngine.eCamera.cPosition;
	target = currentEngine.eCamera.cTarget;

	pos = AddVector(pos, xaxis);
	target = AddVector(target, xaxis);

	pos = AddVector(pos, yaxis);
	target = AddVector(target, yaxis);

	currentEngine.eCamera.cPosition = pos;
	currentEngine.eCamera.cTarget = target;
}

void zoomCamera(Engine& currentEngine, float value)
{
	punct3d pos = currentEngine.eCamera.cPosition;
	punct3d target = currentEngine.eCamera.cTarget;

	punct3d zaxis = DifVector(target, pos);
	zaxis = NormaliseVect(zaxis);

	Plane targetPlane;
	targetPlane.point = target;
	targetPlane.normal = ProdVect_Const(zaxis, -1);

	//Calculeaza translatia
	zaxis = ProdVect_Const(zaxis, value);

	//Translateaza camera
	pos = AddVector(pos, zaxis);

	if (DistancePointPlane(targetPlane, pos) > 0.5 && DistanceTwoPoints(pos, target) < 30)
		currentEngine.eCamera.cPosition = pos;

}

