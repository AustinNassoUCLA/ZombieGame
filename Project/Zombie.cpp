//
//  Zombie.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include "Zombie.h"
#include "globals.h"
#include "Arena.h"

#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Zombie implementation
///////////////////////////////////////////////////////////////////////////

Zombie::Zombie(Arena* ap, int r, int c)
{
    if (ap == nullptr)
    {
        cout << "***** A zombie must be created in some Arena!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > ap->rows()  ||  c < 1  ||  c > ap->cols())
    {
        cout << "***** Zombie created with invalid coordinates (" << r << ","
        << c << ")!" << endl;
        exit(1);
    }
    m_arena = ap;
    m_row = r;
    m_col = c;
    brain_count = 0; //INIT BRAIN COUNT **ADDED**
    can_move = true; // **ADDED**
    m_dead = false; // **ADDED**
}

int Zombie::row() const
{
    return m_row;;
}

int Zombie::col() const
{
    return m_col;
}

bool Zombie::isDead() const
{
    
    return m_dead;
    // XTODO: return whether the Zombie is dead
    // Delete the following line and replace it with the correct code.
    // This implementation compiles, but is incorrect.
}

void Zombie::move()
{
    // XTODO:
    //   Return without moving if the zombie has eaten one brain (so is
    //   supposed to move only every other turn) and this is a turn it
    //   does not move.
    
    //   Otherwise, attempt to move in a random direction; if it can't
    //   move, don't move.  If it lands on a poisoned brain, eat the brain,
    //   so it is no longer on that grid point.
    
    int dir = randInt(NORTH, WEST);
    if (can_move)
    {
        if (attemptMove(*m_arena, dir, m_row, m_col))
        {
            if (m_arena->getCellStatus(m_row, m_col) == HAS_BRAIN)
            {
                brain_count++;
                m_arena->setCellStatus(m_row, m_col, EMPTY);
                if (brain_count==2)
                {
                    m_dead = true;
                    return;
                }
            }
            
            if (brain_count == 1)
                can_move = false;
        }
    }
    
    else
        can_move = true;
}

