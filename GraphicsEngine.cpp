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


CGraphics::CGraphics()
{
	font.loadFromFile("Include/Fonts/Font1.ttf");
	window.create(sf::VideoMode(990, 540), "Turing Machine");
	texture.loadFromFile("Include/Sprites/Sprites.png");
	for (int i = 0; i < 19; i++)
	{
		squares.push_back(CSquare(&texture, 52 * i, 200));
		squares[i].value.setFont(font);
		squares[i].value.setFillColor(sf::Color::Black);
		squares[i].value.setCharacterSize(40);
		squares[i].value.setString("#");
		squares[i].value.setPosition(squares[i].pos.x+16, squares[i].pos.y-1);

	}
	pointer.push_back(CPointer(&texture, 26 - 40 +52*10, 113));
	pointer[0].value.setFont(font);
	pointer[0].value.setFillColor(sf::Color::Black);
	pointer[0].value.setCharacterSize(40);
	pointer[0].value.setString("0");
	pointer[0].value.setPosition(pointer[0].pos.x + 30, pointer[0].pos.y + 13);

}

void CGraphics::drawAll()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
	window.clear(sf::Color(255, 255, 255));
	for (size_t k = 0; k < squares.size(); k++)
	{
		window.draw(squares[k].squareSpr);
		window.draw(squares[k].value);
	}
	for (size_t k = 0; k < pointer.size(); k++)
	{
		window.draw(pointer[k].pointerSpr);
		window.draw(pointer[k].value);
	}
	window.display();
}
void CGraphics::sync(int* tape, int position, int value) 
{
	for (int i = 0; i < 19; i++)
	{
		switch (tape[i])
		{
		case 0:
			squares[i].value.setString("0");
			break;
		case 1:
			squares[i].value.setString("1");
			break;
		case 2:
			squares[i].value.setString(" ");
			break;
		}
	}
	pointer[0].changePos(26 - 40 + 52 * position, 113);
	pointer[0].value.setPosition(pointer[0].pos.x + 30, pointer[0].pos.y + 13);
	ptString = std::to_string(value);
	pointer[0].value.setString(ptString);



}
