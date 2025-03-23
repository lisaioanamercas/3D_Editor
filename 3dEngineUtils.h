#pragma once

#include "Engine.h"
#include "ObjTransform.h"
#include "Camera.h"
#include "FilesOp.h"

void Initialize(Engine& currentEngine);

void Input(Engine& currentEngine);

void Update(Engine& currentEngine);

void Draw(Engine& currentEngine);

void handleButton(sf::Event event, sf::Sprite& button, sf::Texture& buttonTexture, sf::Texture& hoverTexture, const char* filepath, Engine& mainEngine, sf::Text& popupText, sf::RectangleShape& textBackground, int x, int y, string S);