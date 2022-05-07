#pragma once
#include "../../headers/game/Tile.h"

namespace Minesweeper {
	Tile::Tile(SDL_Texture* texture, const int& arr_pos) : texture(texture), index(arr_pos), bitmask(Tilebitmask::None) { }
	Tile::~Tile() { texture = nullptr; }

	void Tile::add(Tilebitmask&& value)
	{
		bitmask |= value;
	}

	void Tile::remove(Tilebitmask&& value)
	{
		bitmask &= ~value;
	}

	const Tilebitmask& Tile::getmask() const
	{
		return bitmask;
	}
}