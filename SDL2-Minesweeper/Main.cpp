// SDL2-Minesweeper.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "headers/GameManager.h"

using namespace std;
int main(int argc, char* argv[])
{
	return Minesweeper::GameManager::execute();
}
