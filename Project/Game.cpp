//
//  Game.cpp
//  Project 1
//
//  Created by Austin Nasso on 1/10/14.
//  Copyright (c) 2014 Austin Nasso. All rights reserved.
//

#include "Game.h"
#include "globals.h"
#include "Arena.h" 
#include "Player.h"

#include <iostream>
#include <string>

using namespace std;

///////////////////////////////////////////////////////////////////////////
//  Game implementation
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nZombies)
{
    if (nZombies < 0  ||  nZombies > MAXZOMBIES)
    {
        cout << "***** Game created with invalid number of zombies:  "
        << nZombies << endl;
        exit(1);
    }
    int nEmpty = rows * cols - nZombies - 1;  // 1 for Player
    if (nEmpty < 0)
    {
        cout << "***** Game created with a " << rows << " by "
        << cols << " arena, which is too small too hold a player and "
        << nZombies << " zombies!" << endl;
        exit(1);
    }
    
    // Create arena
    m_arena = new Arena(rows, cols);
    
    // Add player
    int rPlayer;
    int cPlayer;
    do
    {
        rPlayer = randInt(1, rows);
        cPlayer = randInt(1, cols);
    } while (m_arena->getCellStatus(rPlayer, cPlayer) != EMPTY);
    m_arena->addPlayer(rPlayer, cPlayer);
    
    // Populate with zombies
    while (nZombies > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);
        if (r == rPlayer && c == cPlayer)
            continue;
        m_arena->addZombie(r, c);
        nZombies--;
    }
}

Game::~Game()
{
    delete m_arena;
}

string Game::takePlayerTurn()
{
    for (;;)
    {
        cout << "Your move (n/e/s/w/x/h or nothing): ";
        string playerMove;
        getline(cin, playerMove);
        
        Player* player = m_arena->player();
        int dir;
        
        if (playerMove.size() == 0)
        {
            if (recommendMove(*m_arena, player->row(), player->col(), dir))
                return player->move(dir);
            else
                return player->dropBrain();
        }
        else if (playerMove.size() == 1)
        {
            if (tolower(playerMove[0]) == 'x')
                return player->dropBrain();
            else if (tolower(playerMove[0]) == 'h')
            {
               return "Display history";
            }
            else if (charToDir(playerMove[0], dir))
                return player->move(dir);
        }
        cout << "Player move must be nothing, or 1 character n/e/s/w/x/h." << endl;
    }
}

void Game::play()
{
    m_arena->display("");
    while ( ! m_arena->player()->isDead()  &&  m_arena->zombieCount() > 0)
    {
        string msg = takePlayerTurn();
        if (msg == "Display history")
        {
            m_arena->history().display();
            cout << "Press enter to continue";
            cin.ignore(1000, '\n');
            m_arena->display("");
            continue;
        }
        Player* player = m_arena->player();
        if (player->isDead())
            break;
        m_arena->moveZombies();
        m_arena->display(msg);
    }
    if (m_arena->player()->isDead())
        cout << "You lose." << endl;
    else
        cout << "You win." << endl;
}

