#pragma once
#include <SDL.h>
#include "Tilebitmask.h"

namespace Minesweeper {
	struct Tile {
		const static int size;
	private:
		Tilebitmask bitmask = Tilebitmask::None;
		Tile(const Tile&) = delete;
		Tile(Tile&&) = delete;
	public:
		Tile();
		~Tile();
		void add(Tilebitmask&&);
		void remove(Tilebitmask&&);
		void draw(SDL_Renderer*) const;
		const Tilebitmask& getmask() const;
	};
}