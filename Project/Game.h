//
//  Game.h
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#ifndef Project_1_Game_h
#define Project_1_Game_h

#include <string>

class Arena;

class Game
{
public:
    // Constructor/destructor
    Game(int rows, int cols, int nZombies);
    ~Game();
    
    // Mutators
    void play();
    
private:
    Arena* m_arena;
    
    // Helper functions
    std::string takePlayerTurn();
};

#endif
