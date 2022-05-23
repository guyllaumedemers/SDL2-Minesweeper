#pragma once
#include "ImGuiHandler.h"
#include "EventHandler.h"
#include "game/GameManagerImp.h"

namespace Toolset {
	class GameManager {
	private:
		static ImGuiHandler* imgui_context;
		static GameManagerImp* imp;
		static Subscriber* applicationQuitListener;
		static Subscriber* mouseDownListener;
		static Subscriber* newGameListener;
		static Subscriber* modeChangedListener;
		static Subscriber* helpDocumentListener;
		static bool isRunning;
		static void init();
		static void run();
		static void destroy();
		static void registerEvents();
	public:
		static int execute();
		static void exit();
	};
}