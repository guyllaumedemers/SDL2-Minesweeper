#pragma once
#include "../../headers/game/LevelHandler.h"
#include <SDL.h>
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
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

	void LevelHandler::destroy()
	{
		delete level;
		level = nullptr;
	}

	void LevelHandler::update(const int& row, const int& col)
	{
		level->update(row, col);
	}

	void LevelHandler::refresh(SDL_Renderer* renderer, const int& w, const int& h)
	{
		level->refresh(renderer, w, h);
	}

	void LevelHandler::draw(SDL_Renderer* renderer)
	{
		level->draw(renderer);
	}

	Level* LevelHandler::getLevel()
	{
		return level;
	}
}