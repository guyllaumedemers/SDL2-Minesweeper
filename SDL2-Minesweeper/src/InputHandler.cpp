#pragma once
#include "../headers/InputHandler.h"
#include "../headers/EventManager.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	void InputHandler::getInput(SDL_Event& e)
	{
		EventHandler* event_selected = nullptr;
		switch (e.type)
		{
		case SDL_QUIT:
			event_selected = EventManager::get("onApplicationQuitEvent");
			if (event_selected) event_selected->invoke();
			break;
		case SDL_MOUSEBUTTONDOWN:
			event_selected = EventManager::get("onMouseDownEvent");
			if (event_selected) event_selected->invoke();
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