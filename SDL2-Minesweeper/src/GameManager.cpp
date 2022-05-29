#pragma once
#include "../headers/GameManager.h"
#include "../headers/game/Screen.h"
#include "../headers/EventHandler.h"
#include "../headers/InputHandler.h"

#include <string>
#include <iostream>

#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	/// <summary>
	/// static fields
	/// </summary>
	ImGuiHandler<SDL_Renderer, SDL_Event>* GameManager::imgui_context = nullptr;
	GameManagerImp* GameManager::imp = nullptr;
	bool GameManager::isRunning = false;

	static const string event_keys[] = {
		"onApplicationQuit"
	};

	void GameManager::init()
	{
#ifdef _DEBUG
		CRTMemoryLeak::init();
		imp = DBG_NEW GameManagerImp(Mode::Hard, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = DBG_NEW ImGuiHandler<SDL_Renderer, SDL_Event>(Screen::w, Screen::h);
		EventHandler::create(event_keys[0], DBG_NEW Event<bool>());
		EventHandler::add<bool>(event_keys[0], DBG_NEW Subscriber<bool>([](const bool& val) { isRunning = !val; }));
#else		
		imp = new GameManagerImp(Mode::Hard, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = new ImGuiHandler<SDL_Renderer, SDL_Event>(Screen::w, Screen::h);
		EventHandler::create(event_keys[0], new Event<bool>());
		EventHandler::add<bool>(event_keys[0], DBG_NEW Subscriber<bool>([](const bool& val) { isRunning = !val; }));
#endif
		isRunning = true;
	}

	void GameManager::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) {
				imgui_context->processInputs(_e, [](SDL_Event& e) { InputHandler::getInput(e); });
				imgui_context->refresh([](SDL_Renderer* renderer) { imp->refresh(renderer, Screen::w, Screen::h); }, Screen::w, Screen::h);
				imgui_context->draw([](SDL_Renderer* renderer) { imp->draw(renderer); });
			}
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