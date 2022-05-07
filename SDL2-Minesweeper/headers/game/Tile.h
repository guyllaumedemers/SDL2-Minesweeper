#pragma once
#include <SDL.h>

namespace Minesweeper {
	struct Tile {
		SDL_Texture* texture = nullptr;
		void refresh();
		void draw();
	};
}