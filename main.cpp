
#include "MainIncludes.h"

int main()
{
    sf::RenderWindow window(sf::VideoMode(960,540), "SFML works!");

    std::vector <CSquare> squares; //vector of Turing Machine's Tape
    sf::Texture texture; //it doesn't load, when not in main file
    texture.loadFromFile("Sprites/Sprites.png");
    CPointer pointer(&texture, 26 - 40, 113);
    for (int i = 0; i < 19; i++)
    {
        squares.push_back(CSquare(&texture,52*i, 200));
    }

    while (window.isOpen())
    {
        window.clear(sf::Color(255, 255, 255));;

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        for (size_t k = 0; k < squares.size(); k++)
        {
            window.draw(squares[k].squareSpr);
        }
        window.draw(pointer.pointerSpr);
        window.display();

        Sleep(1000);
        pointer.changePos(pointer.pos.x + 52, pointer.pos.y);
    }

    return 0;
}