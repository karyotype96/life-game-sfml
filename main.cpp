#include <SFML/Graphics.hpp>
#include <iostream>
#include "Board.h"

#define TSIZE 10
#define XSIZE 1200
#define YSIZE 800

int main(){

    sf::Vector2i clickPos;

    sf::RenderWindow window(sf::VideoMode(XSIZE, YSIZE), "Conway's Game of Life", sf::Style::Titlebar | sf::Style::Close);
    Board b;

    try {
        b.init(XSIZE, YSIZE, TSIZE);
    } catch (const char *msg){
        std::cerr << msg << std::endl;
        exit(0);
    }

    window.clear(sf::Color::Black);
    b.displayBoard(&window, XSIZE, YSIZE);

    while (window.isOpen()){

        sf::Event event;
        while (window.pollEvent(event)){

            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::KeyPressed){
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace))
                    b.zero();
                b.next();
                window.clear(sf::Color::Black);
                b.displayBoard(&window, XSIZE, YSIZE);
            }

            if (event.type == sf::Event::MouseButtonPressed){
                clickPos = sf::Mouse::getPosition(window);
                b.flipCell(sf::Vector2u((clickPos.x / TSIZE) + 2, (clickPos.y / TSIZE) + 2));
                window.clear();
                b.displayBoard(&window, XSIZE, YSIZE);
            }

        }

    }

    return 0;
}
