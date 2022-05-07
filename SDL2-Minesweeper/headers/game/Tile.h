#pragma once
#include <SDL.h>
#include "Tilebitmask.h"

namespace Minesweeper {
	struct Tile {
	private:
		Tilebitmask bitmask = Tilebitmask::None;
		SDL_Texture* texture = nullptr;
		int index = 0;
		Tile() = delete;
		Tile(const Tile&) = delete;
		Tile(Tile&&) = delete;
	public:
		Tile(SDL_Texture*, const int&);
		~Tile();
		void add(Tilebitmask&&);			//Testing, is the RValue going to hold in the bitmask? or is it going to be discarted once out of scope
		void remove(Tilebitmask&&);
		const Tilebitmask& getmask() const;
	};
}