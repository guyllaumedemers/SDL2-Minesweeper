#pragma once
#include "../../headers/game/Tile.h"

namespace Minesweeper {
	const int Tile::size = 20;

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

	void Tile::refresh(SDL_Renderer* renderer) const
	{
		//TODO Renderer Tile according to his bitmask flags
	}

	const Tilebitmask& Tile::getmask() const
	{
		return bitmask;
	}
}