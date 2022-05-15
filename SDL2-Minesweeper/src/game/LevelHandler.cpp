#pragma once
#include "../../headers/game/LevelHandler.h"
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

namespace Minesweeper {
	LevelHandler::LevelHandler(const Mode& mode) { create(mode); }
	LevelHandler::~LevelHandler() { destroy(); }

	void LevelHandler::create(const Mode& mode)
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
			level = DBG_NEW Level(30, 16, 99, 99);
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
			level = new Level(30, 16, 99, 99);
			break;
		default:
			throw "ERROR::LEVEL_CREATION::FAILED";
		}
#endif
	}

	void LevelHandler::destroy()
	{
		delete level;
		level = nullptr;
	}
}