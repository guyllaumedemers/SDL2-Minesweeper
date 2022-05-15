#pragma once
#include "../../headers/game/GameManagerImp.h"
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

namespace Minesweeper {
	GameManagerImp::GameManagerImp(const Mode& mode) { create(mode); }
	GameManagerImp::~GameManagerImp() { destroy(); }

	void GameManagerImp::create(const Mode& mode)
	{
#ifdef _DEBUG
		level_context = DBG_NEW LevelHandler(mode);
#else
		level_context = new LevelHandler(mode);
#endif
	}

	void GameManagerImp::destroy()
	{
		delete level_context;
		level_context = nullptr;
	}

	void GameManagerImp::refresh()
	{
	}

	void GameManagerImp::draw()
	{
	}
}