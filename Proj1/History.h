//
//  History.h
//  CS32Project1
//
//  Created by Tim Yu on 4/5/18.
//  Copyright © 2018 CS32. All rights reserved.
//

#ifndef History_h
#define History_h

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
private:
    int m_Rows;
    int m_Cols;
    char m_Grid[MAXROWS][MAXCOLS];
};
#endif /* History_h */
