//
//  Arena.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include "Arena.h"
#include "Zombie.h"
#include "Player.h"
#include "globals.h"
#include "History.h"
#include <iostream>
#include <string>

using namespace std; 
///////////////////////////////////////////////////////////////////////////
//  Arena implementation
///////////////////////////////////////////////////////////////////////////

Arena::Arena(int nRows, int nCols):history_var(nRows, nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Arena created with invalid size " << nRows << " by "
        << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nZombies = 0;
    m_turns = 0;
    for (int r = 1; r <= m_rows; r++)
        for (int c = 1; c <= m_cols; c++)
            setCellStatus(r, c, EMPTY);
}

Arena::~Arena()
{
    delete m_player;
    for (int k = 0; k<m_nZombies; k++)
        delete m_zombies[k];
    // XTODO:  release the player and all remaining dynamically allocated robots
}

int Arena::rows() const
{
    return m_rows;
}

int Arena::cols() const
{
    return m_cols;
}

Player* Arena::player() const
{
    return m_player;
}

int Arena::zombieCount() const
{
    return m_nZombies;
}

int Arena::getCellStatus(int r, int c) const
{
    checkPos(r, c);
    return m_grid[r-1][c-1];
}

int Arena::numberOfZombiesAt(int r, int c) const
{
    int count = 0;
    
    for (int k = 0; k<m_nZombies; k++)
    {
        if ((m_zombies[k]->col() == c) && (m_zombies[k]->row() == r))
            count++;
    }
    
    return count;
    // XTODO:  return the number of zombies at row r, column c
    // Delete the following line and replace it with the correct code.
    // This implementation compiles, but is incorrect.
}

void Arena::display(string msg) const
{
    char displayGrid[MAXROWS][MAXCOLS];
    int r, c;
    
    // Fill displayGrid with dots (empty) and stars (brains)
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            displayGrid[r-1][c-1] = (getCellStatus(r,c) == EMPTY ? '.' : '*');
    
    // Indicate each zombie's position
    if (m_nZombies != 0)
    {
        for (int k = 0; k<m_nZombies; k++)
        {
            int number_of_zom = (numberOfZombiesAt(m_zombies[k]->row(), m_zombies[k]->col()));
            if (number_of_zom == 1)
                displayGrid[m_zombies[k]->row()-1][m_zombies[k]->col()-1] = 'Z';
            else if (number_of_zom >= 2 && number_of_zom <= 8)
                displayGrid[m_zombies[k]->row()-1][m_zombies[k]->col()-1] = '0' + number_of_zom;
            else if (number_of_zom >= 9)
                displayGrid[m_zombies[k]->row()-1][m_zombies[k]->col()-1] = '9';
        }
    }
    
    // XTODO:  If one zombie is at some grid point, set the displayGrid char
    //        to 'Z'.  If it's 2 though 8, set it to '2' through '8'.
    //        For 9 or more, set it to '9'.
    
    // Indicate player's position
    if (m_player != nullptr)
        displayGrid[m_player->row()-1][m_player->col()-1] = (m_player->isDead() ? 'X' : '@');
    
    // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << displayGrid[r-1][c-1];
        cout << endl;
    }
    cout << endl;
    
    // Write message, zombie, and player info
    if (msg != "")
        cout << msg << endl;
    cout << "There are " << zombieCount() << " zombies remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player!" << endl;
    else if (m_player->isDead())
        cout << "The player is dead." << endl;
    cout << m_turns << " turns have been taken." << endl;
}

History& Arena:: history()
{
    return history_var;
}

void Arena::setCellStatus(int r, int c, int status)
{
    checkPos(r, c);
    m_grid[r-1][c-1] = status;
}

bool Arena::addZombie(int r, int c)
{
    if (m_nZombies == MAXZOMBIES)
        return false;
    m_zombies[m_nZombies] = new Zombie(this, r, c);
    m_nZombies++;
    return true;
}

bool Arena::addPlayer(int r, int c)
{
    // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;
    
    // Dynamically alocate a new Player and add it to the arena
    m_player = new Player(this, r, c);
    return true;
}

void Arena::moveZombies()
{
    // Move all zombies
    
    for (int k = 0; k<m_nZombies; k++)
    {
        if (m_zombies[k] != nullptr)
        {
            //Move zombies
            m_zombies[k]->move();
            if ((m_zombies[k]->col() == m_player->col()) && (m_zombies[k]->row() == m_player->row()))
                m_player->setDead();
            
            //If one zombie is dead, delete element and shift array items to the left
            if (m_zombies[k]->isDead())
            {
                history_var.record(m_zombies[k]->row(), m_zombies[k]->col()); //Record zombie position
                delete m_zombies[k];
                m_nZombies--;
                for (int i = k; i<m_nZombies; i++)
                    m_zombies[i] = m_zombies[i+1];
                m_zombies[m_nZombies] = nullptr;
            }
        }
    }
    
    // XTODO:  Move each zombie.  Mark the player as dead if necessary.
    //        Release any dead dynamically allocated zombie.
    
    // Another turn has been taken
    m_turns++;
}

void Arena::checkPos(int r, int c) const
{
    if (r < 1  ||  r > m_rows  ||  c < 1  ||  c > m_cols)
    {
        cout << "***** " << "Invalid arena position (" << r << ","
        << c << ")" << endl;
        exit(1);
    }
}

