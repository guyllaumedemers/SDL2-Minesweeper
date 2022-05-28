#pragma once
#include "ImGuiHandler.h"
#include "game/GameManagerImp.h"

#include <SDL.h>

namespace Toolset {
	class GameManager {
	private:
		static ImGuiHandler<SDL_Renderer, SDL_Event>* imgui_context;
		static GameManagerImp* imp;
		static bool isRunning;
		static void init();
		static void run();
		static void destroy();
	public:
		static int execute();
		static void exit();
	};
}