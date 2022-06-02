#pragma once
#include "Tilebitmask.h"

#include <SDL.h>
#include <string>

using namespace std;
namespace Minesweeper {
	struct Tile {
		static const int size;
		static const string textures[5];
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