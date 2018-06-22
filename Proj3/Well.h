#ifndef WELL_INCLUDED
#define WELL_INCLUDED

#include <stack>
#include "Piece.h"

using namespace std;

class Screen;
class Game;

class Well
{
public:
    Well(int x, int y);
    void display(Screen& screen, int x, int y);
    Piece* getPiece();
    Piece* giveNewPiece();
    void setPiece(Piece* piece);
    void setNewPiece();
    Piece* getNewPiece();
    
    void transitionNewPiece();
    void updateScreen(Screen& screen, Game& g);
    void clearLine(Game& g); // clear line if there are all $'s
    
    void saveScreen(Screen& screen);
    
    void specialVaporFunction(Screen& screen);
    void specialFoamFunction(Screen& screen);
    void recursiveFoamFill(int y, int x, int left_x, int right_x, int up_y, int bot_y);
    
    void updateCoord();
    
    bool checkRight(Screen& screen);
    bool checkLeft(Screen& screen);
    bool checkBottom(Screen& screen);
    bool checkOrientation(Screen& screen);
    
    bool gameOver();
    
    void wipeScreen();
    
private:
    stack<Coord> m_saveLoc; // stores all locations of $'s
    char m_grid[19][12]; // declare 2D array to mimic all contents of the screen
    int m_x, m_y;
    Piece* m_piece;
    Piece* m_new_piece;
};

#endif // WELL_INCLUDED

