#pragma once
#include "bridge/GameManagerImp.h"
#include "ImGuiHandler.h"
#include "EventHandler.h"
#include "Screen.h"
#include "Mode.h"
#include "builder/ImGuiMinesweeperBuilder.h"

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
			/// <summary>
			/// Poll generic Events from inputs
			/// </summary>
			if (imgui_context != nullptr && imp != nullptr && imgui_context->pollEvents([](GraphicAPIsEvent& e) -> void { imp->pollEvents(e); }) > 0) {
				/// <summary>
				/// refresh game logic to renderer on event callbacks
				/// </summary>
				imgui_context->refresh([](GraphicAPIsRendering* renderer) -> void { imp->refresh(renderer, Screen::w, Screen::h); });
				/// <summary>
				/// update renderer context
				/// </summary>
				imgui_context->draw([](GraphicAPIsRendering* renderer) -> void { imp->draw(renderer); });
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
		delete imgui_context;
		imgui_context = nullptr;
		delete imp;
		imp = nullptr;
	}

	/// <summary>
	/// reset game state
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::reset(const Mode& mode)
	{
		/// <summary>
		/// Args mode is being cleared from memory in the subsequent destroy() giving back an invalid value, require local caching
		/// </summary>
		Mode mode_backup = mode;
		destroy();

		static const string event_keys[] = {
			"onApplicationQuit",
			"onMouseDown",
			"onNewGame"
		};

		imp = new GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>(mode_backup, [](const int& w, const int& h) -> void { Screen::setScreenSize(w, h); });
		imgui_context = new ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>(new ImGuiMinesweeperBuilder<SDLHandler>(), Screen::w, Screen::h);

		/// <summary>
		/// Events
		/// </summary>
		EventHandler::create(event_keys[0], new Event<bool>());
		EventHandler::add<bool>(event_keys[0], new Subscriber<bool>([](const bool& val) -> void { isRunning = !val; }));
		EventHandler::create(event_keys[1], new Event<int>());
		EventHandler::add<int>(event_keys[1], new Subscriber<int>([](const int& val) -> void { imp->processInputs(val); }));
		EventHandler::create(event_keys[2], new Event<Mode>());
		EventHandler::add<Mode>(event_keys[2], new Subscriber<Mode>([](const Mode& val) -> void { reset(val); }));
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