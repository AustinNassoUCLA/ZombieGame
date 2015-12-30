//
//  main.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Game.h"

int main(int argc, const char * argv[])
{

    // Initialize the random number generator
    srand(static_cast<unsigned int>(time(0)));
    
    // Create a game
    // Use this instead to create a mini-game:   Game g(3, 5, 2);
    Game g(20, 20, 20);
    
    // Play the game
    g.play();

    return 0;
}


/*#include "Arena.h"
#include "History.h"
#include "globals.h"
#include <iostream>

void clearscreen();
int main()
{
    Arena a(1, 4);
    a.addPlayer(1, 4);
    for (int t = 1; t <= 2; t++)
    {
        a.addZombie(1, 1);
        a.setCellStatus(1, 2, HAS_BRAIN);
        a.setCellStatus(1, 3, HAS_BRAIN);
        while (a.zombieCount() > 0)
            a.moveZombies();
    }
    clearScreen();
}*/
