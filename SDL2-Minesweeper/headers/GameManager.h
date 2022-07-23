/*
*	Currently reading this bad boy, https://www.amazon.ca/Large-Scale-Software-Design-John-Lakos/dp/0201633620 and thinking
 *	about ways to optimize physical design to reduce compile time coupling so C++ preprocessor aren't referred in multiple times
 *	as well as generating a more concise Translation unit to reduce linking time.
 *
 */

#ifndef INCLUDED_GAMEMANAGER
#define INCLUDED_GAMEMANAGER

#include "ImGuiHandler.h"
#include "bridge/GameManagerImp.h"
#include "Mode.h"						//Mode Enum is tricky to handle as the Builder pattern reference it, ideally Enum would be encapsulated inside GameManager -> to think about
#include "Screen.h"
#include "builder/ImGuiMinesweeperBuilder.h"
#include "builder/LevelMinesweeperBuilder.h"
#include "SDLHandler.h"
#include "EventHandler.h"
#include <string>

using namespace Toolset;
namespace Minesweeper {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class GameManager {
		static inline ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>* imgui_context = nullptr;
		static inline GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>* game_context = nullptr;
		static inline bool isRunning = false;
		static void init();
		static void run();
		static void destroy();
		static void reset(const Mode&);
	public:
		GameManager(const GameManager&) = delete;
		GameManager(GameManager&&) = delete;
		GameManager() = delete;
		~GameManager() = delete;
		GameManager& operator=(const GameManager&) = delete;
		GameManager& operator=(GameManager&&) = delete;
		static int execute();
	};

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::init()
	{
		reset(Mode::Hard);
		isRunning = true;
	}

	/// <summary>
	/// run [&](){} https://docs.microsoft.com/en-us/cpp/cpp/lambda-expressions-in-cpp?view=msvc-170, Capture Clause
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::run()
	{
		/// <summary>
		///	Here, we don't set the capture clause to take body variable by Reference but rather by copy. A thing to point out is that the variable in
		///	questions are static, meaning global hereby opposing the "default" behaviour of the Capture clause of the lamda expression
		/// </summary>
		while (isRunning) {
			if (imgui_context != nullptr && game_context != nullptr && imgui_context->pollEvents([](GraphicAPIsEvent& e) -> void { game_context->pollEvents(e); }) > 0)
				{
					imgui_context->refresh([](GraphicAPIsRendering* renderer) -> void { game_context->refresh(renderer, Screen::w, Screen::h); });
					imgui_context->draw([](GraphicAPIsRendering* renderer) -> void { game_context->draw(renderer); });
				}
		}
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::destroy()
	{
		EventHandler::flush();
		delete imgui_context;
		imgui_context = nullptr;
		delete game_context;
		game_context = nullptr;
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::reset(const Mode& mode)
	{
		Mode temp = mode;
		destroy();

		static const std::string event_keys[] = {
			"onApplicationQuit",
			"onMouseDown",
			"onNewGame"
		};

		game_context = new GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>(new Minesweeper::LevelMinesweeperBuilder<GraphicAPIsRendering>(temp), [](const int& w, const int& h) -> void { Screen::setScreenSize(w, h); });
		imgui_context = new ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>(new Minesweeper::ImGuiMinesweeperBuilder<SDLHandler>(), Screen::w, Screen::h);

		EventHandler::create(event_keys[0], new Event<bool>());
		EventHandler::add<bool>(event_keys[0], new Subscriber<bool>([](const bool& val) -> void { isRunning = !val; }));
		EventHandler::create(event_keys[1], new Event<int>());
		EventHandler::add<int>(event_keys[1], new Subscriber<int>([](const int& val) -> void { game_context->processInputs(val); }));
		EventHandler::create(event_keys[2], new Event<Mode>());
		EventHandler::add<Mode>(event_keys[2], new Subscriber<Mode>([](const Mode& val) -> void { reset(val); }));
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline int GameManager<GraphicAPIsRendering, GraphicAPIsEvent>::execute()
	{
		init();
		run();
		destroy();
		return EXIT_SUCCESS;
	}
}
#endif