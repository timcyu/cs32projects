#include "Well.h"
#include "UserInterface.h"
#include "Piece.h"
#include "Game.h"

Well::Well(int x, int y) : m_x(x), m_y(y), m_piece(nullptr), m_new_piece(nullptr)
{
    for(int i = 1; i < 11; i++)
    {
        for(int j = 0; j < 18; j++)
        {
            {
                m_grid[j][i] = ' ';
            }
        }
    }
}

// Display function for the well's walls
void Well::display(Screen& screen, int x, int y)
{
    
    // prints left wall of the well
    for(int left_bound = 0; left_bound < y; left_bound++)
    {
        screen.gotoXY(0, left_bound);
        screen.printChar('@');
    }
    
    // prints right wall of the well
    for(int right_bound = 0; right_bound < y; right_bound++)
    {
        screen.gotoXY(11, right_bound);
        screen.printChar('@');
    }
    
    // prints ground of the well
    for(int bottom = 0; bottom < x; bottom++)
    {
        screen.gotoXY(bottom, y);
        screen.printChar('@');
    }
    screen.refresh();
}

// Accessor method for the current piece in play
Piece* Well::getPiece()
{
    return m_piece;
}

// Accessor method for the next piece in play
Piece* Well::giveNewPiece()
{
    return m_new_piece;
}

// Mutator method for the current piece in play
void Well::setPiece(Piece* piece)
{
    m_piece = piece;
}

// Mutator method for the next piece in play
void Well::setNewPiece()
{
    m_new_piece = getNewPiece();
}

// Will become the function that returns a random piecetype each time
Piece* Well::getNewPiece()
{
    Piece* something;
    switch (chooseRandomPieceType())
    {
        case PIECE_I:
            something = new IPiece();
            break;
        case PIECE_L:
            something = new LPiece();
            break;
        case PIECE_J:
            something = new JPiece();
            break;
        case PIECE_T:
            something = new TPiece();
            break;
        case PIECE_O:
            something = new OPiece();
            break;
        case PIECE_S:
            something = new SPiece();
            break;
        case PIECE_Z:
            something = new ZPiece();
            break;
        case PIECE_CRAZY:
            something = new CrazyShape();
            break;
        case PIECE_VAPOR:
            something = new VaporBomb();
            break;
        case PIECE_FOAM:
            something = new FoamBomb();
            break;
    }
    return something;
}


// Function that should be called after the piece is finished in play. Deletes the current piece, sets it equal to the new piece, and gets a new piece.
void Well::transitionNewPiece()
{
    delete m_piece;
    m_piece = m_new_piece;
    m_new_piece = getNewPiece();
}

// clear line if there are all $'s or *'s
void Well::clearLine(Game& g)
{
    int vaporized = 0;
    for(int i = 0; i < 18; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            if(m_grid[i][j] == ' ')
            {
                break;
            }
            else if(j == 10)
            {
                for(int k = i - 1; k > 0; k--)
                {
                    for(int l = 1; l < 11; l++)
                    {
                        m_grid[k + 1][l] = m_grid[k][l];
                    }
                }
                vaporized++;
            }
        }
    }
    if(vaporized > 0)
    {
        g.changeScore(vaporized);
    }
    int rows = g.getRowsLeft();
    if(rows - vaporized > 0)
    {
        rows = rows - vaporized;
    }
    else
    {
        rows = 0;
    }
    g.decrementRowsLeft(rows);
    updateCoord();
}


// Update the stack that stores the coordinate locations of all $'s
void Well::updateCoord()
{
    // temporarily get rid of all contents
    while(m_saveLoc.empty() == false)
    {
        m_saveLoc.pop();
    }
    
    // update m_saveLoc with the new locations of $ or * signs
    for(int i = 0; i < 18; i++)
    {
        for(int j = 1; j < 11; j++)
        {
            if(m_grid[i][j] == '$' || m_grid[i][j] == '*')
            {
                Coord updated(i, j);
                m_saveLoc.push(updated);
            }
        }
    }
}

// Function that updates the screen. When the piece is finished, the screen is saved by changing the XY coordinates of the # to $ on the screen permanently. If not, the screen simply displays.
void Well::updateScreen(Screen& screen, Game& g)
{
    clearLine(g);
    // clear the lines that are full
    
    for(int i = 1; i < 11; i++)
    {
        for(int j = 0; j < 18; j++)
        {
            screen.gotoXY(i, j);
            screen.printChar(m_grid[j][i]);
        }
    }
    
    // if we're at the bottom, time to transition to a new piece and delete the old one
    if(checkBottom(screen) == false)
    {
        if(m_piece->isVapor() == false && m_piece->isFoam() == false)
        {
            saveScreen(screen);
        }
        else if(m_piece->isVapor() == true)
        {
            specialVaporFunction(screen);
        }
        else if(m_piece->isFoam() == true)
        {
            specialFoamFunction(screen);
        }
        for(int i = 1; i < 11; i++)
        {
            for(int j = 0; j < 18; j++)
            {
                screen.gotoXY(i, j);
                screen.printChar(m_grid[j][i]);
            }
        }
        transitionNewPiece();
    }
    else // display where the current piece is at (should be updated based on move)
    {
        m_piece->displayPiece(screen);
    }
    screen.refresh();
}

