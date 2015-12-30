//
//  Player.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include "Player.h"
#include "globals.h"
#include "Arena.h"

#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Player implementation
///////////////////////////////////////////////////////////////////////////

Player::Player(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** The player must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
        << "," << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

string Player::dropBrain()
{
    if (m_arena->getCellStatus(m_row, m_col) == HAS_BRAIN)
        return "There's already a brain at this spot.";
    m_arena->setCellStatus(m_row, m_col, HAS_BRAIN);
    return "A brain has been dropped.";
}

string Player::move(int dir)
{
    if (attemptMove(*m_arena, dir, m_row, m_col))
    {
        if (m_arena->numberOfZombiesAt(m_row, m_col) != 0)
        {
            m_dead = true;
            return "Player walked into a zombie and died.";
        }
        
        else
        {
            switch (dir)
            {
                case NORTH: return "Player moved north."; break;
                case WEST: return "Player moved west."; break;
                case EAST: return "Player moved east."; break;
                case SOUTH: return "Player moved south."; break;
            }
        }
    }
    // XTODO:  Attempt to move the player one step in the indicated
    //        direction.  If this fails,
    //        return "Player couldn't move; player stands."
    //        A player who moves onto a zombie dies, and this
    //        returns "Player walked into a zombie and died."
    //        Otherwise, return one of "Player moved north.",
    //        "Player moved east.", "Player moved south.", or
    //        "Player moved west."
    return "Player couldn't move; player stands.";  // This implementation compiles, but is incorrect.
}

bool Player::isDead() const
{
    return m_dead;
    // XTODO: return whether the Player is dead
    // Delete the following line and replace it with the correct code.
    // This implementation compiles, but is incorrect.
}

void Player::setDead()
{
    m_dead = true;
}

