// Main.cpp : Defines the entry point for the application.
//
#pragma once
#include "headers/GameManager.h"
//#ifdef SDL
#include <SDL.h>
//#endif

using namespace Toolset;
int main(int argc, char* argv[])
{
	return GameManager<SDL_Renderer, SDL_Event>::execute();
}