#pragma once
#include "Mode.h"
#include "game/Level.h"
//#ifdef SDL
#include <SDL.h>
//#endif

#ifdef _DEBUG
#include "CRTMemoryLeak.h"
#endif

using namespace Minesweeper;
namespace Toolset {
	/// <summary>
	/// im going to stop this madness of generic cascading effect here and just generate new levels according to the graphic APIs lib currently used
	/// </summary>
	template<class GraphicAPIsRendering>
	class LevelHandler {
	private:
		Level* level = nullptr;
		LevelHandler(const LevelHandler&) = delete;
		LevelHandler(LevelHandler&&) = delete;
		LevelHandler() = delete;
	public:
		LevelHandler(const Mode & = Mode::Easy);
		~LevelHandler();
		void update(const int&, const int&, const int&);
		void refresh(GraphicAPIsRendering*, const int&, const int&);
		void draw(GraphicAPIsRendering*);
		Level* getLevel();
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering>
	LevelHandler<GraphicAPIsRendering>::LevelHandler(const Mode& mode)
	{
#ifdef _DEBUG
		switch (mode)
		{
		case Mode::Easy:
			level = DBG_NEW Level(8, 8, 10, 10);
			break;
		case Mode::Medium:
			level = DBG_NEW Level(16, 16, 40, 40);
			break;
		case Mode::Hard:
			level = DBG_NEW Level(16, 30, 99, 99);
			break;
		default:
			throw "ERROR::LEVEL_CREATION::FAILED";
		}
#else 
		switch (mode)
		{
		case Mode::Easy:
			level = new Level(8, 8, 10, 10);
			break;
		case Mode::Medium:
			level = new Level(16, 16, 40, 40);
			break;
		case Mode::Hard:
			level = new Level(16, 30, 99, 99);
			break;
		default:
			throw "ERROR::LEVEL_CREATION::FAILED";
		}
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering>
	LevelHandler<GraphicAPIsRendering>::~LevelHandler()
	{
		delete level;
		level = nullptr;
	}

	/// <summary>
	/// Update Level logic
	/// </summary>
	template<class GraphicAPIsRendering>
	void LevelHandler<GraphicAPIsRendering>::update(const int& row, const int& col, const int& lrm)
	{
		level->update(row, col, lrm);
	}

	/// <summary>
	/// Refresh renderer context
	/// </summary>
	template<class GraphicAPIsRendering>
	void LevelHandler<GraphicAPIsRendering>::refresh(GraphicAPIsRendering* renderer, const int& w, const int& h)
	{
		level->refresh((SDL_Renderer*)renderer, w, h);
	}


	/// <summary>
	/// Swap Buffers
	/// </summary>
	template<class GraphicAPIsRendering>
	void LevelHandler<GraphicAPIsRendering>::draw(GraphicAPIsRendering* renderer)
	{
		level->draw((SDL_Renderer*)renderer);
	}

	/// <summary>
	/// Level accessor
	/// </summary>
	template<class GraphicAPIsRendering>
	Level* LevelHandler<GraphicAPIsRendering>::getLevel()
	{
		return level;
	}
}