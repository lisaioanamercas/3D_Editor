#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include "VectorOp.h"
#include "Liste.h"

#define pi 3.141592653589
#define outsideRange INT32_MAX

struct lineColor
{
	punct2d point1;
	punct2d point2;

	sf::Color color1;
	sf::Color color2;
};

struct Camera
{
	punct3d cPosition;
	punct3d cTarget;

	punct3d cUp;
};

struct Object
{
	std::vector<punct3d> objViewPoints;
	std::vector<punct3d> worldViewPoints;
	std::vector<punct3d> cameraViewPoints;
	std::vector<punct3d> clippedPoints;

	std::vector<punct2d> projectedPoints;

	std::vector<Lista> objEdges;
	std::vector<Lista> clippedEdges;
	punct3d objOrigin;

	unsigned nrOfPoints;
	unsigned nrOfClippedPoints;
};

enum engine_mode { viewMode, editMode };

struct Engine
{
	sf::RenderWindow eWindow;
	sf::Time eTime;
	sf::Time eAccTime;

	punct2d eCurrentMousePos;
	punct2d ePrevMousePos;

	float eFov;
	float eAspectRatio;
	engine_mode eMode;

	std::vector<Object> eObjects;
	Camera eCamera;
	Plane eClippingPlanes[5];

	unsigned nrOfObjects;
	unsigned eSelectedObj;
};

void engineInit(Engine& currentEngine);

void clearForClipping(Engine& currentEngine, unsigned index);

bool isDrawable(Engine& currentEngine, unsigned currentObj, unsigned index);

punct2d projectPoint(Engine& currentEngine, punct3d point);

void projectSingleObject(Engine& currentEngine, unsigned index);

void projectObjects(Engine& currentEngine);

void displayPoint(Engine& currentEngine, punct2d coords, float z);

void displayLine(lineColor line, Engine& currentEngine);

void drawObjLine(Engine& currentEngine, unsigned currentObj, unsigned index);

void drawSingleObject(Engine& currentEngine, unsigned index);

void drawObjects(Engine& currentEngine);

