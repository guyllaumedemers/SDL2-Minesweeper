#pragma once
#include <SDL.h>
#include "Tilebitmask.h"

namespace Minesweeper {
	struct Tile {
	private:
		Tilebitmask bitmask = Tilebitmask::None;
		Tile(const Tile&) = delete;
		Tile(Tile&&) = delete;
	public:
		Tile();
		~Tile();
		void add(Tilebitmask&&);
		void remove(Tilebitmask&&);
		const Tilebitmask& getmask() const;
	};
}