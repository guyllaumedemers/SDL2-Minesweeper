#pragma once
#include "../headers/ImGuiHandler.h"
#include "../headers/game/Screen.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	ImGuiHandler::ImGuiHandler() : sdl_context(nullptr), isOpen(true) { create(); }
	ImGuiHandler::~ImGuiHandler() { destroy(); }

	void ImGuiHandler::create()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
#ifdef _DEBUG
		sdl_context = DBG_NEW SDLHandler(Screen::w, Screen::h + ImGui::GetFrameHeightWithSpacing());
#else
		sdl_context = new SDLHandler(Screen::w, Screen::h + ImGui::GetFrameHeightWithSpacing());
#endif
		ImGui_ImplSDL2_InitForSDLRenderer(sdl_context->window, sdl_context->renderer);
		ImGui_ImplSDLRenderer_Init(sdl_context->renderer);
	}

	void ImGuiHandler::destroy()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		delete sdl_context;
		sdl_context = nullptr;
	}

	void ImGuiHandler::processInputs(SDL_Event& e, void(*inputs_callback)(SDL_Event&))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		SDL_assert(inputs_callback);
		inputs_callback(e);
	}

	void ImGuiHandler::refresh(void (*refresh_callback)(SDL_Renderer*))
	{
		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		ImGuiWindowFlags windowflags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoTitleBar;
		

		if (ImGui::Begin("Minesweeper", &isOpen, windowflags)) {
			if (ImGui::BeginMenuBar()) {
				if (ImGui::BeginMenu("Game")) {
					ImGui::EndMenu();
				}
				if (ImGui::MenuItem("Help")) {
				}
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		// Refresh Rendering Platform/Renderer backends
		sdl_context->refresh(refresh_callback);
	}

	void ImGuiHandler::draw(void (*draw_callback)(SDL_Renderer*))
	{
		// Render Platform/Renderer backends and gameobjects
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		sdl_context->draw(draw_callback);
	}
}