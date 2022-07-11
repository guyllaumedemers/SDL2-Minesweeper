#pragma once
#include "Tile.h"
#include <SDL.h>
#include <vector>
#include <unordered_map>

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
		static Tile& optional;
		Tile* map = nullptr;
		void run(Tile&);
		void discard(Tile&);
		void setFlag(Tile&);
		void showAll();
		vector<Tile*> getNeighbors(unordered_map<int, Tile*>&, const int&);
	public:
		Level(const Level&) = delete;
		Level(Level&&) = delete;
		Level() = delete;
		Level(const int&, const int&, const int&, const int&);
		~Level();
		Level& operator=(const Level&) = delete;
		Level& operator=(Level&&) = delete;
		void update(const int&, const int&, const int&);
		void refresh(SDL_Renderer*, const int&, const int&);
		void draw(SDL_Renderer*);
		int getRows();
		int getCols();
		Tile& getTile(const int&) const;
	};
}