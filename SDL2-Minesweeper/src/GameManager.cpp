#pragma once
#include "../headers/GameManager.h"
#include "../headers/InputHandler.h"
#include <iostream>

namespace Minesweeper {
	SDLHandler* GameManager::context = nullptr;
	bool GameManager::isRunning = false;

	void GameManager::init()
	{
		context = new SDLHandler(640, 480);
		isRunning = true;
	}

	void GameManager::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) InputHandler::getInput(_e);
			context->refresh();
			//set logic
			context->draw();
		}
	}

	void GameManager::destroy()
	{
		delete context;
		context = nullptr;
	}

	int GameManager::execute()
	{
		init();
		run();
		destroy();
		return EXIT_SUCCESS;
	}

	void GameManager::exit()
	{
		isRunning = false;
	}
}