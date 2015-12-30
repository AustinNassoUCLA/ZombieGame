//
//  utilities.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include "globals.h" 
#include "Arena.h"


#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cctype>
#include <ctime>
#include <cassert>

using namespace std;
///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementation
///////////////////////////////////////////////////////////////////////////

// Return a uniformly distributed random int from lowest to highest, inclusive
int randInt(int lowest, int highest)
{
    if (highest < lowest)
        swap(highest, lowest);
    return lowest + (rand() % (highest - lowest + 1));
}

bool charToDir(char ch, int& dir)
{
    switch (tolower(ch))
    {
        default:  return false;
        case 'n': dir = NORTH; break;
        case 'e': dir = EAST;  break;
        case 's': dir = SOUTH; break;
        case 'w': dir = WEST;  break;
    }
    return true;
}

// Return false without changing anything if moving one step from (r,c)
// in the indicated direction would run off the edge of the arena.
// Otherwise, update r and c to the position resulting from the move and
// return true.
bool attemptMove(const Arena& a, int dir, int& r, int& c)
{
    switch (dir)
    {
        case SOUTH:
            if (r+1<=a.rows())
            {
                r++;
                break;
            }
            
            else return false;
        case EAST:
            if (c+1<=a.cols())
            {
                c++;
                break;
            }
            
            else return false;
        case WEST:
            if (c-1>=1)
            {
                c--;
                break;
            }
            
            else return false;
        case NORTH:
            if (r-1>=1)
            {
                r--;
                break;
            }
            
            else return false;
        default: return false;
    }
    
    return true;
    
    
    // XTODO:  implement this function
    // Delete the following line and replace it with the correct code.
    // This implementation compiles, but is incorrect.
}

void DirectionPossibilities(int arena_r, int arena_c, int c, int r, bool* n, bool* s, bool* e, bool* w, bool gridOccupied[][MAXCOLS])
{
    int index_r = r-1;
    int index_c = c-1;
    
    //Possible moves due to zombies + corners
    if (r != arena_r && c != 1)
    {
        if (gridOccupied[index_r+1][index_c-1]) //Southwest
        {
            *s = false;
            *w = false;
        }
    }
    
    if (r==arena_r && c==1) //SOUTHWEST CORNER
    {
        *s = false;
        *w = false;
    }
    
    if (r!=1 && c!= 1)
    {
        if (gridOccupied[index_r-1][index_c-1]) //Northwest
        {
            *n = false;
            *w = false;
        }
    }
    
    if (r==1 && c==1) //NORTHWEST CORNER
    {
        *n = false;
        *w = false;
    }
    
    if (r!=arena_r && c!=arena_c)
    {
        if (gridOccupied[index_r+1][index_c+1]) //Southeast
        {
            *s = false;
            *e = false;
        }
    }
    
    if (r==arena_r && c==arena_c) //SOUTHEAST CORNER
    {
        *s = false;
        *e = false;
    }
    
    if (r != 1 && c != arena_c)
    {
        if (gridOccupied[index_r-1][index_c+1]) //Northeast
        {
            *n = false;
            *e = false;
        }
    }
    
    if (r==1 && c==arena_c) //NORTHEAST CORNER
    {
        *n = false;
        *e = false;
    }
    
    
    //Check if on perimeter (not corner); if not, check for zombies
    if (c != arena_c)
    {
        if (gridOccupied[index_r][index_c+1]) //East
            *e = false;
    }
    
    if (c==arena_c) //EAST SIDE
        *e = false;
    
    if (c!=1)
    {
        if (gridOccupied[index_r][index_c-1]) //West
            *w = false;
    }
    
    if (c==1) //WEST SIDE
        *w = false;
    
    if (r!=arena_r)
    {
        if (gridOccupied[index_r+1][index_c]) //South
            *s = false;
    }
    
    if (r==arena_r) //SOUTH SIDE
        *s = false;
    
    if (r!=1)
    {
        if (gridOccupied[index_r-1][index_c]) //North
            *n = false;
    }
    
    if (r==1) //NORTH SIDE
        *n = false;
    
    if (r>=3) //Zombies two spaces away to north
        if (gridOccupied[index_r-2][index_c])
            *n = false;
    
    if (c>=3) //Zombies two spaces away to west
        if (gridOccupied[index_r][index_c-2])
            *w = false;
    
    if (c<=arena_c-2) //Zombies two spaces away to east
        if (gridOccupied[index_r][index_c+2])
            *e = false;
    
    if (r<=arena_r-2) //Zombies two spaces away to south
        if (gridOccupied[index_r+2][index_c])
            *s = false;
    
}

