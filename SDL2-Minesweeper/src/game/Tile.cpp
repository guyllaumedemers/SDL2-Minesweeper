#pragma once
#include "../../headers/game/Tile.h"

namespace Minesweeper {
	Tile::Tile() : bitmask(Tilebitmask::None) { }
	Tile::~Tile() {}

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