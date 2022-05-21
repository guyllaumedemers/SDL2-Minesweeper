#pragma once
#include "SDLHandler.h"
#include "EventHandler.h"
#include <vector>

using namespace std;
namespace Toolset {
	class ImGuiHandler {
	private:
		SDLHandler* sdl_context = nullptr;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
		void create(const int&, const int&);
		void destroy();
	public:
		ImGuiHandler(const int&, const int&);
		~ImGuiHandler();
		void processInputs(SDL_Event&, void(*)(SDL_Event&));
		void refresh(void (*)(SDL_Renderer*), const int&, const int&);
		void draw(void (*)(SDL_Renderer*));
	};
}