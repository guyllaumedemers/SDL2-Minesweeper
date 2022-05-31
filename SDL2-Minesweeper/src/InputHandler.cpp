#pragma once
#include "../headers/InputHandler.h"
#include "../headers/EventHandler.h"

#include <string>
#include <iostream>

#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
	void InputHandler::getInput(SDL_Event& e)
	{
		static const string event_keys[] = { "onApplicationQuit", "onMouseDown" };

		switch (e.type)
		{
		case SDL_QUIT:
			EventHandler::invoke<bool>(event_keys[0], true);
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				EventHandler::invoke<int>(event_keys[1], 0);
				break;
			case SDL_BUTTON_RIGHT:
				EventHandler::invoke<int>(event_keys[1], 1);
				break;
			}
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