#include "GraphicsEngine.hpp"




CSquare::CSquare(sf::Texture* texture,int x, int y)
{
	this->squareSpr.setTexture(*texture);
	this->squareSpr.setTextureRect(sf::IntRect(81, 0, 51, 53));
	this->pos.x = x;
	this->pos.y = y;
	this->squareSpr.setPosition(pos);
}
void CSquare::changePos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->squareSpr.setPosition(pos);
}
CPointer::CPointer(sf::Texture* texture, int x, int y)
{
	this->pointerSpr.setTexture(*texture);
	this->pointerSpr.setTextureRect(sf::IntRect(0, 0, 80, 87));
	this->pos.x = x;
	this->pos.y = y;
	this->pointerSpr.setPosition(pos);
}
void CPointer::changePos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->pointerSpr.setPosition(pos);
}