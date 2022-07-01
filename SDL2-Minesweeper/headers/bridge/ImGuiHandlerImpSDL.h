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
		IBuilder* builder_context = nullptr;
		SDLHandler* sdl_context = nullptr;
		ImGuiHandlerImpSDL(const ImGuiHandlerImpSDL&) = delete;
		ImGuiHandlerImpSDL(ImGuiHandlerImpSDL&&) = delete;
		ImGuiHandlerImpSDL() = delete;
	public:
		ImGuiHandlerImpSDL(IBuilder*, const int&, const int&);
		~ImGuiHandlerImpSDL();
		int pollEvents(void(*)(GraphicAPIsEvent&)) override;
		void refresh(void (*)(GraphicAPIsRendering*)) override;
		void draw(void (*)(GraphicAPIsRendering*)) override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImpSDL(IBuilder* builder_context, const int& w, const int& h) : builder_context(builder_context), ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>()
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
	int ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(void(*inputs_callback)(GraphicAPIsEvent&))
	{
		SDL_Event e;
		if (SDL_WaitEvent(&e) > 0)
		{
			if (ImGui_ImplSDL2_ProcessEvent(&e) && ImGui::IsAnyItemHovered()) return 1;
			inputs_callback(e);
			return 1;
		}
		return 0;
	}

	/// <summary>
	/// Game logic for refreshing
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(void(*refresh_callback)(GraphicAPIsRendering*))
	{
		ImGui_ImplSDLRenderer_NewFrame();
		ImGui_ImplSDL2_NewFrame();
		ImGui::NewFrame();
		dynamic_cast<ImGuiBuilder<SDLHandler>*>(builder_context)->build(sdl_context);
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