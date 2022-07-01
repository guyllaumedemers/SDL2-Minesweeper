#pragma once
#include "../headers/SDLHandler.h"
#include "../headers/TextureHandler.h"
#include <SDL_image.h>
#include <iostream>
#include <string>

namespace Toolset {
	SDLHandler::SDLHandler(const int& w, const int& h)
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

		static const string window_name =
			"Minesweeper";

		SDL_SetWindowTitle(window, window_name.c_str());
		TextureHandler<SDL_Renderer, SDL_Texture>::init();
		TextureHandler<SDL_Renderer, SDL_Texture>::load(renderer, [](SDL_Renderer* ren, string s) -> SDL_Texture* { return IMG_LoadTexture(ren, s.c_str()); });
	}

	SDLHandler::~SDLHandler()
	{
		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_Quit();
		TextureHandler<SDL_Renderer, SDL_Texture>::destroy();
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
