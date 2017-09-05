#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <SFML/Graphics.hpp>

class Board
{
    public:
        Board();

        void init(int, int, int);
        void printBoard();
        void displayBoard(sf::RenderWindow *, int, int);
        void next();
        void flipCell(sf::Vector2u);
        void zero();

    protected:

    private:
        int tsize;
        std::vector<std::vector<int> > todo;
        std::vector<std::vector<int> > curr;

        void copyToCurrent();
        void addSquare(int, int);
};

#endif // BOARD_H
