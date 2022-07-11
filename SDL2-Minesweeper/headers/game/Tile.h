#pragma once
#include "Tilebitmask.h"
#include <SDL.h>

using namespace std;
namespace Minesweeper {
	struct Tile {
		static const int size;
	private:
		Tilebitmask bitmask = Tilebitmask::None;
		int index = -1;
		int value = 0;
	public:
		Tile(const Tile&) = delete;
		Tile(Tile&&) = delete;
		Tile();
		~Tile();
		Tile& operator=(const Tile&) = delete;
		Tile& operator=(Tile&&) = delete;
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