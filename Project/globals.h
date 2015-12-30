//
//  globals.h
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#ifndef Project_1_globals_h
#define Project_1_globals_h

class Arena;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 50;              // max number of rows in the arena
const int MAXCOLS = 50;              // max number of columns in the arena
const int MAXZOMBIES = 500;          // max number of zombies allowed

const int NORTH = 0;
const int EAST  = 1;
const int SOUTH = 2;
const int WEST  = 3;
const int NUMDIRS = 4;

const int EMPTY      = 0;
const int HAS_BRAIN  = 1;

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int randInt(int lowest, int highest);
bool charToDir(char ch, int& dir);
bool attemptMove(const Arena& a, int dir, int& r, int& c);
bool recommendMove(const Arena& a, int r, int c, int& bestDir);
void clearScreen();


#endif
