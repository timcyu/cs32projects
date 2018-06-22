#include "Piece.h"
#include "UserInterface.h"
#include "Well.h"

Piece::Piece() : m_x(4), m_y(0), m_orientation(0)
{
}

Piece::~Piece()
{}

// Accessor method for x location in bounding box
int Piece::getX()
{
    return m_x;
}

// Accessor method for y location in bounding box
int Piece::getY()
{
    return m_y;
}

// Display function that displays the piece on the screen
void Piece::displayPiece(Screen& screen)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(getX() + j + 1, getY() + i);
            if(m_piece[m_orientation][i][j] != ' ')
            {
                screen.printChar(m_piece[m_orientation][i][j]);
            }
        }
    }
}

// Display new piece on the screen
void Piece::displayNewPiece(Screen& screen, int x, int y)
{
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(x + j, y + i);
            int ori = m_orientation;
            screen.printChar(m_piece[ori][i][j]);
        }
    }
}

// Shuffle through orientations 0 to 3. If it's in orientation 3, it should move on to orientation 0
void Piece::changeOrientation(Screen& screen, Well& well)
{
    if(well.checkOrientation(screen) == true)
    {
        if(orientationWallCheck(screen) == true)
        {
            m_orientation++;
            if(m_orientation > 3)
            {
                m_orientation = 0;
            }
        }
    }
}

// Function that moves a piece downwards on the screen
void Piece::moveDown(Screen& screen, Well& well)
{
    if(well.checkBottom(screen) == true)
    {
        if(bottomWallCheck(screen) == true)
        {
            m_y++;
        }
    }
}

// Function that moves a piece right on the screen
void Piece::moveRight(Screen& screen, Well& well)
{
    if(well.checkRight(screen) == true)
    {
        if(rightWallCheck(screen) == true)
        {
            m_x++;
        }
    }
}

// Function that moves a piece left on the screen
void Piece::moveLeft(Screen& screen, Well& well)
{
    if(well.checkLeft(screen) == true)
    {
        if(leftWallCheck(screen) == true)
        {
            m_x--;
        }
    }
}

// Function that finds the rightmost location of a # in a bounding box for checking if the piece hits the right wall
int Piece::rightMost(Screen& screen)
{
    int temp = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(getX() + j + 1, getY() + i);
            if(m_piece[m_orientation][i][j] == '#')
            {
                if(j > temp)
                {
                    temp = j;
                }
            }
            
        }
    }
    return getX() + 1 + temp;
}

// Function that finds the letmost location of a # in a bounding box for checking if the piece hits the left wall
int Piece::leftMost(Screen& screen)
{
    int temp = 11;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(getX() + j + 1, getY() + i);
            if(m_piece[m_orientation][i][j] == '#')
            {
                if(j < temp)
                {
                    temp = j;
                }
            }
            
        }
    }
    return getX() + 1 + temp;
}

// Function that finds the bottommost location of a # in a bounding box for checking if the piece hits the ground
int Piece::bottomMost(Screen& screen)
{
    int temp_y = 0;
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(getX() + j + 1, getY() + i);
            if(m_piece[m_orientation][i][j] == '#')
            {
                if(i > temp_y)
                {
                    temp_y = i; // temp stores bottommost location of # in bounding box
                }
            }
        }
    }
    return getY() + temp_y; // should store largest y value in screen
}

// Function that checks the boundary conditions of the piece's next orientation in sequence. Returns bounds by reference for checking whether or not it will the ground or walls.
void Piece::orientationMost(Screen& screen, int& rightbound, int& leftbound, int& bottombound)
{
    int box_rightbound = 0;
    int box_leftbound = 11;
    int box_bottombound = 0;
    
    // temporarily set m_orientation to a variable so we can increment it to the next orientation and test to see if it fails against some of the bounds
    int temp_or = m_orientation;
    
    temp_or++;
    if(temp_or > 3)
    {
        temp_or = 0;
    }
    
    // loop through every location of bounding box to find if there's a #, then find the box boundaries
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(getX() + j + 1, getY() + i);
            if(m_piece[temp_or][i][j] == '#')
            {
                if(j > box_rightbound)
                {
                    box_rightbound = j;
                }
                
                if(j < box_leftbound)
                {
                    box_leftbound = j;
                }
                
                if(i > box_bottombound)
                {
                    box_bottombound = i;
                }
            }
        }
    }
    
    // These store all the screen boundary conditions for the next orientation
    rightbound = getX() + 1 + box_rightbound;
    leftbound = getX() + 1 + box_leftbound;
    bottombound = getY() + box_bottombound;
}

