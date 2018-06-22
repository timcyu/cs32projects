#include "Game.h"
#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include <string>
#include <algorithm>

const int SCREEN_WIDTH = 80;
const int SCREEN_HEIGHT = 25;

const int WELL_X = 12;
const int WELL_Y = 18;

const int PROMPT_Y = 20;
const int PROMPT_X = 0;

const int SCORE_X = 16;
const int SCORE_Y = 8;

const int ROWS_LEFT_X = 16;
const int ROWS_LEFT_Y = 9;

const int LEVEL_X = 16;
const int LEVEL_Y = 10;

const int NEXT_PIECE_TITLE_X = 16;
const int NEXT_PIECE_TITLE_Y = 3;

const int NEXT_PIECE_X = 16;
const int NEXT_PIECE_Y = 4;

Game::Game(int width, int height)
: m_screen(SCREEN_WIDTH, SCREEN_HEIGHT), m_level(1), m_well(width, height), m_score(0), m_rowsLeft(5)
{
}

void Game::play()
{
    m_well.display(m_screen, WELL_X, WELL_Y);
    displayStatus();  //  score, rows left, level
    displayPrompt("Press the Enter key to begin playing Chetyris!");
    waitForEnter();  // [in UserInterface.h]
    
    for(;;)
    {
        if ( ! playOneLevel())
            break;
        displayPrompt("Good job!  Press the Enter key to start next level!");
        waitForEnter();
        m_level++;
    }
    displayPrompt("Game Over!  Press the Enter key to exit!");
    waitForEnter();
}

void Game::displayPrompt(std::string s)
{
    m_screen.gotoXY(PROMPT_X, PROMPT_Y);
    m_screen.printStringClearLine(s);   // overwrites previous text
    m_screen.refresh();
}

// Displays various game components
void Game::displayStatus()
{
    // displays "Next piece: "
    m_screen.gotoXY(NEXT_PIECE_TITLE_X, NEXT_PIECE_TITLE_Y);
    m_screen.printString("Next piece:");
    
    // display what the next piece is
    if(m_well.giveNewPiece())
    {
        m_well.giveNewPiece()->displayNewPiece(m_screen, NEXT_PIECE_X, NEXT_PIECE_Y);
    }
    
    // display score
    m_screen.gotoXY(SCORE_X, SCORE_Y);
    m_screen.printString("Score:     ");
    m_screen.printString(rightJustify(7, m_score));
    
    // display level
    m_screen.gotoXY(LEVEL_X, LEVEL_Y);
    m_screen.printString("Level:     ");
    m_screen.printString(rightJustify(7, m_level));
    
    // display rows left
    m_screen.gotoXY(ROWS_LEFT_X, ROWS_LEFT_Y);
    m_screen.printString("Rows left: ");
    m_screen.printString(rightJustify(7, m_rowsLeft));
}

// returns the amount of rows, used in the Well class to decrement rows when they're cleared
int Game::getRowsLeft()
{
    return m_rowsLeft;
}

// Increment the score based on how many rows are cleared
void Game::changeScore(int vaporized)
{
    if(vaporized == 1)
    {
        m_score += 100;
    }
    else if(vaporized == 2)
    {
        m_score += 200;
    }
    else if(vaporized == 3)
    {
        m_score += 400;
    }
    else if(vaporized == 4)
    {
        m_score += 800;
    }
    else if(vaporized == 5)
    {
        m_score += 1600;
    }
}

// Rows are decremented in the Well class clearLine function. The parameter passed into this function 
void Game::decrementRowsLeft(int rows)
{
    m_rowsLeft = rows;
}

string Game::rightJustify(int n, int display)
{
    string disp = to_string(display);
    while(n > 0)
    {
        disp = " " + disp;
        n--;
    }
    return disp;
}

// Play a level...
bool Game::playOneLevel()
{
    m_well.wipeScreen();
    m_rowsLeft = m_level*5;
    
    m_piece = m_well.getNewPiece();
    m_well.setPiece(m_piece);
    m_well.setNewPiece();
    m_well.updateScreen(m_screen, *this);
    this->displayStatus();
    
    double reactionTime = max(1000-(100*(m_level-1)), 100);
    Timer t;
    t.start();
    double prev_time = 0.0;
    
    while(true)
    {
        char key;
        if(getCharIfAny(key))
        {
            switch(key)
            {
                case ARROW_UP:
                    m_well.getPiece()->changeOrientation(m_screen, m_well);
                    break;
                case ARROW_DOWN:
                    m_well.getPiece()->moveDown(m_screen, m_well);
                    break;
                case ARROW_RIGHT:
                    m_well.getPiece()->moveRight(m_screen, m_well);
                    break;
                case ARROW_LEFT:
                    m_well.getPiece()->moveLeft(m_screen, m_well);
                    break;
                case ' ':
                    while(m_well.checkBottom(m_screen) == true)
                    {
                        m_well.getPiece()->moveDown(m_screen, m_well);
                    }
                    break;
                case 'Q':
                case 'q':
                    return false;
                    break;
            }
            m_well.updateScreen(m_screen, *this);
            this->displayStatus();
        }
        
        if(t.elapsed() > reactionTime + prev_time)
        {
            
            m_well.getPiece()->moveDown(m_screen, m_well);
            m_well.updateScreen(m_screen, *this);
            prev_time += reactionTime;
            this->displayStatus();
        }
        
        if(m_well.gameOver() == true)
        {
            return false;
        }
        
        if(m_rowsLeft == 0)
        {
            m_well.updateScreen(m_screen, *this);
            this->displayStatus();
            return true;
        }
    }
    return false;
}
