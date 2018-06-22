#ifndef GAME_INCLUDED
#define GAME_INCLUDED

#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>

class Game
{
public:
    Game(int width, int height);
    void play();
    bool playOneLevel();
    void displayPrompt(std::string s);
    void displayStatus();
    
    int getRowsLeft();
    void changeScore(int vaporized);
    void decrementRowsLeft(int rows);
    
    string rightJustify(int n, int display);
    
private:
    Screen  m_screen;
    int     m_level;
    Well    m_well;
    int     m_score;
    int     m_rowsLeft;
    Piece*  m_piece;
};

#endif // GAME_INCLUDED

