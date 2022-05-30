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
		switch (e.type)
		{
		case SDL_QUIT:
			EventHandler::invoke<bool>("onApplicationQuit", true);
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				EventHandler::invoke<int>("onMouseDown", 0);
				break;
			case SDL_BUTTON_RIGHT:
				EventHandler::invoke<int>("onMouseDown", 1);
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