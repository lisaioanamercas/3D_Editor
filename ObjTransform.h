#pragma once

#include "Engine.h"

void translateSelectedObj(Engine& currentEngine, punct3d translation);

void translateObj(Engine& currentEngine, unsigned index, punct3d translation);

void xRotateSelectedObj(Engine& currentEngine, float angle);

void yRotateSelectedObj(Engine& currentEngine, float angle);

void zRotateSelectedObj(Engine& currentEngine, float angle);

void rotateObj(Engine& currentEngine, unsigned index, float angle, punct3d axis);

void resizeSelectedObj(Engine& currentEngine, float factor);

punct3d axisRotate(punct3d input, float angle, punct3d axis);
