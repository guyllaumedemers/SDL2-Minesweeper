#pragma once
#include "../headers/ImGuiHandler.h"
#include "../headers/imgui/TopMenuBar.h"
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	ImGuiHandler::ImGuiHandler(SDLHandler* handler) : sdl_context(handler) { create(sdl_context); }
	ImGuiHandler::~ImGuiHandler() { destroy(); }

	void ImGuiHandler::create(SDLHandler* handler)
	{
#ifdef _DEBUG
		user_interface.push_back(DBG_NEW TopMenuBar(DBG_NEW TopMenuBarImp()));
#else		
		user_interface.push_back(new TopMenuBar(new TopMenuBarImp()));	//Temp solution, will probably create a builder pattern to return proper vector<ImGuiComponent*>
#endif
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForSDLRenderer(handler->window, handler->renderer);
		ImGui_ImplSDLRenderer_Init(handler->renderer);
	}

	void ImGuiHandler::destroy()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		for (auto& it : user_interface) delete it;
		delete sdl_context;
		sdl_context = nullptr;
	}

	void ImGuiHandler::processInputs(SDL_Event& e, void(*inputs_callback)(SDL_Event&))
	{
		ImGui_ImplSDL2_ProcessEvent(&e);
		SDL_assert(inputs_callback);
		inputs_callback(e);
	}

	void ImGuiHandler::refresh(void (*refresh_callback)())
	{
		// Start the Dear ImGui frame
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();

		// Show ImGui Widget
		for (const auto& it : user_interface) it->refresh();

		// Rendering
		ImGui::Render();
		// Refresh Rendering Platform/Renderer backends
		sdl_context->refresh(refresh_callback);
	}

	void ImGuiHandler::draw(void (*draw_callback)())
	{
		// Render Platform/Renderer backends and gameobjects
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		sdl_context->draw(draw_callback);
	}
}