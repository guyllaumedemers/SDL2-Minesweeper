#pragma once
#include <headers/InputHandler.h>
#include <headers/GameManager.h>

namespace Minesweeper {
	void InputHandler::getInput(SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			break;
		default:
			break;
		}
	}
}