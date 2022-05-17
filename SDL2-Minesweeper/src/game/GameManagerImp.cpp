#pragma once
#include "../../headers/game/GameManagerImp.h"
#include "../../headers/InputHandler.h"
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif
#include <iostream>

using namespace Toolset;
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

	void GameManagerImp::processInputs()
	{
		int row = 0;
		int col = 0;
		InputHandler::getMouseState(row, col);
		level_context->update(row, col);
	}

	void GameManagerImp::refresh(SDL_Renderer* renderer)
	{
		level_context->refresh(renderer);
	}

	void GameManagerImp::draw(SDL_Renderer* renderer)
	{
		level_context->draw(renderer);
	}
}