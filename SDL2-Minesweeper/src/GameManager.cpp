#pragma once
#include "../headers/GameManager.h"
#include "../headers/InputHandler.h"
#include "../headers/game/Screen.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif
#include <iostream>

namespace Toolset {
	ImGuiHandler* GameManager::imgui_context = nullptr;
	GameManagerImp* GameManager::imp = nullptr;
	Subscriber* GameManager::applicationQuitListener = nullptr;
	Subscriber* GameManager::mouseDownListener = nullptr;
	bool GameManager::isRunning = false;

	void GameManager::init()
	{
#ifdef _DEBUG
		CRTMemoryLeak::init();
		imp = DBG_NEW GameManagerImp(Mode::Hard);
		imgui_context = DBG_NEW ImGuiHandler();
		applicationQuitListener = DBG_NEW Subscriber(InputHandler::onApplicationQuitEvent, []() { exit(); });
		mouseDownListener = DBG_NEW Subscriber(InputHandler::onMouseDownEvent, []() { imp->processInputs(); });
#else		
		imp = new GameManagerImp(Mode::Hard);
		imgui_context = new ImGuiHandler();
		applicationQuitListener = new Subscriber(InputHandler::onApplicationQuitEvent, []() { exit(); });
		mouseDownListener = new Subscriber(InputHandler::onMouseDownEvent, []() {});
#endif
		isRunning = true;
	}

	void GameManager::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) imgui_context->processInputs(_e, [](SDL_Event& e) { InputHandler::getInput(e); });
			imgui_context->refresh([](SDL_Renderer* renderer) { imp->refresh(renderer); });
			imgui_context->draw([](SDL_Renderer* renderer) { imp->draw(renderer); });
			//TODO Frame Capping
		}
	}

	void GameManager::destroy()
	{
		InputHandler::destroy();
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