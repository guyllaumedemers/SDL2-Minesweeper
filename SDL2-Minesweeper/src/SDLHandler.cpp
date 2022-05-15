#pragma once
#include "../headers/SDLHandler.h"
#include "../headers/TextureHandler.h"
#include <iostream>

namespace Toolset {
	SDLHandler::SDLHandler(int w, int h) { create(w, h); }
	SDLHandler::~SDLHandler() { destroy(); }

	void SDLHandler::create(int w, int h)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		{
			SDL_Log("SDL_INIT FAILED: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		else if (SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer) != 0)
		{
			SDL_Log("CONTEXT INTIALIZATION FAILED: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		TextureHandler::init();
		TextureHandler::load(renderer);
	}

	void SDLHandler::destroy()
	{
		TextureHandler::destroy();
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_Quit();
	}

	void SDLHandler::refresh(void (*refresh_callback)())
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_assert(refresh_callback);
		refresh_callback();
	}

	void SDLHandler::draw(void (*draw_callback)())
	{
		SDL_assert(draw_callback);
		draw_callback();
		SDL_RenderPresent(renderer);
	}
}
