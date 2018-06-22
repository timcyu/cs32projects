//
//  History.cpp
//  CS32Project1
//
//  Created by Tim Yu on 4/5/18.
//  Copyright © 2018 CS32. All rights reserved.
//

#include <iostream>
using namespace std;

#include "History.h"
History::History(int nRows, int nCols)
{
    m_Rows = nRows;
    m_Cols = nCols;
    for(int r = 1; r <= nRows; r++)
    {
        for(int c = 1; c <= nCols; c++)
        {
            m_Grid[r][c] = '.'; // At beginning, all '.' since no flatulans have been preached yet
        }
    }
}

bool History::record(int r, int c)
{
    if(r < 1 || r > m_Rows || c < 1 || c > m_Cols)
    {
        return false; // Must be inside the city, with top left being [1][1]!
    }
    else
    {
        if(m_Grid[r][c] == '.')
        {
            m_Grid[r][c] = 'A';
        }
        else if(m_Grid[r][c] >= 'A' && m_Grid[r][c] < 'Z')
        {
            m_Grid[r][c]++;
        } // Increment from A -> Z after each flatulan is converted at some gridpoint
        return true;
    }
}

void History::display() const
{
    clearScreen(); // Clears the screen first
    for(int r = 1; r <= m_Rows; r++)
    {
        for(int c = 1; c <= m_Cols; c++)
        {
            cout << m_Grid[r][c]; // Displays the history grid
        }
        cout << endl;
    }
    cout << endl;
}





