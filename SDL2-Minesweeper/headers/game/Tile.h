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
		int index = -1;
		int value = 0;
		Tile(const Tile&) = delete;
		Tile(Tile&&) = delete;
	public:
		Tile();
		~Tile();
		void add(const Tilebitmask&);
		void remove(const Tilebitmask&);
		void refresh(SDL_Renderer*);
		const Tilebitmask& getmask() const;
		const int& getIndex() const;
		const int& getValue() const;
		void setIndex(const int&);
		void setValue(const int&);
	};
}