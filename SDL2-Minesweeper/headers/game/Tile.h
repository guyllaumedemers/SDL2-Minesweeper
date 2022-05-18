#pragma once
#include <SDL.h>
#include <string>
#include "Tilebitmask.h"

using namespace std;
namespace Minesweeper {
	struct Tile {
		const static int size;
		const static string textures[];
	private:
		Tilebitmask bitmask = Tilebitmask::None;
		int value = 0;
		Tile(const Tile&) = delete;
		Tile(Tile&&) = delete;
		int getValue();
	public:
		Tile();
		~Tile();
		void add(const Tilebitmask&);
		void remove(const Tilebitmask&);
		void refresh(SDL_Renderer*);
		const Tilebitmask& getmask() const;
		void setValue(const int&);
	};
}