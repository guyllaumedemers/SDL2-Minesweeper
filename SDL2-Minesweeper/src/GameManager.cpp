#pragma once
#include "../headers/GameManager.h"
#include "../headers/EventManager.h"
#include "../headers/InputHandler.h"
#include "../headers/game/Screen.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	/// <summary>
	/// static fields
	/// </summary>
	ImGuiHandler* GameManager::imgui_context = nullptr;
	GameManagerImp* GameManager::imp = nullptr;
	bool GameManager::isRunning = false;

	/// <summary>
	/// static subscribers
	/// </summary>
	Subscriber* GameManager::applicationQuitListener = nullptr;
	Subscriber* GameManager::mouseDownListener = nullptr;
	Subscriber* GameManager::newGameListener = nullptr;
	Subscriber* GameManager::modeChangedListener = nullptr;
	Subscriber* GameManager::helpDocumentListener = nullptr;

	void GameManager::init()
	{
		EventManager::create();
#ifdef _DEBUG
		CRTMemoryLeak::init();
		imp = DBG_NEW GameManagerImp(Mode::Hard, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = DBG_NEW ImGuiHandler(Screen::w, Screen::h);
#else		
		imp = new GameManagerImp(Mode::Hard, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = new ImGuiHandler(Screen::w, Screen::h);
#endif
		registerEvents();
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
		EventManager::destroy();
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

	void GameManager::registerEvents()
	{
#ifdef _DEBUG
		applicationQuitListener = DBG_NEW Subscriber(EventManager::get("onApplicationQuitEvent"), []() { exit(); });
		mouseDownListener = DBG_NEW Subscriber(EventManager::get("onMouseDownEvent"), []() { imp->processInputs(); });
		newGameListener = DBG_NEW Subscriber(EventManager::get("onNewGameSelectedEvent"), []() { /*DoSomething()*/});
		modeChangedListener = DBG_NEW Subscriber(EventManager::get("onModeSelectionChangedEvent"), []() { /*DoSomething()*/});
		helpDocumentListener = DBG_NEW Subscriber(EventManager::get("onHelpDocumentSelectedEvent"), []() { /*DoSomething()*/});
#else		
		applicationQuitListener = new Subscriber(EventManager::get("onApplicationQuitEvent"), []() { exit(); });
		mouseDownListener = new Subscriber(EventManager::get("onMouseDownEvent"), []() { imp->processInputs(); });
		newGameListener = new Subscriber(EventManager::get("onNewGameSelectedEvent"), []() { /*DoSomething()*/});
		modeChangedListener = new Subscriber(EventManager::get("onModeSelectionChangedEvent"), []() { /*DoSomething()*/});
		helpDocumentListener = new Subscriber(EventManager::get("onHelpDocumentSelectedEvent"), []() { /*DoSomething()*/});
#endif
	}
}