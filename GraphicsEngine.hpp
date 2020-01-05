#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include "MainIncludes.h"
class CSquare  //sprite with position of tape's square
{
public:
	sf::Texture squareText;
	sf::Sprite squareSpr;
	sf::Vector2f pos; //
	sf::Text value;
	CSquare(sf::Texture*, int, int);
	void changePos(int, int);
};
class CPointer //sprite with position of pointer
{
public:
	sf::Texture pointerText;
	sf::Sprite pointerSpr;
	sf::Vector2f pos; // position
	sf::Text value;
	
	CPointer(sf::Texture*, int, int);
	void changePos(int, int);
};


class CGraphics //graphics and displaying objects
{
public:
	sf::Font font;
	sf::Texture texture;
	sf::RenderWindow window;
	std::vector <CSquare> squares; //vector of Turing Machine's Tape
	std::vector <CPointer> pointer; //vector of Turing Machine's Pointer
	std::string ptString;
	CGraphics();
	void drawAll();
	void sync(int*,int, int); //sync graphics with machine code
	
};
