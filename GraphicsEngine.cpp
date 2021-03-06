#include "GraphicsEngine.hpp"


extern NumberConverter convert;

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
CControlPanel::CControlPanel(sf::Texture* texture, int x, int y, std::string str,sf::Font* ft, int i, int j)
{
	this->controlSpr1.setTexture(*texture);
	this->controlSpr1.setTextureRect(sf::IntRect(186, 1, 111, 65));
	this->controlSpr2.setTexture(*texture);
	this->controlSpr2.setTextureRect(sf::IntRect(186, 66, 111, 65));
	this->pos.x = x;
	this->pos.y = y;
	this->clicked = 0;
	this->controlSpr1.setPosition(pos);
	this->controlSpr2.setPosition(pos);
	this->sign = str;
	this->value.setFont(*ft);
	this->value.setFillColor(sf::Color::White);
	this->value.setCharacterSize(40);
	this->value.setString(str);
	this->value.setPosition(this->pos.x + 49, this->pos.y + 8);
	this->id_x = i;
	this->id_y = j;

}
void CControlPanel::changePos(int x, int y)
{
	this->pos.x = x;
	this->pos.y = y;
	this->controlSpr1.setPosition(pos);
	this->controlSpr2.setPosition(pos);
}
void CControlPanel::changeState()
{
	this->clicked = !this->clicked;
}

CGraphics::CGraphics()
{
	
	font.loadFromFile("Include/Fonts/Font1.ttf");
	window.create(sf::VideoMode(2081, 540), "Turing Machine");
	texture.loadFromFile("Include/Sprites/Sprites.png");
	//tape create
	for (int i = 0; i < 40; i++)
	{
		squares.push_back(CSquare(&texture, 52 * i, 200));
		squares[i].value.setFont(font);
		squares[i].value.setFillColor(sf::Color::Black);
		squares[i].value.setCharacterSize(40);
		squares[i].value.setString("#");
		squares[i].value.setPosition(squares[i].pos.x+16, squares[i].pos.y-1);

	}
	//pointer create
	pointer.push_back(CPointer(&texture, 26 - 40 +52*10, 113));
	pointer[0].value.setFont(font);
	pointer[0].value.setFillColor(sf::Color::Black);
	pointer[0].value.setCharacterSize(40);
	pointer[0].value.setString("0");
	pointer[0].value.setPosition(pointer[0].pos.x + 30, pointer[0].pos.y + 13);
	//control panel create
	panels.push_back(CControlPanel(&texture, 20, 260, "7",  &font, 0, 0));
	panels.push_back(CControlPanel(&texture, 132, 260, "8", &font, 0, 1));
	panels.push_back(CControlPanel(&texture, 244, 260, "9", &font, 0, 2));
	panels.push_back(CControlPanel(&texture, 20, 326, "4",  &font, 1, 0));
	panels.push_back(CControlPanel(&texture, 132, 326, "5", &font, 1, 1));
	panels.push_back(CControlPanel(&texture, 244, 326, "6", &font, 1, 2));
	panels.push_back(CControlPanel(&texture, 20, 391, "1",  &font, 2, 0));
	panels.push_back(CControlPanel(&texture, 132, 391, "2", &font, 2, 1));
	panels.push_back(CControlPanel(&texture, 244, 391, "3", &font, 2, 2));
	panels.push_back(CControlPanel(&texture, 132, 457, "0", &font, 3, 1));
	panels.push_back(CControlPanel(&texture, 244, 457, "=", &font, 3, 2));
	panels.push_back(CControlPanel(&texture, 20, 457, "<-", &font, 3, 0));
	panels.push_back(CControlPanel(&texture, 356, 260, "+", &font, 0, 3));
	panels.push_back(CControlPanel(&texture, 356, 326, "-", &font, 1, 3));
	panels.push_back(CControlPanel(&texture, 356, 391, "*", &font, 2, 3));
	panels.push_back(CControlPanel(&texture, 356, 457, "/", &font, 3, 3));
	this->pointer_x = 0;
	this->pointer_y = 0;
	//equation 
	this->FIRST_VALUE = 0;
	this->SECOND_VALUE = 0;
	this->OPERATION = Operation::ADD;
	this->entryCounter = 0;
	operationText1.setFont(font);
	operationText1.setCharacterSize(40);
	operationText1.setFillColor(sf::Color::White);
	operationText1.setPosition(600, 400);
	operationText1.setString("0");
	operationText2.setFont(font);
	operationText2.setCharacterSize(40);
	operationText2.setFillColor(sf::Color::White);
	operationText2.setPosition(800, 400);
	operationText2.setString("0");
	signText.setFont(font);
	signText.setCharacterSize(40);
	signText.setFillColor(sf::Color::White);
	signText.setPosition(730, 400);
	signText.setString("+");
	textBox.setTexture(texture);
	textBox.setTextureRect(sf::IntRect(0, 131, 300, 44));
	textBox.setPosition(588, 405);
	this->SEND = 0;
	textBox2.setTexture(texture);
	textBox2.setTextureRect(sf::IntRect(0, 131, 300, 44));
	textBox2.setPosition(588, 455);
	resultText.setFont(font);
	resultText.setCharacterSize(40);
	resultText.setFillColor(sf::Color::White);
	resultText.setPosition(620, 450);
	resultText.setString("Result");
	
	
}