void brainGridAnalysis(int rows, int cols, const bool brainAtpos[][MAXCOLS], int &recDir)
{
    //DIVIDE GRID INTO 9 PIECES
    int row_split_1, row_split_2, col_split_1, col_split_2;
    int northwest_total = 0, north_total = 0, northeast_total = 0;
    int west_total = 0, central_total = 0, east_total = 0;
    int southwest_total = 0, south_total = 0, southeast_total = 0;
    int top_total, bottom_total, right_total, left_total;
    
    row_split_1 = (rows/3);
    row_split_2 = 2*row_split_1;
    col_split_1 = (cols/3);
    col_split_2 = 2*col_split_1;
    
    //ADD UP BRAINS IN EACH REGION
    
    //LEFT
    for (int k = 0; k<row_split_1; k++)
        for (int i = 0; i<col_split_1; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                northwest_total++;
        }
    
    for (int k = row_split_1; k<row_split_2; k++)
        for (int i = 0; i<col_split_1; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                west_total++;
        }
    
    for (int k = row_split_2; k<rows; k++)
        for (int i = 0; i<col_split_1; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                southwest_total++;
        }
    //MIDDLE
    for (int k = 0; k<row_split_1; k++)
        for (int i = col_split_1; i<col_split_2; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                north_total++;
        }
    
    for (int k = row_split_1; k<row_split_2; k++)
        for (int i = col_split_1; i<col_split_2; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                central_total++;
        }
    
    for (int k = row_split_2; k<rows; k++)
        for (int i = col_split_1; i<col_split_2; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                south_total++;
        }
    
    //RIGHT
    for (int k = 0; k<row_split_1; k++)
        for (int i = col_split_2; i<cols; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                northeast_total++;
        }
    
    for (int k = row_split_1; k<row_split_2; k++)
        for (int i = col_split_2; i<cols; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                east_total++;
        }
    
    for (int k = row_split_2; k<rows; k++)
        for (int i = col_split_2; i<cols; i++)
        {
            if (brainAtpos[k][i] == HAS_BRAIN)
                southeast_total++;
        }
    
    top_total = northeast_total + northwest_total + north_total;
    bottom_total = southeast_total + southwest_total + south_total;
    left_total = northwest_total + west_total + southwest_total;
    right_total = northeast_total + east_total + southeast_total;
    
    if (top_total > bottom_total && top_total > left_total && top_total > right_total)
        recDir = SOUTH;
    
    if (bottom_total > top_total && bottom_total > left_total && bottom_total > right_total)
        recDir = NORTH;
    
    if (left_total > top_total && left_total > bottom_total && left_total > right_total)
        recDir = EAST;
    
    if (right_total > top_total && right_total > bottom_total && right_total > left_total)
        recDir = WEST;
    
}
// Recommend a move for a player at (r,c):  A false return means the
// recommendation is that the player should drop a brain and not move;
// otherwise, this function sets bestDir to the recommended direction
// to move and returns true.
bool recommendMove(const Arena& a, int r, int c, int& bestDir)
{
    
    //TRUE/FALSE GRID INDICATES OCCUPIED SPACES, possible moves, alternating behavior, brain status of current position
    bool gridOccupied[MAXROWS][MAXCOLS], brainAtPos[MAXROWS][MAXCOLS], move[4], alternating, status_current_pos;
    status_current_pos = a.getCellStatus(r, c);
    
    //Set alternating variable
    int n = randInt(2, 3);
    int index_r = r-1, index_c = c-1;
    alternating = ((randInt(1,n) == 1)) ? true : false; //LESS LIKELY TO BE TRUE
    
    //Initialize move possibilities to true
    for (int i = 0; i < 4; i++)
        move[i] = true;
    
    for (int k = 0; k<a.rows(); k++)
        for (int i = 0; i<a.cols(); i++)
        {
            if (a.numberOfZombiesAt(k+1, i+1) == 0)
                gridOccupied[k][i] = false;
            
            else gridOccupied[k][i] = true;
            
            if (a.getCellStatus(k+1, i+1) == EMPTY)
                brainAtPos[k][i] = false;
            
            else brainAtPos[k][i] = true;
        }
    
    DirectionPossibilities(a.rows(), a.cols(), c, r, move+NORTH, move+SOUTH, move+EAST, move+WEST, gridOccupied);
    
    //If in the body of the grid
    if (c!=1 && c!=a.cols() && r!= 1 && r!=a.rows())
    {
        int possible_moves = 0;
        int wall_moves = 0;
        
        //Possible wall moves
        if (c+1 == a.cols())
            wall_moves++;
        
        if (c-1 == 1)
            wall_moves++;
        
        if (r-1 == 1)
            wall_moves++;
        
        if (r+1 == a.rows())
            wall_moves++;
        
        for (int i = 0; i<4; i++)
        {
            if (move[i])
                possible_moves++;
        }
        
        if (possible_moves>1 && wall_moves<=1 && !alternating) //If only one wall move out of options, don't move there
        {
            if (r+1==a.rows())
                move[SOUTH] = false;
            
            if (r-1==1)
                move[NORTH] = false;
            
            if (c+1==a.cols())
                move[EAST] = false;
            
            if (c-1==1)
                move[WEST] = false;
        }
        
        if (possible_moves==4 && status_current_pos==EMPTY && !alternating) //If no threat, drop a poisoned brain sometimes
        {
            return false;
        }
        
        if (possible_moves==4)
        {
            int recDir;
            
            //When the option to go into a spot where a brain doesnt exist is available, go to that spot
            if (! ((brainAtPos[index_r+1][index_c]==HAS_BRAIN) && (brainAtPos[index_r-1][index_c]==HAS_BRAIN) && (brainAtPos[index_r][index_c+1]==HAS_BRAIN) && (brainAtPos[index_r][index_c-1]==HAS_BRAIN)))
            {
                
                if (brainAtPos[index_r+1][index_c]==HAS_BRAIN)
                    move[SOUTH] = false;
                
                if (brainAtPos[index_r-1][index_c]==HAS_BRAIN)
                    move[NORTH] = false;
                
                if (brainAtPos[index_r][index_c+1]==HAS_BRAIN)
                    move[EAST] = false;
                
                if (brainAtPos[index_r][index_c-1]==HAS_BRAIN)
                    move[WEST] = false;
            }
            
            else //When surrounded by brains, go away from them
            {
                brainGridAnalysis(a.rows(), a.cols(), brainAtPos, recDir);
                if (recDir == NORTH)
                {
                    move[SOUTH] = false;
                    move[WEST] = false;
                    move[EAST] = false;
                }
                
                if (recDir == SOUTH)
                {
                    move[NORTH] = false;
                    move[WEST] = false;
                    move[EAST] = false;
                }
                
                if (recDir == WEST)
                {
                    move[SOUTH] = false;
                    move[NORTH] = false;
                    move[EAST] = false;
                }
                
                if (recDir == EAST)
                {
                    move[SOUTH] = false;
                    move[WEST] = false;
                    move[NORTH] = false;
                }
            }
        }
        
        //Select move
        for (int i = 0; i<4; i++)
        {
            if (alternating)
                i = 3-i;
            
            if (move[i])
            {
                bestDir = i;
                return true;
            }
            
            if (alternating)
                i = 3-i;
        }
        return false;
    }
    
    else //IF SIDE, TRY TO GET OFF OF SIDE
    {
        int possible_moves = 0;
        for (int i = 0; i<4; i++)
        {
            if (move[i])
                possible_moves++;
        }
        
        if (possible_moves>1 && alternating)
        {
            if (r==1 && c!=1 && c!=a.cols() && move[SOUTH]) //NORTH SIDE
            {
                move[EAST] = false;
                move[WEST] = false;
            }
            
            if (c==1 && r!=1 && r!=a.rows() && move[EAST]) //WEST SIDE
            {
                move[NORTH] = false;
                move[SOUTH] = false;
            }
            
            if (r==a.rows() && c!=1 && c!=a.cols() && move[NORTH]) //SOUTH SIDE
            {
                move[EAST] = false;
                move[WEST] = false;
            }
            
            if (c==a.cols() && r!=1 && r!=a.rows() && move[WEST]) //EAST SIDE
            {
                move[NORTH] = false;
                move[SOUTH] = false;
            }
        }
        
        if (possible_moves==3 && status_current_pos==EMPTY && !alternating) //If no threat, drop a poisoned brain
        {
            return false;
        }
        
        if (!alternating && possible_moves==3) //If current position occupied by brain
        {
            int recDir;
            bool sideFound = true;
            
            if (!(move[WEST]) && sideFound)
            {
                if (!((brainAtPos[index_r+1][index_c]==HAS_BRAIN) && (brainAtPos[index_r-1][index_c]==HAS_BRAIN) && (brainAtPos[index_r][index_c+1]==HAS_BRAIN)))
                {
                    if (brainAtPos[index_r+1][index_c]==HAS_BRAIN)
                        move[SOUTH] = false;
                    
                    if (brainAtPos[index_r-1][index_c]==HAS_BRAIN)
                        move[NORTH] = false;
                    
                    if (brainAtPos[index_r][index_c+1]==HAS_BRAIN)
                        move[EAST] = false;
                }
                
                else
                {
                    brainGridAnalysis(a.rows(), a.cols(), brainAtPos, recDir);
                    if (recDir == NORTH)
                    {
                        move[SOUTH] = false;
                        move[WEST] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == SOUTH)
                    {
                        move[NORTH] = false;
                        move[WEST] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == EAST)
                    {
                        move[SOUTH] = false;
                        move[WEST] = false;
                        move[NORTH] = false;
                    }
                }
                
                sideFound = false;
            }
            
            if (!(move[EAST]) && sideFound)
            {
                if (!((brainAtPos[index_r+1][index_c]==HAS_BRAIN) && (brainAtPos[index_r-1][index_c]==HAS_BRAIN) && (brainAtPos[index_r][index_c-1]==HAS_BRAIN)))
                {
                    if (brainAtPos[index_r+1][index_c]==HAS_BRAIN)
                        move[SOUTH] = false;
                    
                    if (brainAtPos[index_r-1][index_c]==HAS_BRAIN)
                        move[NORTH] = false;
                    
                    if (brainAtPos[index_r][index_c-1]==HAS_BRAIN)
                        move[WEST] = false;
                }
                
                else
                {
                    brainGridAnalysis(a.rows(), a.cols(), brainAtPos, recDir);
                    if (recDir == NORTH)
                    {
                        move[SOUTH] = false;
                        move[WEST] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == SOUTH)
                    {
                        move[NORTH] = false;
                        move[WEST] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == WEST)
                    {
                        move[SOUTH] = false;
                        move[NORTH] = false;
                        move[EAST] = false;
                    }
                }
                
                sideFound = false;
            }
            
            if (!(move[SOUTH]) && sideFound)
            {
                if (!((brainAtPos[index_r][index_c+1]==HAS_BRAIN) && (brainAtPos[index_r-1][index_c]==HAS_BRAIN) && (brainAtPos[index_r][index_c-1]==HAS_BRAIN)))
                {
                    if (brainAtPos[index_r][index_c+1]==HAS_BRAIN)
                        move[EAST] = false;
                    
                    if (brainAtPos[index_r-1][index_c]==HAS_BRAIN)
                        move[NORTH] = false;
                    
                    if (brainAtPos[index_r][index_c-1]==HAS_BRAIN)
                        move[WEST] = false;
                }
                
                else
                {
                    brainGridAnalysis(a.rows(), a.cols(), brainAtPos, recDir);
                    if (recDir == NORTH)
                    {
                        move[SOUTH] = false;
                        move[WEST] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == WEST)
                    {
                        move[SOUTH] = false;
                        move[NORTH] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == EAST)
                    {
                        move[SOUTH] = false;
                        move[WEST] = false;
                        move[NORTH] = false;
                    }
                }
                sideFound = false;
            }
            
            if (!(move[NORTH]) && sideFound)
            {
                if (!((brainAtPos[index_r+1][index_c]==HAS_BRAIN) && (brainAtPos[index_r][index_c+1]==HAS_BRAIN) && (brainAtPos[index_r][index_c-1]==HAS_BRAIN)))
                {
                    if (brainAtPos[index_r+1][index_c]==HAS_BRAIN)
                        move[SOUTH] = false;
                    
                    if (brainAtPos[index_r][index_c+1]==HAS_BRAIN)
                        move[EAST] = false;
                    
                    if (brainAtPos[index_r][index_c-1]==HAS_BRAIN)
                        move[WEST] = false;
                }
                
                else
                {
                    brainGridAnalysis(a.rows(), a.cols(), brainAtPos, recDir);
                    if (recDir == SOUTH)
                    {
                        move[NORTH] = false;
                        move[WEST] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == WEST)
                    {
                        move[SOUTH] = false;
                        move[NORTH] = false;
                        move[EAST] = false;
                    }
                    
                    if (recDir == EAST)
                    {
                        move[SOUTH] = false;
                        move[WEST] = false;
                        move[NORTH] = false;
                    }
                }
                
            }
            sideFound = false;
        }
        
        //Select Move
        for (int i = 0; i<4; i++)
        {
            if (!alternating)
                i = 3-i;
            
            if (move[i])
            {
                bestDir = i;
                return true;
            }
            
            if (!alternating)
                i = 3-i;
        }
        
        return false;
    }
    
    return false;
}

