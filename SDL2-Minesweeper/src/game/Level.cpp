#pragma once
#include "../../headers/game/Level.h"
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

namespace Minesweeper {
	Level::Level(const int& rows, const int& cols, const int& bombs, const int& flags) { create(rows, cols, bombs, flags); }
	Level::~Level() { destroy(); }

	void Level::create(const int& rows, const int& cols, const int& bombs, const int& flags)
	{
#ifdef _DEBUG
		map = DBG_NEW Tile[rows * cols];
#else
		map = new Tile[rows * cols];
#endif
		this->rows = rows;
		this->cols = cols;
		this->bombs = bombs;
		this->flags = flags;
	}

	void Level::destroy()
	{
		delete[] map;
		map = nullptr;
	}

	int Level::getRows()
	{
		return rows;
	}

	int Level::getCols()
	{
		return cols;
	}

	const Tile& Level::getTile(const int& index) const
	{
		return map[index];
	}
}