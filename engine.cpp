#include "Engine.h"

void engineInit(Engine& currentEngine)
{
	//Initializare variabile engine
	//currentEngine.eWindow.create(sf::VideoMode(1280, 720), "3dENGINE");
	currentEngine.eWindow.create(sf::VideoMode::getDesktopMode(), "3dENGINE");
	currentEngine.eTime = sf::Time::Zero;
	currentEngine.eAccTime = sf::Time::Zero;
	currentEngine.eCurrentMousePos.x = 0;
	currentEngine.eCurrentMousePos.y = 0;
	currentEngine.ePrevMousePos.x = 0;
	currentEngine.ePrevMousePos.y = 0;

	currentEngine.eFov = pi/2;
	currentEngine.eAspectRatio = (float)currentEngine.eWindow.getSize().x / currentEngine.eWindow.getSize().y;

	currentEngine.eSelectedObj = 0;
	currentEngine.nrOfObjects = 0;

	//Initializare variabile camera
	currentEngine.eCamera.cPosition.x = 0;
	currentEngine.eCamera.cPosition.y = 4;
	currentEngine.eCamera.cPosition.z = -4;

	currentEngine.eCamera.cTarget.x = 0;
	currentEngine.eCamera.cTarget.y = 0;
	currentEngine.eCamera.cTarget.z = 0;

	currentEngine.eCamera.cUp.x = 0;
	currentEngine.eCamera.cUp.y = 1;
	currentEngine.eCamera.cUp.z = 0;

	//Initializare planuri
	currentEngine.eClippingPlanes[0].point.x = 0;
	currentEngine.eClippingPlanes[0].point.y = 0;
	currentEngine.eClippingPlanes[0].point.z = 0.1; //0.1

	currentEngine.eClippingPlanes[0].normal.x = 0;
	currentEngine.eClippingPlanes[0].normal.y = 0;
	currentEngine.eClippingPlanes[0].normal.z = 1;
	//
	currentEngine.eClippingPlanes[1].point.x = 0;
	currentEngine.eClippingPlanes[1].point.y = 0;
	currentEngine.eClippingPlanes[1].point.z = 0;

	currentEngine.eClippingPlanes[1].normal.x = 0;
	currentEngine.eClippingPlanes[1].normal.y = -1;
	currentEngine.eClippingPlanes[1].normal.z = 1; //1
	//
	currentEngine.eClippingPlanes[2].point.x = 0;
	currentEngine.eClippingPlanes[2].point.y = 0;
	currentEngine.eClippingPlanes[2].point.z = 0;

	currentEngine.eClippingPlanes[2].normal.x = 0;
	currentEngine.eClippingPlanes[2].normal.y = 1;
	currentEngine.eClippingPlanes[2].normal.z = 1; //1
	//
	currentEngine.eClippingPlanes[3].point.x = 0;
	currentEngine.eClippingPlanes[3].point.y = 0;
	currentEngine.eClippingPlanes[3].point.z = 0;

	currentEngine.eClippingPlanes[3].normal.x = 1;
	currentEngine.eClippingPlanes[3].normal.y = 0;
	currentEngine.eClippingPlanes[3].normal.z = 1; //1
	//
	currentEngine.eClippingPlanes[4].point.x = 0;
	currentEngine.eClippingPlanes[4].point.y = 0;
	currentEngine.eClippingPlanes[4].point.z = 0;

	currentEngine.eClippingPlanes[4].normal.x = -1;
	currentEngine.eClippingPlanes[4].normal.y = 0;
	currentEngine.eClippingPlanes[4].normal.z = 1; //1
}

void clearForClipping(Engine& currentEngine, unsigned index)
{
	currentEngine.eObjects[index].projectedPoints.clear();
	currentEngine.eObjects[index].clippedPoints.clear();

	for (int i = 0; i < currentEngine.eObjects[index].nrOfClippedPoints; i++)
		golesteLista(currentEngine.eObjects[index].clippedEdges[i]);
	currentEngine.eObjects[index].clippedEdges.clear();

	currentEngine.eObjects[index].nrOfClippedPoints =
		currentEngine.eObjects[index].nrOfPoints;
}

bool isDrawable(Engine& currentEngine, unsigned currentObj, unsigned index)
{
	if (currentEngine.eObjects[currentObj].clippedPoints[index].x != outsideRange)
		return true;
	else
		return false;
}

