// Main.cpp : Defines the entry point for the application.
//
#pragma once

#include "headers/GameManager.h"

using namespace std;
int main(int argc, char* argv[])
{
	return Minesweeper::GameManager::execute();
}