// TODO:  implement this function
// Delete the following line and replace it with your code.
// This implementation compiles, but is incorrect.

// Your replacement implementation should do something intelligent.
// You don't have to be any smarter than the following, although
// you can if you want to be:  If staying put runs the risk of a
// zombie possibly moving onto the player's location when the zombies
// move, yet moving in a particular direction puts the player in a
// position that is safe when the zombies move, then the chosen
// action is to move to a safer location.  Similarly, if staying put
// is safe, but moving in certain directions puts the player in danger,
// then the chosen action should not be to move in one of the
// dangerous directions; instead, the player should stay put or move to
// another safe position.  In general, a position that may be moved to
// by many zombies is more dangerous than one that may be moved to by
// few.
//
// Unless you want to, you do not have to take into account that a
// zombie might be poisoned and thus sometimes less dangerous than one
// that is not.  That requires a more sophisticated analysis that
// we're not asking you to do.

// DO NOT MODIFY THE CODE BETWEEN HERE AND THE MAIN ROUTINE
#ifdef _MSC_VER  //  Microsoft Visual C++

#include <windows.h>

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                               &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not Microsoft Visual C++, so assume UNIX interface

#include <cstring>

void clearScreen()
{
    static const char* term = getenv("TERM");
    static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
}

#endif
