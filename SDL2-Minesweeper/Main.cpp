// Main.cpp : Defines the entry point for the application.
//
#ifndef INCLUDED_MAIN
#define INCLUDED_MAIN

#include "headers/GameManager.h"
#include <ctime>

//TODO I want to create an Include Guard that generate a MACRO according to the graphical api lib used in the project
//TODO so that users have the freedom of using the same basic setup for running the Gameloop and branch off according to the created MACRO in the subsequent scripts.

int main(int argc, char* argv[])
{
    srand(time(NULL));
    return Minesweeper::GameManager<SDL_Renderer, SDL_Event>::execute();
}
#endif
