#pragma once
#include <SDL.h>
#include "../headers/EventHandler.h"

namespace Toolset {
	class InputHandler {
	public:
		static EventHandler* onApplicationQuitEvent;
		static EventHandler* onMouseDownEvent;
		static void getInput(SDL_Event& e);
		static void getMouseState(int&, int&);
	};
}