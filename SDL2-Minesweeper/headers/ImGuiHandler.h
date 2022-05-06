#pragma once
#include "SDLHandler.h"

namespace Toolset {
	class ImGuiHandler {
	private:
		SDLHandler* context = nullptr;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
		void create(SDLHandler*);
		void destroy();
	public:
		ImGuiHandler(SDLHandler*);
		~ImGuiHandler();
		void processInputs(SDL_Event&, void(*)(SDL_Event&));
		void refresh(void (*)());
		void draw(void (*)());
	};
}