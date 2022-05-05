#include "../headers/SDLHandler.h"
#include <iostream>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

namespace Minesweeper {
	SDLHandler::SDLHandler(int w, int h) { create(w, h); }
	SDLHandler::~SDLHandler() { destroy(); }

	void SDLHandler::create(int w, int h)
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
			SDL_Log("SDL_INIT FAILED: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}
		else if (SDL_CreateWindowAndRenderer(w, h, 0, &window, &renderer) != 0) {
			SDL_Log("CONTEXT INTIALIZATION FAILED: %s", SDL_GetError());
			exit(EXIT_FAILURE);
		}

		//SDL_RendererInfo info;
		//SDL_GetRendererInfo(renderer, &info);
		//SDL_Log("Current SDL_Renderer: %s", info.name);

		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// Setup Platform/Renderer backends
		ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
		ImGui_ImplSDLRenderer_Init(renderer);
	}

	void SDLHandler::destroy()
	{
		// Cleanup
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();

		SDL_DestroyWindow(window);
		window = nullptr;
		SDL_DestroyRenderer(renderer);
		renderer = nullptr;
		SDL_Quit();
	}

	void SDLHandler::refresh()
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		{
			static float f = 0.0f;
			static int counter = 0;

			ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

			ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)

			ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f

			if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
				counter++;
			ImGui::SameLine();
			ImGui::Text("counter = %d", counter);

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
			ImGui::End();
		}
		ImGui::Render();
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
	}

	void SDLHandler::draw()
	{
		SDL_RenderPresent(renderer);
	}
}
