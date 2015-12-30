//
//  History.h
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#ifndef __Project_1__History__
#define __Project_1__History__

#include "globals.h"

class History
{
public:
    History(int nRows, int nCols);
    bool record(int r, int c);
    void display() const;
    
private:
    int n_rows;
    int n_cols;
    char char_grid[MAXROWS][MAXCOLS];
};

#endif /* defined(__Project_1__History__) */