// Change the final location of the piece's # to $
void Well::saveScreen(Screen& screen)
{
    stack<Coord> moneyConvert;
    
    m_piece->storeXY(moneyConvert, screen);
    
    while(moneyConvert.empty() == false)
    {
        Coord coords = moneyConvert.top();
        moneyConvert.pop();
        int x_coord = coords.x();
        int y_coord = coords.y();
        m_grid[y_coord][x_coord] = '$';
        
        // push the location of all $'s onto this member variable stack m_saveLoc so that whenever we are checking whether or not we can move our piece, it must not contain a # in that coordinate.
        Coord temp_loc(y_coord, x_coord);
        m_saveLoc.push(temp_loc);
    }
}

void Well::specialVaporFunction(Screen& screen)
{
    stack<Coord> vaporLoc;
    m_piece->storeXY(vaporLoc, screen);
    
    int x_coord = 11;
    int y_coord = 0;
    while(vaporLoc.empty() == false)
    {
        Coord coord = vaporLoc.top();
        vaporLoc.pop();
        if(coord.x() <= x_coord) // set the x_coord to the left most x coordinate of vaporbomb
        {
            x_coord = coord.x();
        }
        y_coord = coord.y();
    }
    for(int i = y_coord - 2; i <= y_coord + 2; i++) // vaporbomb will clear the rows 2 above it and 2 below it
    {
        if(i >= 0 && i < 18) // must be in the well to clear
        {
            m_grid[i][x_coord] = ' ';
            m_grid[i][x_coord + 1] = ' ';
        }
    }
    updateCoord();
}

//*** SOME ERRORS NOTICED*** , sometimes, it messes with other pieces' ability to check whether or not they are bounded by something else
void Well::specialFoamFunction(Screen& screen)
{
    stack<Coord> foamLoc; // it's just one coordinate...but whatever
    m_piece->storeXY(foamLoc, screen);
    while(foamLoc.empty() == false)
    {
        Coord foam = foamLoc.top();
        foamLoc.pop();
        int x = foam.x();
        int y = foam.y();
        recursiveFoamFill(y, x, x - 2, x + 2, y - 2, y + 2);
    }
    
    updateCoord();
}

// Much like solving a maze, use a recursive call to continually drop * in places until it reaches a dead end. Constraints are determined by checking the distance from the original X Y position in that distance x value cannot be more than 2 away from original x, and y cannot be more than 2 away from original y.
void Well::recursiveFoamFill(int y, int x, int left_x, int right_x, int up_y, int bot_y)
{
    m_grid[y][x] = '*';
    if(y - 1 >= up_y && m_grid[y-1][x] == ' ')
        recursiveFoamFill(y-1, x, left_x, right_x, up_y, bot_y);
    if(y + 1 <= bot_y && m_grid[y+1][x] == ' ')
        recursiveFoamFill(y+1, x, left_x, right_x, up_y, bot_y);
    if(x - 1 >= left_x && m_grid[y][x-1] == ' ')
        recursiveFoamFill(y, x-1, left_x, right_x, up_y, bot_y);
    if(x + 1 <= right_x && m_grid[y][x+1] == ' ')
        recursiveFoamFill(y, x+1, left_x, right_x, up_y, bot_y);
}

