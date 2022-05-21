#pragma once
#include "../../headers/game/LevelHandler.h"
#include <SDL.h>
#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif
#include <iostream>

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
		Tile& target = level->getTile(row * level->getCols() + col);

	}

	void LevelHandler::refresh(SDL_Renderer* renderer, const int& w, const int& h)
	{
		SDL_Texture* target = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		SDL_SetRenderTarget(renderer, target);
		int rows = level->getRows();
		int cols = level->getCols();
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

			Tile& tile = level->getTile(i);
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

	void LevelHandler::draw(SDL_Renderer* renderer)
	{
		//TODO Draw doodles
	}

	Level* LevelHandler::getLevel()
	{
		return level;
	}
}