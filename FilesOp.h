#pragma once

#include <iostream>
#include <fstream>
#include "Engine.h"

punct3d extractVertex(char line[256]);

void extractEdge(char line[256], std::vector<Lista>& graph);

void readObject(const char* filepath, Engine& currentEngine);

void loadObject(const char* filepath, Engine& currentEngine);
