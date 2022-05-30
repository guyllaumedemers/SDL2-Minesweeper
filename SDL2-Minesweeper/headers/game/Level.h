#pragma once
#include "Tile.h"

#include <unordered_map>
#include <vector>
#include <SDL.h>

/// <summary>
/// Using array sequence of tiles to improve efficiency by accessing sequential memory blocks
/// </summary>
using namespace std;
namespace Minesweeper {
	/// <summary>
	/// Specific to the game type in dev, not reusable
	/// </summary>
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
		void run(Tile&);
		void discard(Tile&);
		void showAll();
		vector<Tile*> getNeighbors(unordered_map<int, Tile*>&, const int&);
	public:
		Level(const int&, const int&, const int&, const int&);
		~Level();
		void update(const int&, const int&, const int&);
		void refresh(SDL_Renderer*, const int&, const int&);
		void draw(SDL_Renderer*);
		int getRows();
		int getCols();
		Tile& getTile(const int&) const;
	};
}