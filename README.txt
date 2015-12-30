INTRODUCTION
------------
DATE CREATED: December 2013

PROJECT: Zombie ASCII Based Game (CS32: Project 1)

LANGUAGES EMPLOYED: C++

DESCRIPTION: This is a school project where our task was to complete functions in the Zombie game given a basic OOP game framework. One of the more interesting functions we had to implement was recommend move. Basically, in the game there is a player (indicated by '@') who's task is to avoid all zombies (indicated by 'Z'). Each turn the player can move north ('n'), south ('s'), east ('e'), west ('w'), drop a bomb ('x'), see where zombies died ('h'), or do nothing (which calls the recommend move function). If nothing is entered, the recommend move function will automatically choose a beneficial move for the player. I programmed the recommend move function to systematically drop bombs (indicated by '*' in game) in the least occupied parts of the map while avoiding all zombies. My implementation of the function wins the game nearly every time (if the user were to simply press enter without entering a move). 

HOW TO RUN
-----------
1. In a unix based terminal execute with command: ./Zombie