void CGraphics::drawAll()
{
	for (size_t k = 0; k < panels.size(); k++) //pointer on blackened panel
	{
		if (panels[k].id_y == pointer_x && panels[k].id_x == pointer_y)
		{
			panels[k].clicked = 1;
		}
		else
		{
			panels[k].clicked = 0;
		}
	}
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
	for (size_t k = 0; k < panels.size(); k++)
	{
		if (panels[k].clicked)
		{
			window.draw(panels[k].controlSpr2);
		}
		else
		{
			window.draw(panels[k].controlSpr1);
		}
		window.draw(panels[k].value);
	}
	window.draw(textBox);
	window.draw(operationText1);
	window.draw(operationText2);
	window.draw(signText);
	window.draw(textBox2);
	window.draw(resultText);

	window.display();
}
void CGraphics::sync(int* tape, int position, int value)
{
	for (int i = 0; i < 40; i++)
	{
		switch (tape[i])
		{
		case 0:
			squares[i].value.setString("0");
			break;
		case 1:
			squares[i].value.setString("1");
			break;
		case EMPTY:
			squares[i].value.setString(" ");
			break;

		case 2:
			squares[i].value.setString("2");
			break;
		case 3:
			squares[i].value.setString("3");
			break;
		case 4:
			squares[i].value.setString("4");
			break;
		case 5:
			squares[i].value.setString("5");
			break;
		case 6:
			squares[i].value.setString("6");
			break;
		case 7:
			squares[i].value.setString("7");
			break;
		case 8:
			squares[i].value.setString(" ");
			break;
		case 9:
			squares[i].value.setString("9");
			break;
		}
	}
	pointer[0].changePos(26 - 40 + 52 * position, 113);
	pointer[0].value.setPosition(pointer[0].pos.x + 30, pointer[0].pos.y + 13);
	ptString = std::to_string(value);
	pointer[0].value.setString(ptString);
}

void CGraphics::controls()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		pointer_x--;
		if (pointer_x < 0) pointer_x = 0;
		Sleep(200);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		pointer_y--;
		if (pointer_y < 0) pointer_y = 0;
		Sleep(200);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		pointer_x++;
		if (pointer_x > 3) pointer_x = 3;
		Sleep(200);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		pointer_y++;
		if (pointer_y > 3) pointer_y = 3;
		Sleep(200);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) //DATA ENTRY
	{
		if (pointer_x == 0 && pointer_y == 0)//7
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 7;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 7;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}

		}
		if (pointer_x == 0 && pointer_y == 1)//4
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 4;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 4;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}

		}
		if (pointer_x == 0 && pointer_y == 2)//1
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 1;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 1;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 0 && pointer_y == 3) //<-
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE / 10;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				if (entryCounter == 0 && SECOND_VALUE == 0)
				{
					entryCounter = 2;
					writing = 0;
				}
				else
				{
					SECOND_VALUE = SECOND_VALUE / 10;
					operationText2.setString(std::to_string(SECOND_VALUE));
				}
			}
			entryCounter--;
			if (entryCounter < 0) entryCounter = 0;
		}
		if (pointer_x == 1 && pointer_y == 0)//8
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 8;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 8;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 1 && pointer_y == 1)//5
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 5;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 5;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 1 && pointer_y == 2)//2
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 2;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 2;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 1 && pointer_y == 3)//0
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 0;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 0;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 2 && pointer_y == 0)//9
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 9;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 9;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 2 && pointer_y == 1)//6
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 6;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 6;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 2 && pointer_y == 2)//3
		{
			if (writing == 0)
			{
				FIRST_VALUE = FIRST_VALUE * 10 + 3;
				if (FIRST_VALUE < 255) entryCounter++;
				else FIRST_VALUE = 255;
				operationText1.setString(std::to_string(FIRST_VALUE));
			}
			else
			{
				SECOND_VALUE = SECOND_VALUE * 10 + 3;
				if (SECOND_VALUE < 255) entryCounter++;
				else SECOND_VALUE = 255;
				operationText2.setString(std::to_string(SECOND_VALUE));
			}
		}
		if (pointer_x == 2 && pointer_y == 3)//= ///////////////////////////////////////////////STARTING OPERATION
		{
			std::cout << "=";  
			if (OPERATION == Operation::SUB && SECOND_VALUE > FIRST_VALUE)
			{
				resultText.setString("2nd value needs to \nbe lower than 1st");
				resultText.setCharacterSize(20);
			}
			else if (OPERATION == Operation::DIV && SECOND_VALUE == 0)
			{
				resultText.setString("Cannot divide by 0");
				resultText.setCharacterSize(20);
			}
			else
			SEND = 1;
		}
		if (pointer_x == 3 && pointer_y == 0)//+
		{
			if(writing==0)entryCounter = 0;
			writing = 1;
			OPERATION = Operation::ADD;
			signText.setString("+");
		}
		if (pointer_x == 3 && pointer_y == 1)//-
		{
			if (writing == 0)entryCounter = 0;
			writing = 1;
			OPERATION = Operation::SUB;
			signText.setString("-");
		}
		if (pointer_x == 3 && pointer_y == 2)//*
		{
			if (writing == 0)entryCounter = 0;
			writing = 1;
			OPERATION = Operation::MUL;
			signText.setString("*");
		}
		if (pointer_x == 3 && pointer_y == 3)// '/'
		{
			if (writing == 0)entryCounter = 0;
			writing = 1;
			OPERATION = Operation::DIV;
			signText.setString("/");
		}
		Sleep(250);
	}

}