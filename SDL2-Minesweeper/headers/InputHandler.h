#pragma once
#include <SDL.h>

namespace Toolset {
	class InputHandler {
	public:
		static void getInput(SDL_Event& e);
		static void getMouseState(int&, int&);
	};
}