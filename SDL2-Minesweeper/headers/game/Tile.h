
#ifndef INCLUDED_TILE
#define INCLUDED_TILE

#include "Tilebitmask.h"
#include <SDL.h>

namespace Minesweeper {
	class Tile {
		inline static const int tile_size = 20;
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
		void add(const Tilebitmask& value)		{ bitmask |= value; }
		void remove(const Tilebitmask& value)	{ bitmask &= ~value; }
		void refresh(SDL_Renderer*);
		const Tilebitmask& getmask() const	{ return bitmask; }
		const int& getIndex() const			{ return index; }
		const int& getValue() const			{ return value; }
		void setIndex(const int& index) { this->index = index; }
		void setValue(const int& value) { this->value = value; }
		static const int getTileSize()	{ return tile_size; }
	};

	inline Tile::Tile() : bitmask(Tilebitmask::Covered),
		index(-1),
		value(0)
	{}

	inline Tile::~Tile()
	{}
}
#endif