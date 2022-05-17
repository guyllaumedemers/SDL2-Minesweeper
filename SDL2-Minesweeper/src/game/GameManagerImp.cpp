#pragma once
#include "../../headers/game/GameManagerImp.h"
#include "../../headers/InputHandler.h"
#include "../../headers/game/Screen.h"
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

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
		int w = level_context->getLevel()->getCols() * Tile::size;
		int h = level_context->getLevel()->getRows() * Tile::size;
		Screen::setScreenSize(w, h);
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