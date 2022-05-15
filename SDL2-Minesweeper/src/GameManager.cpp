#pragma once
#include "../headers/GameManager.h"
#include "../headers/InputHandler.h"
#include <iostream>
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	ImGuiHandler* GameManager::imgui_context = nullptr;
	GameManagerImp* GameManager::imp = nullptr;
	bool GameManager::isRunning = false;

	void GameManager::init()
	{
#ifdef _DEBUG
		CRTMemoryLeak::init();
		imgui_context = DBG_NEW ImGuiHandler(DBG_NEW SDLHandler(640, 480));
		imp = DBG_NEW GameManagerImp(Mode::Easy);
#else		
		imgui_context = new ImGuiHandler(new SDLHandler(640, 480));
		imp = new GameManagerImp(Mode::Easy);
#endif
		isRunning = true;
	}

	void GameManager::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) imgui_context->processInputs(_e, [](SDL_Event& e) { InputHandler::getInput(e); });
			imgui_context->refresh([]() { imp->refresh(); });
			imgui_context->draw([]() { imp->draw(); });
			//TODO Frame Capping
		}
	}

	void GameManager::destroy()
	{
		delete imp;
		imp = nullptr;
		delete imgui_context;
		imgui_context = nullptr;
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