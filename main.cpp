#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <string>
#include "Engine.h"
#include "ObjTransform.h"
#include "Camera.h"
#include "3dEngineUtils.h"
#include <fstream>
#include <iostream>

#define window mainEngine.eWindow

int main()
{

    Engine mainEngine;
    sf::Clock clock;
    bool rotire_w = 0;
    Initialize(mainEngine);

    std::ofstream outputFile("exemplu.txt");

    if (outputFile.is_open()) {
        // Write data to the file
        outputFile << "Hello, World!\n";
        outputFile << "This is a line of text.\n";
        outputFile.close();
    }
    else {
        std::cerr << "Error opening file for writing.\n";
        return 1;
    }

    // Reading from the file
    std::ifstream inputFile("exemplu.txt");

    if (inputFile.is_open()) {
        std::string line;
        while (std::getline(inputFile, line)) {
            // Process each line of the file
            std::cout << "Read from file: " << line << '\n';
        }
        inputFile.close();
    }
    else {
        std::cerr << "Error opening file for reading.\n";
        return 1;
    }


    while (mainEngine.eWindow.isOpen())
    {
        //Seteaza timpul
        mainEngine.eTime = clock.restart();
        mainEngine.eAccTime += mainEngine.eTime;//NU MAI AVEM 2 CLOCK RESTART URI ! :)

        Input(mainEngine);

        sf::Texture cubS, pyrS, maiS, sfeS, cilS, conS, addPS, addLS, rotS, bigS, ambS;
        if (!cubS.loadFromFile("B1.png") || !pyrS.loadFromFile("B2.png") ||
            !maiS.loadFromFile("B3.png") || !sfeS.loadFromFile("B4.png") ||
            !cilS.loadFromFile("B5.png") || !conS.loadFromFile("SB.png") ||
            !addPS.loadFromFile("SB.png") || !addLS.loadFromFile("SB.png") ||
            !rotS.loadFromFile("SB.png") || !bigS.loadFromFile("SB.png") ||
            !ambS.loadFromFile("B11.png"))
        {
            std::cerr << "Error loading button textures\n";
            return 1;
        }

        sf::Texture cubH, pyrH, maiH, sfeH, cilH, conH, addPH, addLH, rotH, bigH, ambH;
        if (!cubH.loadFromFile("B1hover.png") || !pyrH.loadFromFile("B2hover.png") ||
            !maiH.loadFromFile("B3hover.png") || !sfeH.loadFromFile("B4hover.png") ||
            !cilH.loadFromFile("B5hover.png") || !conH.loadFromFile("SBhover.png") ||
            !addPH.loadFromFile("SBhover.png") || !addLH.loadFromFile("SBhover.png") ||
            !rotH.loadFromFile("SBhover.png") || !bigH.loadFromFile("SBhover.png") ||
            !ambH.loadFromFile("B11hover.png"))
        {
            std::cerr << "Error loading hover textures\n";
            return 1;
        }

        sf::Sprite cub(cubS), piramida(pyrS), maimuta(maiS), sfera(sfeS), cilindru(cilS), con(conS), addPoint(addPS), addLine(addLS), rotire(rotS), mai_mare(bigS), ambience(ambS);


        cub.setPosition(0, 10);
        piramida.setPosition(90, 10);
        maimuta.setPosition(180, 10);
        sfera.setPosition(270, 10);
        cilindru.setPosition(360, 10);
        con.setPosition(450, 10);
        addPoint.setPosition(540, 10);
        addLine.setPosition(630, 10);
        rotire.setPosition(720, 10);
        mai_mare.setPosition(810, 10);
        ambience.setPosition(900, 10);
        //save.setPosition(coord[12].x, 10);
        //restore.setPosition(coord[13].x, 10);
        //clear.setPosition(coord[14].x, 10);
        //clear.setPosition(coord[15].x, 10);
        //exit.setPosition(coord[16].x, 10);


        sf::Font font;
        if (!font.loadFromFile("arial.ttf"))
        {
            std::cerr << "Error loading font\n";
            return 1;
        }

        sf::Text popupText;
        sf::RectangleShape textBackground;

        popupText.setFont(font);
        popupText.setCharacterSize(16);
        popupText.setFillColor(sf::Color::White);
        textBackground.setFillColor(sf::Color(128, 128, 128, 200));


        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            if (rotire_w == 1)
            {
                mainEngine.eSelectedObj = 1;
                yRotateSelectedObj(mainEngine, mainEngine.eTime.asSeconds() * pi);
            }

            ///pur si simplu citire din fisier
            handleButton(event, cub, cubS, cubH, "cube.obj", mainEngine, popupText, textBackground, 0, 10, "sdfgh'\n'ukfhvgyudsjcuivkfjdghyu");
            handleButton(event ,piramida, pyrS, pyrH, "pyramid.obj", mainEngine, popupText, textBackground, 90, 10, "sdfghukfhvgyudsjcuivkfjdghyu");
            handleButton(event ,maimuta, maiS, maiH, "suzanne.obj", mainEngine, popupText, textBackground, 180, 10, "sdfghukfhvgyudsjcuivkfjdghyu");
            handleButton(event, sfera, sfeS, sfeH, "ball.obj", mainEngine, popupText, textBackground, 270, 10, "sdfghukfhvgyudsjcuivkfjdghyu");
            handleButton(event ,cilindru, cilS, cilH, "cylinder.obj", mainEngine, popupText, textBackground, 360, 10, "sdfghukfhvgyudsjcuivkfjdghyu");
            handleButton(event, con, conS, conH, "cone.obj", mainEngine, popupText, textBackground, 450, 10, "sdfghukfhvgyudsjcuivkfjdghyu");
            /////////////////////////////////////////////////////////////////////////////////////////////////////////
            handleButton(event, addPoint, addPS, addPH, "cone.obj", mainEngine, popupText, textBackground, 540, 10, "sdfghukfhvgyudsjcuivkfjdghyu");
            handleButton(event, addLine, addLS, addLH, "cone.obj", mainEngine, popupText, textBackground, 630, 10, "sdfghukfhvgyudsjcuivkfjdghyu");





            ////buton9
            if (rotire.getGlobalBounds().contains(mousePos))
            {
                rotire.setTexture(rotH);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    ////
                    rotire_w = 1;
                }
            }
            else
            {
                rotire.setTexture(rotS);
            }

            ////buton10
            if (mai_mare.getGlobalBounds().contains(mousePos))
            {
                mai_mare.setTexture(bigH);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    mainEngine.eSelectedObj = 1;
                    resizeSelectedObj(mainEngine, 5);
                }
            }
            else
            {
                mai_mare.setTexture(bigS);
            }
            
            if (ambience.getGlobalBounds().contains(mousePos))
            {
                ambience.setTexture(ambH);
                if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
                {
                    std::cout << "altele\n";
                    window.close();

                }
            }
            else
            {
                ambience.setTexture(ambS);
            }
            
            Update(mainEngine);

            //ambienta
            //int orice;
            //orice = mainEngine.eAccTime.asSeconds()*10;
            //orice %= 256; 
            window.clear(sf::Color(30, 30, 30, 255));
            //window.clear(sf::Color(orice, orice, orice, 255));

            drawObjects(mainEngine);

            window.draw(cub);
            window.draw(piramida);
            window.draw(maimuta);
            window.draw(sfera);
            window.draw(cilindru);
            window.draw(con);
            window.draw(addPoint);
            window.draw(addLine);
            window.draw(rotire);
            window.draw(mai_mare);
            window.draw(ambience);


            if (cub.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                window.draw(textBackground);
                window.draw(popupText);
            }
            else if (piramida.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                window.draw(textBackground);
                window.draw(popupText);
            }
            else if (maimuta.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                window.draw(textBackground);
                window.draw(popupText);
            }
            else if (sfera.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                window.draw(textBackground);
                window.draw(popupText);
            }
            else if (cilindru.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                window.draw(textBackground);
                window.draw(popupText);
            }
            else if (con.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
            {
                window.draw(textBackground);
                window.draw(popupText);
            }

            window.display();
        }
    }
    return 0;
}