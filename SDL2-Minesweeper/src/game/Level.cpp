#pragma once
#include "../../headers/game/Level.h"
#include <string>
#include <queue>

#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

using namespace std;
namespace Minesweeper {
	/// <summary>
	/// unsafe
	/// </summary>
	static Tile& optional = Tile();

	Level::Level(const int& rows, const int& cols, const int& bombs, const int& flags)
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

	Level::~Level()
	{
		delete[] map;
		map = nullptr;
	}

	void Level::update(const int& row, const int& col, const int& lrm)
	{
		/// <summary>
		/// Process input for right click
		/// </summary>
		Tile& target = getTile(row * getCols() + col);
		if (lrm) {
			setFlag(target);
			return;
		}
		int invalidTileClicked =
			(int)(target.getmask() & Tilebitmask::Uncovered) +
			(int)(target.getmask() & Tilebitmask::Bomb) +
			(int)(target.getmask() & Tilebitmask::Flag);
		if (invalidTileClicked > 0) discard(target);
		else run(target);
	}

	void Level::refresh(SDL_Renderer* renderer, const int& w, const int& h)
	{
		SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetRenderTarget(renderer, target);
		int rows = getRows();
		int cols = getCols();
		int size = Tile::size;
		for (int i = 0; i < rows * cols; ++i) {
			SDL_Texture* sub_target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, size, size);
			SDL_SetRenderTarget(renderer, sub_target);

			SDL_Rect dest = {
				(i % cols) * size,
				(i / cols) * size,
				size,
				size
			};

			Tile& tile = getTile(i);
			tile.refresh(renderer);

			SDL_SetRenderTarget(renderer, target);
			SDL_RenderCopy(renderer, sub_target, NULL, &dest);
			SDL_DestroyTexture(sub_target);
			sub_target = nullptr;
		}
		SDL_SetRenderTarget(renderer, NULL);
		SDL_RenderCopy(renderer, target, NULL, NULL);
		SDL_DestroyTexture(target);
		target = nullptr;
	}

	void Level::draw(SDL_Renderer* renderer)
	{
		//Do nothing
	}

	int Level::getRows()
	{
		return rows;
	}

	int Level::getCols()
	{
		return cols;
	}

	Tile& Level::getTile(const int& index) const
	{
		if (index < 0 || index >= rows * cols) return optional;
		else return map[index];
	}

	void Level::discard(Tile& target)
	{
		int invalidMove =
			(int)(target.getmask() & Tilebitmask::Flag) +
			(int)(target.getmask() & Tilebitmask::Uncovered);
		if (invalidMove > 0) return;
		/// <summary>
		/// handles clicking on a bomb behaviour
		/// </summary>
		/// <param name="target"></param>
		target.remove(Tilebitmask::Covered);
		target.add(Tilebitmask::Hit);
		/// <summary>
		/// game lost event callback
		/// </summary>
		/// <param name="target"></param>
		showAll();
	}

	void Level::setFlag(Tile& target)
	{
		int invalidMove =
			(int)(target.getmask() & Tilebitmask::Uncovered);
		if (invalidMove) return;

		int hasFlag =
			(int)(target.getmask() & Tilebitmask::Flag);
		if (hasFlag) {
			flags += 1;
			target.remove(Tilebitmask::Flag);
		}
		else {
			if (flags > 0) {
				flags -= 1;
				target.add(Tilebitmask::Flag);
			}
		}
	}

	void Level::showAll()
	{
		for (int i = 0; i < getRows() * getCols(); ++i)
		{
			//TODO Uncover all tiles with proper values
		}
	}

	void Level::run(Tile& target)
	{
		unordered_map<int, Tile*> memoization_map;
		queue<Tile*> pool;

		pool.push(&target);

		while (!pool.empty()) {

			Tile& current = *(pool.front());
			/// <summary>
			/// edge case handling for when a tile is added twice in the queue array
			/// </summary>
			/// <param name="target"></param>
			if (memoization_map.find(current.getIndex()) != memoization_map.end()) {
				pool.pop();
				continue;
			}
			vector<Tile*> neighbors = getNeighbors(memoization_map, current.getIndex());
			{
				/// <summary>
				/// set the current entry value so we can display numbers showing the number of adjacent bombs
				/// </summary>
				/// <param name="target"></param>
				int nbBombs = 0;
				for (const auto& it : neighbors) if ((int)(it->getmask() & Tilebitmask::Bomb)) ++nbBombs;
				current.setValue(nbBombs);
				if (nbBombs != 0) {
					/// <summary>
					/// update tile bitmask value
					/// </summary>
					/// <param name="target"></param>
					if (current.getValue() > 0) current.add(Tilebitmask::Numbered);
					current.remove(Tilebitmask::Covered);
					current.add(Tilebitmask::Uncovered);
					pool.pop();
					continue;
				}
			}
			{
				/// <summary>
				/// verify that the neighbors to process next are of valid type
				/// </summary>
				/// <param name="target"></param>
				for (const auto& it : neighbors) {
					int invalidMove =
						(int)(it->getmask() & Tilebitmask::Bomb) +
						(int)(it->getmask() & Tilebitmask::Flag) +
						(int)(it->getmask() & Tilebitmask::Uncovered);
					if (invalidMove > 0) continue;
					else pool.push(it);
				}
			}
			{
				/// <summary>
				/// add entry that was processed to memoization map to optimize lookup and prevent infinite loop
				/// </summary>
				/// <param name="target"></param>
				memoization_map.insert({ current.getIndex(), &current });
			}
			{
				/// <summary>
				/// update tile bitmask value for empties
				/// </summary>
				/// <param name="target"></param>
				current.remove(Tilebitmask::Covered);
				current.add(Tilebitmask::Uncovered);
			}
			pool.pop();
			neighbors.clear();
		}
		memoization_map.clear();
	}

	vector<Tile*> Level::getNeighbors(unordered_map<int, Tile*>& memoization_map, const int& index)
	{
		vector<Tile*> collection;
		int indices[8] = {
			index + 1,
			index - 1,
			index + cols,
			index - cols,
			index + cols + 1,
			index + cols - 1,
			index - cols + 1,
			index - cols - 1
		};
		for (const auto& it : indices) {
			/// <summary>
			/// edge processing
			/// </summary>
			/// <param name="memoization_map"></param>
			/// <param name="index"></param>
			/// <returns></returns>
			if (it % cols == 0 && index % cols == cols - 1 || it % cols == cols - 1 && index % cols == 0) continue;
			/// <summary>
			/// standard lookup
			/// </summary>
			/// <param name="memoization_map"></param>
			/// <param name="index"></param>
			/// <returns></returns>
			Tile& temp = getTile(it);

			if (temp.getIndex() == -1 || memoization_map.find(temp.getIndex()) != memoization_map.end()) continue;
			else collection.push_back(&temp);
		}
		return collection;
	}
}