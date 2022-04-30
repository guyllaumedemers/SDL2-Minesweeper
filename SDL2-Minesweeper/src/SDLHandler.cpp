#pragma once
#include "../headers/SDLHandler.h"

namespace Minesweeper {
	SDLHandler::SDLHandler(int w, int h) { create(w, h); }
	SDLHandler::~SDLHandler() { destroy(); }

	void SDLHandler::create(int w, int h)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("SDL_INIT FAILED: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		else if (SDL_CreateWindowAndRenderer(w, h, -1, window, renderer) < 0) {
			SDL_Log("CONTEXT INTIALIZATION FAILED: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
	}

	void SDLHandler::destroy()
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_Quit();
	}

	void SDLHandler::refresh()
	{
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	}

	void SDLHandler::draw()
	{
		SDL_RenderPresent(renderer);
	}
}
