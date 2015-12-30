//
//  History.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include "History.h"
#include "globals.h"

#include <iostream>

using namespace std;

History::History(int nRows, int nCols)
{
    //Initialize row and col vars
    n_rows = nRows;
    n_cols = nCols; 
    
    //Create grid
    for (int i = 0; i<n_rows; i++)
        for (int k = 0; k<n_cols; k++)
            char_grid[i][k] = '.';
}

bool History::record(int r, int c)
{
    if (r < 1 || r > n_rows || c < 1 || c > n_cols)
        return false;
    
    else
    {
        if (char_grid[r-1][c-1] == 'Z')
            return true;
        
        if (char_grid[r-1][c-1] == '.')
            char_grid[r-1][c-1] = 'A';
        else
            char_grid[r-1][c-1]++;
        
        return true;
    }
}

void History::display() const
{
    clearScreen();
    for (int r = 1; r <= n_rows; r++)
    {
        for (int c = 1; c <= n_cols; c++)
            cout << char_grid[r-1][c-1];
        cout << endl;
    }
    
    cout << endl;
}