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

class CControlPanel
{
public:
	sf::Texture controlText;
	sf::Sprite controlSpr1;
	sf::Sprite controlSpr2;
	sf::Vector2f pos;
	sf::Text value;
	bool clicked;
	std::string sign;
	sf::Font* font;
	int id_x;
	int id_y;
	CControlPanel(sf::Texture*, int, int, std::string, sf::Font*, int, int);
	void changePos(int, int);
	void changeState();
};

class CGraphics //graphics and displaying objects
{
public:
	sf::Font font;
	sf::Texture texture;
	sf::RenderWindow window;
	std::vector <CSquare> squares; //vector of Turing Machine's Tape
	std::vector <CPointer> pointer; //vector of Turing Machine's Pointer
	std::vector <CControlPanel> panels; //vector of input panels
	std::string ptString;
	int FIRST_VALUE;//
	int SECOND_VALUE;// ENTRY 
	int OPERATION;//
	bool writing; //0 writing to first value, 1 writing to 2nd value
	int entryCounter;// for decimal conversion
	int pointer_x;//location on panels
	int pointer_y;//
	sf::Text operationText1;//
	sf::Text operationText2;// for text box
	sf::Text signText;//
	sf::Sprite textBox;//
	CGraphics();
	void drawAll();
	void sync(int*,int, int); //sync graphics with machine code
	void controls();
	
};
