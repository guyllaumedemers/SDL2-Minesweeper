#pragma once
#include <SDL.h>

namespace Toolset {
	class SDLHandler {
	public:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDLHandler(const SDLHandler&) = delete;
		SDLHandler(SDLHandler&&) = delete;
		SDLHandler() = delete;
		SDLHandler(const int&, const int&);
		~SDLHandler();
		SDLHandler& operator=(const SDLHandler&) = delete;
		SDLHandler& operator=(SDLHandler&&) = delete;
		void refresh(void(*)(SDL_Renderer*));
		void draw(void (*)(SDL_Renderer*));
	};
}