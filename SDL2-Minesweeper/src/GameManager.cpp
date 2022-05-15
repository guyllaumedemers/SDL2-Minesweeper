#pragma once
#include "../headers/GameManager.h"
#include "../headers/InputHandler.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif
#include <iostream>

namespace Minesweeper {
	ImGuiHandler* GameManager::context = nullptr;
	bool GameManager::isRunning = false;

	void GameManager::init()
	{
#ifdef _DEBUG
		CRTMemoryLeak::init();
		context = DBG_NEW ImGuiHandler(DBG_NEW SDLHandler(640, 480));
#else		
		context = new ImGuiHandler(new SDLHandler(640, 480));
#endif
		isRunning = true;
	}

	void GameManager::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) context->processInputs(_e, [](SDL_Event& e) {InputHandler::getInput(e); });
			context->refresh([]() {});
			context->draw([]() {});
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