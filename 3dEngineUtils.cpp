#include "3dEngineUtils.h"
#define window mainEngine.eWindow

void Initialize(Engine& currentEngine)
{
	engineInit(currentEngine);

	char filepaths[10][256];
	strcpy(filepaths[0], "axes.obj");
	//strcpy(filepaths[1], "Suzanne.obj");

	for (int i = 0; i < 1; i++)
		loadObject(filepaths[i], currentEngine);

	punct3d translateAxes;
	translateAxes.x = -50;
	translateAxes.y = 0;
	translateAxes.z = -50;

	punct3d translate;
	translate.x = 0;
	translate.y = 4;
	translate.z = 0;

	punct3d axis;
	axis.x = 0;
	axis.y = 1;
	axis.z = 0;
	translateObj(currentEngine, 0, translateAxes);
	//translateObj(currentEngine, 1, translate);
	//rotateObj(currentEngine, 1, pi / 2, axis);
}

void Input(Engine& currentEngine)
{
	sf::Event event;
	while (currentEngine.eWindow.pollEvent(event))
	{
		//Inchide program
		if (event.type == sf::Event::Closed)
			currentEngine.eWindow.close();
		if (event.type == sf::Event::KeyPressed)
			if (event.key.code == sf::Keyboard::Escape)
				currentEngine.eWindow.close();

		//Camera zoom
		if (event.type == sf::Event::MouseWheelScrolled)
			zoomCamera(currentEngine, event.mouseWheelScroll.delta);
	}
	sf::Vector2i tempMouse;
	tempMouse = sf::Mouse::getPosition(currentEngine.eWindow);


	currentEngine.eCurrentMousePos.x = tempMouse.x;
	currentEngine.eCurrentMousePos.y = tempMouse.y;

	punct2d mCoords;
	mCoords = DifVector2d(currentEngine.eCurrentMousePos, currentEngine.ePrevMousePos);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		moveCamera(currentEngine, mCoords);
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
		rotateCamera(currentEngine, mCoords);

	currentEngine.ePrevMousePos.x = currentEngine.eCurrentMousePos.x;
	currentEngine.ePrevMousePos.y = currentEngine.eCurrentMousePos.y;
}

void Update(Engine& currentEngine)
{
	transformAllCameraView(currentEngine);
	projectObjects(currentEngine);

}

void Draw(Engine& currentEngine)
{
	currentEngine.eWindow.clear(sf::Color::Black);
	drawObjects(currentEngine);
	currentEngine.eWindow.display();

}

void handleButton(sf::Event event, sf::Sprite& button, sf::Texture& buttonTexture, sf::Texture& hoverTexture,
	const char* filepath, Engine& mainEngine, sf::Text& popupText, sf::RectangleShape& textBackground, int x, int y, string S)
{

	sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	if (button.getGlobalBounds().contains(mousePos))
	{
		button.setTexture(hoverTexture);

		popupText.setString(S);
		popupText.setPosition(x + 45, y + 90);
		textBackground.setSize(sf::Vector2f(popupText.getGlobalBounds().width + 20, popupText.getGlobalBounds().height + 10));
		textBackground.setPosition(x + 40, y + 85);

		if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
		{
			loadObject(filepath, mainEngine);
		}
	}
	else
	{
		button.setTexture(buttonTexture);
	}
}