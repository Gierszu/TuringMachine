#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>

class CSquare 
{
public:
	sf::Texture squareText;
	sf::Sprite squareSpr;
	sf::Vector2f pos; //
	CSquare(sf::Texture*, int, int);
	void changePos(int, int);
};
class CPointer
{
public:
	sf::Texture pointerText;
	sf::Sprite pointerSpr;
	sf::Vector2f pos; //
	CPointer(sf::Texture*, int, int);
	void changePos(int, int);
};

