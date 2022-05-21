#pragma once
#include "../headers/SDLHandler.h"
#include "../headers/TextureHandler.h"
#include <iostream>

namespace Toolset {
	SDLHandler::SDLHandler(const int& w, const int& h) { create(w, h); }
	SDLHandler::~SDLHandler() { destroy(); }

	void SDLHandler::create(const int& w, const int& h)
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
		SDL_SetWindowTitle(window, "Minesweeper");
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

	void SDLHandler::refresh(void (*refresh_callback)(SDL_Renderer*))
	{
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		SDL_assert(refresh_callback);
		refresh_callback(renderer);
	}

	void SDLHandler::draw(void (*draw_callback)(SDL_Renderer*))
	{
		SDL_assert(draw_callback);
		draw_callback(renderer);
		SDL_RenderPresent(renderer);
	}
}
