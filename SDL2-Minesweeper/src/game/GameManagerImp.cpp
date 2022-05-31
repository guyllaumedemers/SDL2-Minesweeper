#pragma once
#include "../../headers/game/GameManagerImp.h"
#include "../../headers/InputHandler.h"

#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	GameManagerImp::GameManagerImp(const Mode& mode, void(*screen_callback)(const int&, const int&))
	{
#ifdef _DEBUG
		level_context = DBG_NEW LevelHandler(mode);
#else
		level_context = new LevelHandler(mode);
#endif
		int w = level_context->getLevel()->getCols() * Tile::size;
		int h = level_context->getLevel()->getRows() * Tile::size;
		screen_callback(w, h);
	}

	GameManagerImp::~GameManagerImp()
	{
		delete level_context;
		level_context = nullptr;
	}

	void GameManagerImp::processInputs(const int& lrm)
	{
		int mousePosX = 0;
		int mousePosY = 0;
		InputHandler::getMouseState(mousePosX, mousePosY);
		if (mousePosY - Tile::size < 0) return;
		else level_context->update((mousePosY - Tile::size) / Tile::size, mousePosX / Tile::size, lrm);
	}

	void GameManagerImp::refresh(SDL_Renderer* renderer, const int& w, const int& h)
	{
		level_context->refresh(renderer, w, h);
	}

	void GameManagerImp::draw(SDL_Renderer* renderer)
	{
		level_context->draw(renderer);
	}
}