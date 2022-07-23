
#ifndef INCLUDED_LEVELMINESWEEPERBUILDER
#define INCLUDED_LEVELMINESWEEPERBUILDER

#include "LevelBuilder.h"
#include "../game/Level.h"
#include "../Mode.h"

namespace Minesweeper {
	template<class GraphicAPIsRendering>
	class LevelMinesweeperBuilder final : public virtual Toolset::LevelBuilder<GraphicAPIsRendering> {
		Level* level = nullptr;
	public:
		LevelMinesweeperBuilder(const LevelMinesweeperBuilder&) = delete;
		LevelMinesweeperBuilder(LevelMinesweeperBuilder&&) = delete;
		LevelMinesweeperBuilder() = delete;
		explicit LevelMinesweeperBuilder(const Toolset::Mode&);
		~LevelMinesweeperBuilder() override;
		LevelMinesweeperBuilder& operator=(const LevelMinesweeperBuilder&) = delete;
		LevelMinesweeperBuilder& operator=(LevelMinesweeperBuilder&&) = delete;
		const Level* getLevel() const { return level; }
		void update(const int&, const int&, const int&) override;
		void refresh(GraphicAPIsRendering*, const int&, const int&) override;
		void draw(GraphicAPIsRendering*) override;
	};

	template <class GraphicAPIsRendering>
	inline LevelMinesweeperBuilder<GraphicAPIsRendering>::LevelMinesweeperBuilder(const Toolset::Mode& mode)
	{
		switch (mode)
		{
		case Toolset::Mode::Easy:
			level = new Level(8, 8, 10, 10);
			break;
		case Toolset::Mode::Medium:
			level = new Level(16, 16, 40, 40);
			break;
		case Toolset::Mode::Hard:
			level = new Level(16, 30, 99, 99);
			break;
		default:
			exit(EXIT_FAILURE);
		}
		this->setLevelWidth(level->getCols() * Tile::getTileSize());
		this->setLevelHeight(level->getRows() * Tile::getTileSize());
	}

	template <class GraphicAPIsRendering>
	inline LevelMinesweeperBuilder<GraphicAPIsRendering>::~LevelMinesweeperBuilder()
	{
		delete level;
		level = nullptr;
	}

	template <class GraphicAPIsRendering>
	inline void LevelMinesweeperBuilder<GraphicAPIsRendering>::update(const int& mpx, const int& mpy, const int& lrm)
	{
		level->update(mpx, mpy, lrm);
	}

	template <class GraphicAPIsRendering>
	inline void LevelMinesweeperBuilder<GraphicAPIsRendering>::refresh(GraphicAPIsRendering* renderer, const int& w, const int& h)
	{
		level->refresh(renderer, w, h);
	}

	template <class GraphicAPIsRendering>
	inline void LevelMinesweeperBuilder<GraphicAPIsRendering>::draw(GraphicAPIsRendering* renderer)
	{
		level->draw(renderer);
	}
}
#endif