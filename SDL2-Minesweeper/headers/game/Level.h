#pragma once
#include "Tile.h"

namespace Minesweeper {
	struct Level {
	private:
		int rows = 0;
		int cols = 0;
		int flags = 0;
		int bombs = 0;
		Tile* map = nullptr;
		Level() = delete;
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		void create(const int&, const int&, const int&, const int&);
		void destroy();
	public:
		Level(const int&, const int&, const int&, const int&);
		~Level();
		int getRows();
		int getCols();
		int getIndex();
	};
}