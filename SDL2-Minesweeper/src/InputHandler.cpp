#pragma once
#include "../headers/InputHandler.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
#ifdef _DEBUG
	EventHandler* InputHandler::onApplicationQuitEvent = DBG_NEW EventHandler();
	EventHandler* InputHandler::onMouseDownEvent = DBG_NEW EventHandler();
#else
	EventHandler* InputHandler::onApplicationQuitEvent = new EventHandler();
	EventHandler* InputHandler::onMouseDownEvent = new EventHandler();
#endif

	void InputHandler::getInput(SDL_Event& e)
	{
		switch (e.type)
		{
		case SDL_QUIT:
			if (onApplicationQuitEvent) onApplicationQuitEvent->invoke();
			break;
		case SDL_MOUSEBUTTONDOWN:
			if (onMouseDownEvent) onMouseDownEvent->invoke();
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