#pragma once
#include <SDL.h>

namespace Minesweeper {
	class SDLHandler {
	private:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDLHandler() = delete;
		SDLHandler(const SDLHandler&) = delete;
		SDLHandler(SDLHandler&&) = delete;
		void create(int w, int h);
		void destroy();
	public:
		SDLHandler(int w, int h);
		~SDLHandler();
		void refresh();
		void draw();
	};
}