#pragma once
#include "../headers/InputHandler.h"
#include "../headers/GameManager.h"

using namespace Minesweeper;
namespace Toolset {
	void InputHandler::getInput(SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			GameManager::exit();
			break;
		default:
			break;
		}
	}
}