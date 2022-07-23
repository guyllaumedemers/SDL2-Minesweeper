
#ifndef INCLUDED_SDLHANDLER
#define INCLUDED_SDLHANDLER

#include <SDL.h>

namespace Toolset {
	class SDLHandler {
		SDL_Window* window = nullptr;
		SDL_Renderer* renderer = nullptr;
	public:
		SDLHandler(const SDLHandler&) = delete;
		SDLHandler(SDLHandler&&) = delete;
		SDLHandler() = delete;
		SDLHandler(const int&, const int&);
		~SDLHandler();
		SDLHandler& operator=(const SDLHandler&) = delete;
		SDLHandler& operator=(SDLHandler&&) = delete;
		SDL_Window* getWindow() const		{ return window; }
		SDL_Renderer* getRenderer() const { return renderer; }
		void refresh(void(*)(SDL_Renderer*));
		void draw(void (*)(SDL_Renderer*));
	};
}
#endif