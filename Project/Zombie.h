//
//  zombie.h
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#ifndef Project_1_zombie_h
#define Project_1_zombie_h

class Arena;  // This is needed to let the compiler know that Arena is a
// type name, since it's mentioned in the Zombie declaration.

class Zombie
{
public:
    // Constructor
    Zombie(Arena* ap, int r, int c);
    
    // Accessors
    int  row() const;
    int  col() const;
    bool isDead() const;
    
    // Mutators
    void move();
    
private:
    Arena* m_arena;
    int    m_row;
    int    m_col;
    int brain_count; //**ADDED**
    bool can_move; //**ADDED**
    bool m_dead; //**ADDED**
    // XTODO: You'll probably find that a zombie object needs additional
    // data members to support your implementation of the behavior affected
    // by poisoned brains.
};

#endif
