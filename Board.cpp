#include "Board.h"
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>

Board::Board()
{

}

void Board::init(int x, int y, int tilesize){
    tsize = tilesize;

    if (x % tsize != 0 || y % tilesize != 0)
        throw "Invalid tile/window size";

    //next step
    todo.reserve(x / tilesize + 4);
    for (unsigned int i = 0; i < todo.capacity(); i++){
        std::vector<int> v(y / tilesize + 4);
        todo.push_back(v);
    }

    for (unsigned int i = 0; i < todo.size(); i++){
        for (unsigned int j = 0; j < todo[i].size(); j++){
            todo[i][j] = 0;
        }
    }
    //current board
    curr.reserve(x / tilesize + 4);

    for (unsigned int i = 0; i < curr.capacity(); i++){
        std::vector<int> v(y / tilesize + 4);
        curr.push_back(v);
    }

    for (unsigned int i = 0; i < curr.size(); i++){
        for (unsigned int j = 0; j < curr[i].size(); j++){
            curr[i][j] = 0;
        }
    }
}

void Board::printBoard()
{
    std::cout << "Todo: " << std::endl;
    for (unsigned int y = 0; y < curr.size(); y++){
        for (unsigned int x = 0; x < curr[y].size(); x++){
            std::cout << todo[x][y] << " ";
        }
        std::cout << std::endl;
    }

    std::cout << "Curr: " << std::endl;
    for (unsigned int y = 0; y < curr.size(); y++){
        for (unsigned int x = 0; x < curr[y].size(); x++){
            std::cout << curr[x][y] << " ";
        }
        std::cout << std::endl;
    }
}

void Board::displayBoard(sf::RenderWindow *rw, int xsize, int ysize){
    sf::RectangleShape currentShape;

    for (unsigned int i = 1; i < curr.size() - 1; i++){
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(i * tsize, 0)),
            sf::Vertex(sf::Vector2f(i * tsize, ysize))
        };
        line[0].color = sf::Color(128, 128, 128);
        line[1].color = sf::Color(128, 128, 128);
        rw->draw(line, 2, sf::Lines);
    }

    for (unsigned int i = 1; i < curr.size() - 1; i++){
        sf::Vertex line[] =
        {
            sf::Vertex(sf::Vector2f(0, i * tsize)),
            sf::Vertex(sf::Vector2f(xsize, i * tsize))
        };
        line[0].color = sf::Color(128, 128, 128);
        line[1].color = sf::Color(128, 128, 128);
        rw->draw(line, 2, sf::Lines);
    }

    for (unsigned int x = 1; x < (curr.size() - 1); x++){
        for (unsigned int y = 1; y < (curr[0].size()) - 1; y++){
            if (curr[x][y] > 0){
                currentShape = sf::RectangleShape(sf::Vector2f(tsize, tsize));
                currentShape.setPosition(tsize * (x - 2), tsize * (y - 2));
                rw->draw(currentShape);
            }
        }
    }

    rw->display();
}

void Board::next(){
    int total;

    for (unsigned int x = 1; x < curr.size() - 1; x++){
        for (unsigned int y = 1; y < curr[x].size() - 1; y++){
            total =
                curr[x - 1][y - 1] +
                curr[x][y - 1] +
                curr[x + 1][y - 1] +
                curr[x - 1][y] +
                curr[x + 1][y] +
                curr[x - 1][y + 1] +
                curr[x][y + 1] +
                curr[x + 1][y + 1];

            if (total < 2 || total > 3){
                todo[x][y] = 0;
            } else if (total == 2){
                todo[x][y] = curr[x][y];
            } else if (total == 3) {
                todo[x][y] = 1;
            }

            total = 0;
        }

    }

    copyToCurrent();
}

void Board::flipCell(sf::Vector2u pos){
    curr[pos.x][pos.y] = !curr[pos.x][pos.y];

}

void Board::copyToCurrent()
{
    for (unsigned int i = 0; i < todo.size(); i++){
        for (unsigned int j = 0; j < todo[i].size(); j++){
            curr[i][j] = todo[i][j];
            todo[i][j] = 0;
        }
    }
}

void Board::zero(){
    for (unsigned int i = 0; i < todo.size(); i++){
        for (unsigned int j = 0; j < todo[i].size(); j++){
            curr[i][j] = 0;
        }
    }
}
