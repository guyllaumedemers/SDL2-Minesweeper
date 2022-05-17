#pragma once
#include "SDLHandler.h"
#include "imgui/ImGuiComponent.h"
#include <vector>

using namespace GraphicalToolset;
using namespace std;
namespace Toolset {
	class ImGuiHandler {
	private:
		SDLHandler* sdl_context = nullptr;
		vector<ImGuiComponent*> user_interface;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
		void create(SDLHandler*);
		void destroy();
	public:
		ImGuiHandler(SDLHandler*);
		~ImGuiHandler();
		void processInputs(SDL_Event&, void(*)(SDL_Event&));
		void refresh(void (*)(SDL_Renderer*));
		void draw(void (*)(SDL_Renderer*));
	};
}