punct2d projectPoint(Engine& currentEngine, punct3d point)
{
	float coefficient = 1 / std::tanf(currentEngine.eFov / 2);
	float AS = currentEngine.eAspectRatio;

	punct2d rezultat;

	//PROIECTIE
	rezultat.x = -point.x * coefficient;
	rezultat.y = -point.y * coefficient * AS;

	if (point.z != 0)
	{
		rezultat.x /= point.z;
		rezultat.y /= point.z;
	}

	//SCALARE PENTRU ECRAN
	rezultat.x += 1;
	rezultat.y += 1;

	rezultat.x *= 0.5 * currentEngine.eWindow.getSize().x;
	rezultat.y *= 0.5 * currentEngine.eWindow.getSize().y;

	return rezultat;
}

void projectSingleObject(Engine& currentEngine, unsigned index)
{
	punct2d temp;
	for (int i = 0; i < currentEngine.eObjects[index].nrOfClippedPoints; i++)
		currentEngine.eObjects[index].projectedPoints.push_back(temp);

	for (int i = 0; i < currentEngine.eObjects[index].nrOfClippedPoints; i++)
	{
		if (isDrawable(currentEngine, index, i))
			currentEngine.eObjects[index].projectedPoints[i] = projectPoint(currentEngine, currentEngine.eObjects[index].clippedPoints[i]);
	}
}

void projectObjects(Engine& currentEngine)
{
	for (int i = 0; i < currentEngine.nrOfObjects; i++)
		projectSingleObject(currentEngine, i);
}

void displayPoint(Engine& currentEngine, punct2d coords, float z)
{
	sf::CircleShape point;
	point.setFillColor(sf::Color::White);
	point.setRadius(3);
	point.setOrigin(1.5, 1.5);
	point.setPosition(coords.x, coords.y);

	currentEngine.eWindow.draw(point);
}

void displayLine(lineColor line, Engine& currentEngine)
{
	sf::Vertex vLine[2];
	sf::Vector2f p1(line.point1.x, line.point1.y);
	sf::Vector2f p2(line.point2.x, line.point2.y);
	vLine[0] = p1;
	vLine[1] = p2;

	vLine[0].color = line.color1;
	vLine[1].color = line.color2;

	currentEngine.eWindow.draw(vLine, 2, sf::Lines);
}

void drawObjLine(Engine& currentEngine, unsigned currentObj, unsigned index)
{
	sf::Color c1;
	sf::Color c2;
	switch (currentObj)
	{
	case 0:
		c1 = sf::Color(200, 200, 200, 100);
		c2 = sf::Color(200, 200, 200, 100);
		break;
	default:
		c1 = sf::Color::White;
		c2 = sf::Color::White;
	}

	nod* temp = currentEngine.eObjects[currentObj].clippedEdges[index].prim;
	while (temp != nullptr)
	{
			lineColor currentLine;
			currentLine.point1.x = currentEngine.eObjects[currentObj].projectedPoints[index].x;
			currentLine.point1.y = currentEngine.eObjects[currentObj].projectedPoints[index].y;
			currentLine.point2.x = currentEngine.eObjects[currentObj].projectedPoints[temp->info].x;
			currentLine.point2.y = currentEngine.eObjects[currentObj].projectedPoints[temp->info].y;

			currentLine.color1 = c1;
			currentLine.color2 = c2;

			displayLine(currentLine, currentEngine);

		temp = temp->next;
	}
}

void drawSingleObject(Engine& currentEngine, unsigned index)
{
	for (int i = 0; i < currentEngine.eObjects[index].nrOfClippedPoints; i++)
	{
		if (isDrawable(currentEngine, index, i))
		{
			drawObjLine(currentEngine, index, i);

			if (index != 0)
			{
				punct2d coords;
				coords.x = currentEngine.eObjects[index].projectedPoints[i].x;
				coords.y = currentEngine.eObjects[index].projectedPoints[i].y;
				float z = currentEngine.eObjects[index].objOrigin.z;
				//displayPoint(currentEngine, coords, z);
			}
		}
	}
	clearForClipping(currentEngine, index);
}

void drawObjects(Engine& currentEngine)
{
	for (int i = 0; i < currentEngine.nrOfObjects; i++)
		drawSingleObject(currentEngine, i);
}
