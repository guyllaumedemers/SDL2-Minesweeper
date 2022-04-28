#pragma once
#include <SDL.h>

namespace Minesweeper {
	class InputHandler {
	public:
		static void getInput(SDL_Event& e);
	};
}