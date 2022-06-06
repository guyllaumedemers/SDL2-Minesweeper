#pragma once
#include "bridge/GameManagerImp.h"
#include "ImGuiHandler.h"
#include "EventHandler.h"
#include "Screen.h"
#include "Mode.h"
#include "builder/ImGuiMinesweeperBuilder.h"

#ifdef _DEBUG
#include "CRTMemoryLeak.h"
#endif

using namespace Minesweeper;
namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class GameManager {
	private:
		static ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>* imgui_context;
		static GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>* imp;
		static bool isRunning;
		static void init();
		static void run();
		static void destroy();
		static void reset(const Mode&);
	public:
		static int execute();
	};

	/// <summary>
	/// static fields
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>* GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::imgui_context = nullptr;

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>* GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::imp = nullptr;

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	bool GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::isRunning = false;

	/// <summary>
	/// init
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::init()
	{
		reset(Mode::Hard);
		isRunning = true;
	}

	/// <summary>
	/// run
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::run()
	{
		while (isRunning) {
			SDL_Event _e;
			if (SDL_WaitEvent(&_e)) {
				imgui_context->pollEvents(_e, [](GraphicAPIsEvent& e) { imp->pollEvents(e); });
				imgui_context->refresh([](GraphicAPIsRendering* renderer) { imp->refresh(renderer, Screen::w, Screen::h); }, Screen::w, Screen::h);
				imgui_context->draw([](GraphicAPIsRendering* renderer) { imp->draw(renderer); });
			}
		}
	}

	/// <summary>
	/// destroy
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::destroy()
	{
		EventHandler::flush();
		delete imp;
		imp = nullptr;
		delete imgui_context;
		imgui_context = nullptr;
	}

	/// <summary>
	/// reset game state
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::reset(const Mode& mode)
	{
		destroy();

		static const string event_keys[] = {
			"onApplicationQuit",
			"onMouseDown",
			"onNewGame"
		};

#ifdef _DEBUG
		CRTMemoryLeak::init();
		imp = DBG_NEW GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>(mode, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = DBG_NEW ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>(DBG_NEW ImGuiMinesweeperBuilder<SDLHandler>(), Screen::w, Screen::h);
		EventHandler::create(event_keys[0], DBG_NEW Event<bool>());
		EventHandler::add<bool>(event_keys[0], DBG_NEW Subscriber<bool>([](const bool& val) { isRunning = !val; }));
		EventHandler::create(event_keys[1], DBG_NEW Event<int>());
		EventHandler::add<int>(event_keys[1], DBG_NEW Subscriber<int>([](const int& val) { imp->processInputs(val); }));
		EventHandler::create(event_keys[2], DBG_NEW Event<Mode>());
		EventHandler::add<Mode>(event_keys[2], DBG_NEW Subscriber<Mode>([](const Mode& val) { reset(val); }));
#else		
		imp = new GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>(mode, [](const int& w, const int& h) { Screen::setScreenSize(w, h); });
		imgui_context = new ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>(new ImGuiMinesweeperBuilder<SDLHandler>(), Screen::w, Screen::h);
		EventHandler::create(event_keys[0], new Event<bool>());
		EventHandler::add<bool>(event_keys[0], new Subscriber<bool>([](const bool& val) { isRunning = !val; }));
		EventHandler::create(event_keys[1], new Event<int>());
		EventHandler::add<int>(event_keys[1], new Subscriber<int>([](const int& val) { imp->processInputs(val); }));
		EventHandler::create(event_keys[2], new Event<Mode>());
		EventHandler::add<Mode>(event_keys[2], new Subscriber<Mode>([](const Mode& val) { reset(val); }));
#endif
	}

	/// <summary>
	/// execute
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	int GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::execute()
	{
		init();
		run();
		destroy();
		return EXIT_SUCCESS;
	}
}