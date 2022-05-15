// Main.cpp : Defines the entry point for the application.
//
#pragma once
#include "headers/CRTMemoryLeak.h"
#include "headers/GameManager.h"

using namespace std;
int main(int argc, char* argv[])
{
#ifdef _DEBUG
	CRTMemoryLeak::init();
#endif
	return Minesweeper::GameManager::execute();
}