// Checks whether or not a piece can move left
bool Well::checkLeft(Screen& screen)
{
    bool result = true;
    
    // copy over member variable stack's contents into temporary stack
    stack<Coord> leftFilled;
    leftFilled = m_saveLoc;
    
    // get the coordinates of the currently falling piece
    stack<Coord> current;
    m_piece->storeXY(current, screen);
    
    // Check all coordinates together to make sure that all of the current falling coordinates do not move right into a coordinate that is covered by a $ already
    while(leftFilled.empty() == false)
    {
        Coord coord = leftFilled.top();
        leftFilled.pop();
        int x_pos = coord.x();
        int y_pos = coord.y();
        
        while(current.empty() == false)
        {
            Coord coord_curr = current.top();
            current.pop();
            int x_pos_curr = coord_curr.x();
            int y_pos_curr = coord_curr.y();
            if(m_grid[y_pos_curr][x_pos_curr - 1] == m_grid[y_pos][x_pos] || m_grid[y_pos_curr][x_pos_curr - 1] == '*')
            {
                result = false;
                break;
            }
        }
    }
    if(result == true && m_piece->leftWallCheck(screen) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks whether or not a piece can move right
bool Well::checkRight(Screen& screen)
{
    bool result = true;
    
    // copy over member variable stack's contents into temporary stack
    stack<Coord> rightFilled;
    rightFilled = m_saveLoc;
    
    // get the coordinates of the currently falling piece
    stack<Coord> current;
    m_piece->storeXY(current, screen);
    
    // Check all coordinates together to make sure that all of the current falling coordinates do not move right into a coordinate that is covered by a $ already
    while(rightFilled.empty() == false)
    {
        Coord coord = rightFilled.top();
        rightFilled.pop();
        int x_pos = coord.x();
        int y_pos = coord.y();
        
        while(current.empty() == false)
        {
            Coord coord_curr = current.top();
            current.pop();
            int x_pos_curr = coord_curr.x();
            int y_pos_curr = coord_curr.y();
            if(m_grid[y_pos_curr][x_pos_curr + 1] == m_grid[y_pos][x_pos] || m_grid[y_pos_curr][x_pos_curr + 1] == '*')
            {
                result = false;
                break;
            }
        }
    }
    if(result == true && m_piece->rightWallCheck(screen) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}


// Check the bottom to make sure it is not a $ so the piece does not overlap it
bool Well::checkBottom(Screen& screen)
{
    bool result = true;
    
    // copy over member variable stack's contents into temporary stack
    stack<Coord> bottomFilled;
    bottomFilled = m_saveLoc;
    
    // get the coordinates of the currently falling piece
    stack<Coord> current;
    m_piece->storeXY(current, screen);
    
    // Check all coordinates together to make sure that all of the current falling coordinates do not fall into a coordinate that is covered by a $ already
    while(bottomFilled.empty() == false)
    {
        Coord coord = bottomFilled.top();
        bottomFilled.pop();
        int x_pos = coord.x();
        int y_pos = coord.y();
        
        while(current.empty() == false)
        {
            Coord coord_curr = current.top();
            current.pop();
            int x_pos_curr = coord_curr.x();
            int y_pos_curr = coord_curr.y();
            if(m_grid[y_pos_curr + 1][x_pos_curr] == m_grid[y_pos][x_pos] || m_grid[y_pos_curr + 1][x_pos_curr] == '*' )
            {
                result = false;
                break;
            }
        }
    }
    if(result == true && m_piece->bottomWallCheck(screen) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Checks if an orientation rotate can be performed without overlapping something else
bool Well::checkOrientation(Screen& screen)
{
    bool result = true;
    
    // copy over member variable stack's contents into temporary stack
    stack<Coord> oriFilled;
    oriFilled = m_saveLoc;
    
    // get the coordinates of the currently falling piece
    stack<Coord> current;
    m_piece->storeXY(current, screen);
    
    // Check all coordinates together to make sure that all of the current falling coordinates do not fall into a coordinate that is covered by a $ already
    while(oriFilled.empty() == false)
    {
        Coord coord = oriFilled.top();
        oriFilled.pop();
        int x_pos = coord.x();
        int y_pos = coord.y();
        
        while(current.empty() == false)
        {
            Coord coord_curr = current.top();
            current.pop();
            int x_pos_curr = coord_curr.x();
            int y_pos_curr = coord_curr.y();
            if(m_grid[y_pos_curr + 1][x_pos_curr] == m_grid[y_pos][x_pos] || m_grid[y_pos_curr + 1][x_pos_curr] == '*' || m_grid[y_pos_curr][x_pos_curr + 1] == m_grid[y_pos][x_pos] || m_grid[y_pos_curr][x_pos_curr + 1] == '*' || m_grid[y_pos_curr][x_pos_curr - 1] == m_grid[y_pos][x_pos] || m_grid[y_pos_curr][x_pos_curr - 1] == '*')
            {
                result = false;
                break;
            }
        }
    }
    if(result == true && m_piece->orientationWallCheck(screen) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// If a piece hits the top, end game
bool Well::gameOver()
{
    for(int k = 1; k < 11; k++)
    {
        if(m_grid[0][k] == '$' || m_grid[0][k] == '*')
        {
            return true;
        }
    }
    return false;
    
}

// Wipe the screen at the start of each level
void Well::wipeScreen()
{
    
    // empty that stack
    while(m_saveLoc.empty() == false)
    {
        m_saveLoc.pop();
    }
    
    // print the grid
    for(int i = 1; i < 11; i++)
    {
        for(int j = 0; j < 18; j++)
        {
            m_grid[j][i] = ' ';
        }
    }
}

