#pragma once
#include "ImGuiBuilder.h"
#include "../composite/ImGuiComplexComponent.h"
#include "../../headers/composite/components/Tab.h"
#include "../../headers/composite/components/Entry.h"
#include "../../headers/composite/components/Window.h"
#include "../../headers/Mode.h"
#include "../SDLHandler.h"
#include "../Screen.h"

#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#include <vector>
#include <string>

#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

using namespace Toolset;
namespace Minesweeper {
	/// <summary>
	/// concrete builder
	/// </summary>
	template<class GraphicAPIsContext>
	class ImGuiMinesweeperBuilder : virtual public ImGuiBuilder<GraphicAPIsContext> {
	private:
		ImGuiComplexComponent* builder_parts = nullptr;
		ImGuiMinesweeperBuilder(const ImGuiMinesweeperBuilder&) = delete;
		ImGuiMinesweeperBuilder(ImGuiMinesweeperBuilder&&) = delete;
	protected:
		void buildApplicationMenu() override;
		void buildGameplayMenu(GraphicAPIsContext*) override;
		void buildGameplayUi(GraphicAPIsContext*) override;
	public:
		ImGuiMinesweeperBuilder();
		~ImGuiMinesweeperBuilder();
		void build(GraphicAPIsContext*) override;
		void reset() override;
	};


	/// <summary>
	/// static fields
	/// </summary>
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

	static const string menu_callbacks[4] = {
		"onNewGame",
		"onModeChanged",
		"onApplicationQuit",
		"onHelpDocumentRequested"
	};

	template<class GraphicAPIsContext>
	ImGuiMinesweeperBuilder<GraphicAPIsContext>::ImGuiMinesweeperBuilder() : builder_parts(nullptr)
	{
		reset();
		buildApplicationMenu();
	}

	template<class GraphicAPIsContext>
	ImGuiMinesweeperBuilder<GraphicAPIsContext>::~ImGuiMinesweeperBuilder()
	{
		delete builder_parts;
		builder_parts = nullptr;
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildApplicationMenu()
	{
#ifdef _DEBUG
		Tab* game_tab = DBG_NEW Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		Tab* mode_tab = DBG_NEW Tab(Rect(0, 0, 0, 0), menu_infos[3].c_str());
		vector<ImGuiComponent*> game_tab_entries =
		{
			DBG_NEW Entry<void*>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), nullptr),
			mode_tab,
			DBG_NEW Entry<void*>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[2].c_str(), nullptr)
		};
		vector<ImGuiComponent*> mode_tab_entries =
		{
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[4].c_str(), menu_callbacks[1].c_str(), Mode::Easy),
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[5].c_str(), menu_callbacks[1].c_str(), Mode::Medium),
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[6].c_str(), menu_callbacks[1].c_str(), Mode::Hard)
		};
		for (const auto& it : mode_tab_entries) mode_tab->add(it);
		for (const auto& it : game_tab_entries) game_tab->add(it);
		builder_parts->add(game_tab);
		builder_parts->add(DBG_NEW Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[3].c_str(), nullptr));
#else	
		Tab* game_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		Tab* mode_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[3].c_str());
		vector<ImGuiComponent*> game_tab_entries =
		{
			new Entry<void*>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), nullptr),
			mode_tab,
			new Entry<void*>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[2].c_str(), nullptr)
		};
		vector<ImGuiComponent*> mode_tab_entries =
		{
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[4].c_str(), menu_callbacks[1].c_str(), Mode::Easy),
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[5].c_str(), menu_callbacks[1].c_str(), Mode::Medium),
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[6].c_str(), menu_callbacks[1].c_str(), Mode::Hard)
		};
		for (const auto& it : mode_tab_entries) mode_tab->add(it);
		for (const auto& it : game_tab_entries) game_tab->add(it);
		builder_parts->add(game_tab);
		builder_parts->add(new Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[3].c_str(), nullptr));
#endif
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildGameplayMenu(GraphicAPIsContext* sdl_context)
	{

	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildGameplayUi(GraphicAPIsContext* sdl_context)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		SDLHandler* handler_ctx = static_cast<SDLHandler*>(sdl_context);
		int w = Screen::w;
		int h = Screen::h;
		SDL_Texture* texture_id = SDL_CreateTexture(handler_ctx->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		dynamic_cast<Window*>(builder_parts)->getviewport()->setviewport((ImTextureID)texture_id, viewport->ID);
		texture_id = nullptr;
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::build(GraphicAPIsContext* sdl_context)
	{
		buildGameplayMenu(sdl_context);
		buildGameplayUi(sdl_context);
		builder_parts->refresh();
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::reset()
	{
		delete builder_parts;
		builder_parts = nullptr;

		bool opt_fullscreen = true;
		bool opt_padding = false;
		ImGuiWindowFlags window_flags = ImGuiWindowFlags_None;
		int w = Screen::w;
		int h = Screen::h;

#ifdef _DEBUG
		builder_parts = DBG_NEW Window(
			Rect(0, 0, w, h),
			menu_infos[0].c_str(),
			DBG_NEW Style(window_flags, opt_fullscreen, opt_padding)
		);
#else
		builder_parts = new Window(
			Rect(0, 0, w, h),
			menu_infos[0].c_str(),
			new Style(window_flags, opt_fullscreen, opt_padding)
		);
#endif
	}
}