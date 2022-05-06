#pragma once
#include "ImGuiHandler.h"

using namespace Toolset;
namespace Minesweeper {
	class GameManager {
	private:
		static ImGuiHandler* context;
		static bool isRunning;
		static void init();
		static void run();
		static void destroy();
	public:
		static int execute();
		static void exit();
	};
}