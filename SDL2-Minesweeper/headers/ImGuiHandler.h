#pragma once
#include "SDLHandler.h"
#include <vector>

using namespace std;
namespace Toolset {
	class ImGuiHandler {
	private:
		bool isOpen = false;
		SDLHandler* sdl_context = nullptr;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
		void create();
		void destroy();
	public:
		ImGuiHandler();
		~ImGuiHandler();
		void processInputs(SDL_Event&, void(*)(SDL_Event&));
		void refresh(void (*)(SDL_Renderer*));
		void draw(void (*)(SDL_Renderer*));
	};
}