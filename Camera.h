#pragma once

#include "Engine.h"
#include "ObjTransform.h"
#include <queue>


bool isInsideView(Engine& currentEngine, punct3d point);

punct3d clipAgainstPlanes(Engine& currentEngine, punct3d p, punct3d q);

unsigned getNextIndex(vector<punct3d>& listOfPts, unsigned index);

void clipPoints(Engine& currentEngine, unsigned index);

void transformCameraView(Engine& currentEngine, unsigned index);

void transformAllCameraView(Engine& currentEngine);

void rotateCamera(Engine& currentEngine, punct2d rotation);

void moveCamera(Engine& currentEngine, punct2d move);

void zoomCamera(Engine& currentEngine, float value);

