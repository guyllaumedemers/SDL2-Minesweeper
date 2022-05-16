#pragma once
#include "ImGuiHandler.h"
#include "game/GameManagerImp.h"
#include "EventHandler.h"

using namespace Minesweeper;
namespace Toolset {
	class GameManager {
	private:
		static ImGuiHandler* imgui_context;
		static GameManagerImp* imp;
		static Subscriber* applicationQuitListener;
		static Subscriber* mouseDownListener;
		static bool isRunning;
		static void init();
		static void run();
		static void destroy();
	public:
		static int execute();
		static void exit();
	};
}