// Taking the rightmost #, check to make sure it is less than the x coordinate of the right wall
bool Piece::rightWallCheck(Screen& screen)
{
    if(rightMost(screen) < right_x_bound)
    {
        return true;
    }
    else
        return false;
}

// Taking the leftmost #, check to make sure it is greater than the x coordinate of the left wall
bool Piece::leftWallCheck(Screen& screen)
{
    if(leftMost(screen) > left_x_bound)
    {
        return true;
    }
    else
        return false;
}

// Taking the bottommost #, check to make sure it is less than the y coordinate of the ground.
bool Piece::bottomWallCheck(Screen& screen)
{
    if(bottomMost(screen) < ground_y_bound)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Taking all 3 boundaries, check to make sure none violate any of the x, y coordinates of walls and ground.
bool Piece::orientationWallCheck(Screen& screen)
{
    int rb = 0, lb = 0, bb = 0;
    orientationMost(screen, rb, lb, bb); // go through that function and store the resulting boundary conditions in the parameters
    if(rb < right_x_bound + 1 && lb + 1 > left_x_bound && bb < ground_y_bound)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Store the xy variables of a piece's # in a stack of coordinates by reference.
void Piece::storeXY(stack<Coord>& xy, Screen& screen)
{
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            screen.gotoXY(getX() + j + 1, getY() + i);
            if(m_piece[m_orientation][i][j] == '#')
            {
                // these x and y coordinates store the location of # in the well. Lets store them in separate vectors parallely.
                int x_coord = getX() + j + 1;
                int y_coord = getY() + i;
                Coord first(y_coord, x_coord);
                xy.push(first);
            }
        }
    }
}

// Normally if inherited from the Piece class it should be false. Only VaporBomb overrides this function and returns true
bool Piece::isVapor()
{
    return false;
}


// Normally if inherited from the Piece class it should be false. Only FoamBomb overrides this function and returns true
bool Piece::isFoam()
{
    return false;
}

// Crazy shape's move left should be the same as a normal piece's move right
void CrazyShape::moveLeft(Screen& screen, Well& well)
{
    if(well.checkRight(screen) == true)
    {
        if(rightWallCheck(screen) == true)
        {
            m_x++;
        }
    }
}

// Crazy shape's move right should be the same as a normal piece's move left
void CrazyShape::moveRight(Screen& screen, Well& well)
{
    if(well.checkLeft(screen) == true)
    {
        if(leftWallCheck(screen) == true)
        {
            m_x--;
        }
    }
}

// Override
bool VaporBomb::isVapor()
{
    return true;
}

// Override
bool FoamBomb::isFoam()
{
    return true;
}

// Definition of TPiece derived class
TPiece::TPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', '#', ' ', ' '},
            {'#', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}


// Definition of LPiece derived class
LPiece::LPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', ' '},
            {'#', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {' ', ' ', '#', ' '},
            {'#', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}

// Definition of JPiece derived class
JPiece::JPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', '#'},
            {' ', ' ', ' ', '#'},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', ' ', ' ', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', '#', '#'},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}

// Definition of OPiece derived class
OPiece::OPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {'#', '#', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}


// Definition of SPiece derived class
SPiece::SPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}

// Definition of ZPiece derived class
ZPiece::ZPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', ' ', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {'#', '#', ' ', ' '},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', ' ', '#', ' '},
            {' ', '#', '#', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}

// Definition of IPiece derived class
IPiece::IPiece() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', '#'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {'#', '#', '#', '#'},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
}

// Definition of VaporBomb derived class
VaporBomb::VaporBomb() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
};

// Definition of FoamBomb derived class
FoamBomb::FoamBomb() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #3
            {' ', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
};

// Definition of crazy shape derived class
CrazyShape::CrazyShape() : Piece()
{
    char piece[4][4][4] =
    {
        {
            // orientation #0
            {'#', ' ', ' ', '#'},
            {' ', '#', '#', ' '},
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '}
        },
        {
            // orientation #1
            {' ', ' ', ' ', '#'},
            {' ', ' ', '#', ' '},
            {' ', ' ', '#', ' '},
            {' ', ' ', ' ', '#'}
        },
        {
            // orientation #2
            {' ', ' ', ' ', ' '},
            {' ', ' ', ' ', ' '},
            {' ', '#', '#', ' '},
            {'#', ' ', ' ', '#'}
        },
        {
            // orientation #3
            {'#', ' ', ' ', ' '},
            {' ', '#', ' ', ' '},
            {' ', '#', ' ', ' '},
            {'#', ' ', ' ', ' '}
        }
    };
    
    for(int i = 0; i < 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                m_piece[i][j][k] = piece[i][j][k];
            }
        }
    }
};

