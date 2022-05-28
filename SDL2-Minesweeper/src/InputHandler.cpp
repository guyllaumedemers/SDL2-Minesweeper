#pragma once
#include "../headers/InputHandler.h"

#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	void InputHandler::getInput(SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			break;
		case SDL_MOUSEBUTTONDOWN:
			break;
		default:
			break;
		}
	}

	void InputHandler::getMouseState(int& x, int& y)
	{
		SDL_GetMouseState(&x, &y);
	}
}