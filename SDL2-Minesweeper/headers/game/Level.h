
#ifndef INCLUDED_LEVEL
#define INCLUDED_LEVEL

#include "Tile.h"
#include <vector>
#include <unordered_map>
#include <optional>
#include <cstdlib>

namespace Minesweeper {
	class Level {
		int rows = 0, cols = 0, flags = 0, bombs = 0;
		inline static std::optional<Tile> optional = std::make_optional<Tile>();
		Tile* map = nullptr;
		std::vector<Tile*> getNeighbors(std::unordered_map<int, Tile*>&, const int&);
		void run(Tile&);
		void discard(Tile&);
		void setFlag(Tile&);
		void showAll();
	public:
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		Level() = delete;
		Level(const int&, const int&, const int&, const int&);
		~Level();
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;
		int getRows() const { return rows; }
		int getCols() const { return cols; }
		Tile& getTile(const int&) const;
		void update(const int&, const int&, const int&);
		void refresh(SDL_Renderer*, const int&, const int&);
		void draw(SDL_Renderer*);
	};
	
	inline Level::Level(const int& rows, const int& cols, const int& bombs, const int& flags)
	{
		map = new Tile[rows * cols];

		this->rows = rows;
		this->cols = cols;
		this->bombs = bombs;
		this->flags = flags;

		for (int i = 0; i < rows * cols; ++i) map[i].setIndex(i);
		int nbBombs = bombs;
		while (nbBombs > 0) {
			int index = rand() % (rows * cols);

			while ((int)(map[index].getmask() & Tilebitmask::Bomb)) {
				index = rand() % (rows * cols);
			}

			map[index].add(Tilebitmask::Bomb);
			--nbBombs;
		}
	}

	inline Level::~Level()
	{
		delete[] map;
		map = nullptr;
	}

	inline Tile& Level::getTile(const int& index) const
	{
		if (index < 0 || index >= rows * cols) return *optional;
		return map[index];
	}
}
#endif