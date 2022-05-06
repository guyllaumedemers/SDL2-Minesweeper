#pragma once
#include <SDL.h>

namespace Toolset {
	class SDLHandler {
	private:
		SDLHandler() = delete;
		SDLHandler(const SDLHandler&) = delete;
		SDLHandler(SDLHandler&&) = delete;
		void create(int w, int h);
		void destroy();
	public:
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
		SDLHandler(int w, int h);
		~SDLHandler();
		void refresh(void(*)());
		void draw(void (*)());
	};
}