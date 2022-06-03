#pragma once
#include "ImGuiHandlerImp.h"
#include "../SDLHandler.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#ifdef _DEBUG
#include "../CRTMemoryLeak.h"
#endif

namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandlerImpSDL : virtual public ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent> {
	private:
		SDLHandler* sdl_context = nullptr;
		ImGuiHandlerImpSDL(const ImGuiHandlerImpSDL&) = delete;
		ImGuiHandlerImpSDL(ImGuiHandlerImpSDL&&) = delete;
		ImGuiHandlerImpSDL() = delete;
	public:
		ImGuiHandlerImpSDL(ImGuiBuilder*, const int&, const int&);
		~ImGuiHandlerImpSDL();
		void pollEvents(GraphicAPIsEvent&, void(*)(GraphicAPIsEvent&)) override;
		void refresh(void (*)(GraphicAPIsRendering*), const int&, const int&) override;
		void draw(void (*)(GraphicAPIsRendering*)) override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImpSDL(ImGuiBuilder* builder_context, const int& w, const int& h) : ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>(builder_context)
	{
#ifdef _DEBUG
		sdl_context = DBG_NEW SDLHandler(w, h);
#else
		sdl_context = new SDLHandler(w, h);
#endif
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImGui::StyleColorsDark();
		ImGui_ImplSDL2_InitForSDLRenderer(sdl_context->window, sdl_context->renderer);
		ImGui_ImplSDLRenderer_Init(sdl_context->renderer);
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandlerImpSDL()
	{
		ImGui_ImplSDLRenderer_Shutdown();
		ImGui_ImplSDL2_Shutdown();
		ImGui::DestroyContext();
		delete sdl_context;
		sdl_context = nullptr;
	}

	/// <summary>
	/// Game logic for input processing
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e, void(*inputs_callback)(GraphicAPIsEvent&))
	{
		ImGui_ImplSDL2_ProcessEvent((SDL_Event*)&e);
		if (ImGui::IsAnyItemHovered()) return;
		SDL_assert(inputs_callback);
		inputs_callback(e);
	}

	/// <summary>
	/// Game logic for refreshing
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(void(*refresh_callback)(GraphicAPIsRendering*), const int& w, const int& h)
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		builder_context->build();
		ImGui::Render();
		sdl_context->refresh(refresh_callback);
	}

	/// <summary>
	/// Game logic for drawing 
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::draw(void(*draw_callback)(GraphicAPIsRendering*))
	{
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
		sdl_context->draw(draw_callback);
	}
}