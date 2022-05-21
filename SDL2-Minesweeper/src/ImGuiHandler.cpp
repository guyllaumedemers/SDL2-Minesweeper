#pragma once
#include "../headers/ImGuiHandler.h"
#include "../headers/game/Screen.h"
#include "../headers/game/Tile.h"
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <imgui_internal.h>
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif
#include <iostream>

using namespace Minesweeper;
using namespace std;
namespace Toolset {
	static SDL_Texture* rendererTexture = nullptr;
	ImGuiHandler::ImGuiHandler() : sdl_context(nullptr) { create(); }
	ImGuiHandler::~ImGuiHandler() { destroy(); }

	void ImGuiHandler::create()
	{
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		//io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
		ImGui::StyleColorsDark();
#ifdef _DEBUG
		sdl_context = DBG_NEW SDLHandler(Screen::w, Screen::h);
#else
		sdl_context = new SDLHandler(Screen::w, Screen::h);
#endif
		ImGui_ImplSDL2_InitForSDLRenderer(sdl_context->window, sdl_context->renderer);
		ImGui_ImplSDLRenderer_Init(sdl_context->renderer);
	}

	void ImGuiHandler::destroy()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		SDL_DestroyTexture(rendererTexture);
		rendererTexture = nullptr;
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

		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static bool p_open = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

		// We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
		// because it would be confusing to have two docking targets within each others.
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
		if (opt_fullscreen)
		{
			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
			ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
			window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar;
		}
		else
		{
			dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
		}

		// When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
		// and handle the pass-thru hole, so we ask Begin() to not render a background.
		if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
			window_flags |= ImGuiWindowFlags_NoBackground;

		// Important: note that we proceed even if Begin() returns false (aka window is collapsed).
		// This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
		// all active windows docked into it will lose their parent and become undocked.
		// We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
		// any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
		if (!opt_padding)
			ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("DockSpace Demo", &p_open, window_flags);
		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		// Submit the DockSpace
		ImGuiIO& io = ImGui::GetIO();
		if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
		{
			ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
			ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
		}

		//if (ImGui::BeginMenuBar())
		//{
		//	if (ImGui::BeginMenu("Game"))
		//	{
		//		if (ImGui::MenuItem("New Game")) {/*Create New Game Callback*/ }
		//		if (ImGui::BeginMenu("Mode")) {
		//			if (ImGui::MenuItem("Easy")) { /*Set Mode Callback*/ }
		//			if (ImGui::MenuItem("Medium")) { /*Set Mode Callback*/ }
		//			if (ImGui::MenuItem("Hard")) { /*Set Mode Callback*/ }
		//			ImGui::EndMenu();
		//		}
		//		if (ImGui::MenuItem("Quit")) { /*Exit Callback*/ }
		//		ImGui::EndMenu();
		//	}
		//	if (ImGui::MenuItem("Help")) { /*Display Doc Help*/ }
		//	ImGui::EndMenuBar();
		//}

		rendererTexture = SDL_CreateTexture(sdl_context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, Screen::w, Screen::h);
		ImGui::Image((ImTextureID)rendererTexture, ImVec2(Screen::w, Screen::h));

		ImGui::End();

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