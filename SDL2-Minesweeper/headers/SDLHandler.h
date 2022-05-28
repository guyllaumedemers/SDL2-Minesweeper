#pragma once
#include <SDL.h>

namespace Toolset {
	class SDLHandler {
	private:
		SDLHandler() = delete;
		SDLHandler(const SDLHandler&) = delete;
		SDLHandler(SDLHandler&&) = delete;
	public:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDLHandler(const int&, const int&);
		~SDLHandler();
		void refresh(void(*)(SDL_Renderer*));
		void draw(void (*)(SDL_Renderer*));
	};
}