#pragma once
#include "ImGuiHandlerImp.h"
#include "SDLHandler.h"

#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <imgui_internal.h>

#ifdef _DEBUG
#include "CRTMemoryLeak.h"
#endif

namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandlerImpSDL : virtual public ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent> {
	private:
		SDLHandler* sdl_context = nullptr;
		ImGuiHandlerImpSDL(const ImGuiHandlerImpSDL&) = delete;
		ImGuiHandlerImpSDL(ImGuiHandlerImpSDL&&) = delete;
	public:
		ImGuiHandlerImpSDL(const int&, const int&);
		~ImGuiHandlerImpSDL();
		void processInputs(GraphicAPIsEvent&, void(*)(GraphicAPIsEvent&)) override;
		void refresh(void (*)(GraphicAPIsRendering*), const int&, const int&) override;
		void draw(void (*)(GraphicAPIsRendering*)) override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImpSDL(const int& w, const int& h)
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
	void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::processInputs(GraphicAPIsEvent& e, void(*inputs_callback)(GraphicAPIsEvent&))
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
		static bool opt_fullscreen = true;
		static bool opt_padding = false;
		static bool p_open = true;
		static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

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

		if (!opt_padding) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		static const string menu_infos[9] = {
			"Minesweeper",
			"Game",
			"New Game",
			"Mode",
			"Easy",
			"Medium",
			"Hard",
			"Quit",
			"Help"
		};


		//EventHandler* event_selected = nullptr;
		/// <summary>
		/// imgui window begin
		/// </summary>
		ImGui::Begin(menu_infos[0].c_str(), &p_open, window_flags);

		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		if (ImGui::BeginMenuBar())
		{
			/// <summary>
			/// game menu
			/// </summary>
			if (ImGui::BeginMenu(menu_infos[1].c_str()))
			{
				/// <summary>
				/// new game
				/// </summary>
				if (ImGui::MenuItem(menu_infos[2].c_str())) {
					/*event_selected = EventManager::get("onNewGameSelectedEvent");
					if (event_selected) event_selected->invoke();*/
				}
				/// <summary>
				/// mode selection
				/// </summary>
				if (ImGui::BeginMenu(menu_infos[3].c_str())) {
					/// <summary>
					/// modes
					/// </summary>
					if (ImGui::MenuItem(menu_infos[4].c_str())) {  }
					if (ImGui::MenuItem(menu_infos[5].c_str())) {  }
					if (ImGui::MenuItem(menu_infos[6].c_str())) {  }
					ImGui::EndMenu();
				}
				/// <summary>
				/// exit
				/// </summary>
				if (ImGui::MenuItem(menu_infos[7].c_str())) {  }
				ImGui::EndMenu();
			}
			/// <summary>
			/// help document
			/// </summary>
			if (ImGui::MenuItem(menu_infos[8].c_str())) { }
			ImGui::EndMenuBar();
		}

		/// <summary>
		/// sdl rendering in imgui window
		/// </summary>
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y + ImGui::GetFrameHeightWithSpacing()));
		SDL_Texture* rendererTexture = SDL_CreateTexture(sdl_context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		ImGui::Image((ImTextureID)rendererTexture, ImVec2(w, h));
		rendererTexture = nullptr;

		ImGui::End();
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