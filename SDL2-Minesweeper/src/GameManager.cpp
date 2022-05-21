#pragma once
#include "../headers/GameManager.h"
#include "../headers/game/Screen.h"
#include "../headers/InputHandler.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

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
		imp = DBG_NEW GameManagerImp(Mode::Hard, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = DBG_NEW ImGuiHandler(Screen::w, Screen::h);
		applicationQuitListener = DBG_NEW Subscriber(InputHandler::onApplicationQuitEvent, []() { exit(); });
		mouseDownListener = DBG_NEW Subscriber(InputHandler::onMouseDownEvent, []() { imp->processInputs(); });
#else		
		imp = new GameManagerImp(Mode::Hard, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = new ImGuiHandler(Screen::w, Screen::h);
		applicationQuitListener = new Subscriber(InputHandler::onApplicationQuitEvent, []() { exit(); });
		mouseDownListener = new Subscriber(InputHandler::onMouseDownEvent, []() { imp->processInputs(); });
#endif
		isRunning = true;
	}

	void GameManager::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) imgui_context->processInputs(_e, [](SDL_Event& e) { InputHandler::getInput(e); });
			imgui_context->refresh([](SDL_Renderer* renderer) { imp->refresh(renderer, Screen::w, Screen::h); }, Screen::w, Screen::h);
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