#ifndef PIECE_INCLUDED
#define PIECE_INCLUDED

#include <stack>

using namespace std;

class Screen;
class Well;

enum PieceType {
    PIECE_I, PIECE_L, PIECE_J, PIECE_T, PIECE_O, PIECE_S, PIECE_Z, PIECE_VAPOR, PIECE_FOAM, PIECE_CRAZY
};

const int box_height = 4;
const int box_width = 4;
const int num_of_orientations = 4;
const int right_x_bound = 10;
const int left_x_bound = 1;
const int ground_y_bound = 17;

PieceType chooseRandomPieceType();

class Coord
{
public:
    Coord(int yy, int xx) : m_y1(yy), m_x1(xx)
    {
    }
    int y() const
    {
        return m_y1;
    }
    int x() const
    {
        return m_x1;
    }
private:
    int m_y1;
    int m_x1;
};

class Piece
{
public:
    Piece();
    virtual ~Piece();
    
    int getX();
    int getY();
    
    void displayPiece(Screen& screen);
    void displayNewPiece(Screen& screen, int x, int y);
    
    
    void changeOrientation(Screen& screen, Well& well);
    void moveDown(Screen& screen, Well& well);
    virtual void moveRight(Screen& screen, Well& well);
    virtual void moveLeft(Screen& screen, Well& well);
    
    int rightMost(Screen& screen); // function that returns the largest # containing x coordinate of bounding box
    int leftMost(Screen& screen); // function that returns smallest # containing x coordinate of bounding box
    int bottomMost(Screen& screen);
    void orientationMost(Screen& screen, int& rightbound, int& leftbound, int& bottombound); // grabs the rightmost, leftmost, and bottommost # containing x and y coordinates of the next orientation
    bool rightWallCheck(Screen& screen); // checks whether or not you can move right (prevent overlap) needs a function that returns rightmost used col of the bounding box to use to check.
    bool leftWallCheck(Screen& screen); // checks whether or not you can move left (prevent overlap) needs a function that returns leftmost used col of the bounding box to use to check.
    bool bottomWallCheck(Screen& screen); // checks whether or not you can move down (prevent overlap) needs a function that returns bottommost used row of the bounding box to use to check.
    bool orientationWallCheck(Screen& screen); // a function that checks to make sure it is okay to rotate
    
    void storeXY(stack<Coord>& xy, Screen& screen);
    
    virtual bool isVapor();
    virtual bool isFoam();
    
    
    // protected because want derived classes to be able to access m_piece. I know this is terrible and violates encapsulation but I'm sorry I didn't have time to fix it. At least it works right...
protected:
    char m_piece[num_of_orientations][box_height][box_width];
    int m_x, m_y, m_orientation;
};


class TPiece : public Piece
{
public:
    TPiece();
};

class LPiece : public Piece
{
public:
    LPiece();
};

class JPiece : public Piece
{
public:
    JPiece();
};

class OPiece : public Piece
{
public:
    OPiece();
};

class SPiece : public Piece
{
public:
    SPiece();
};

class ZPiece : public Piece
{
public:
    ZPiece();
};

class IPiece : public Piece
{
public:
    IPiece();
};

class VaporBomb : public Piece
{
public:
    VaporBomb();
    virtual bool isVapor();
};

class FoamBomb : public Piece
{
public:
    FoamBomb();
    virtual bool isFoam();
};

class CrazyShape : public Piece
{
public:
    CrazyShape();
    virtual void moveRight(Screen& screen, Well& well);
    virtual void moveLeft(Screen& screen, Well& well);
};


#endif // PIECE_INCLUDED

