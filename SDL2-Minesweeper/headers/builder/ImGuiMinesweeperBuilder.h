#pragma once
#include "ImGuiBuilder.h"
#include "../composite/ImGuiComplexComponent.h"
#include "../../headers/composite/components/Window.h"
#include "../../headers/composite/components/Canvas.h"
#include "../../headers/composite/components/Button.h"
#include "../../headers/composite/components/ButtonImage.h"
#include "../../headers/composite/components/Tab.h"
#include "../../headers/composite/components/Entry.h"
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
		void buildCanvas() override;
		void buildViewport(GraphicAPIsContext*) override;
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

	template<class GraphicAPIsContext>
	ImGuiMinesweeperBuilder<GraphicAPIsContext>::ImGuiMinesweeperBuilder() : builder_parts(nullptr)
	{
		reset();
		buildApplicationMenu();
		buildCanvas();
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
		const string menu_callbacks[4] = {
			"onNewGame",
			"onApplicationQuit",
			"onHelpDocumentRequested"
		};

#ifdef _DEBUG
		Tab* game_tab = DBG_NEW Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		Tab* mode_tab = DBG_NEW Tab(Rect(0, 0, 0, 0), menu_infos[3].c_str());
		vector<ImGuiComponent*> game_tab_entries =
		{
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), Mode::Easy),		// need the current mode
			mode_tab,
			DBG_NEW Entry<bool>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[1].c_str(), true)
		};
		vector<ImGuiComponent*> mode_tab_entries =
		{
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[4].c_str(), menu_callbacks[0].c_str(), Mode::Easy),
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[5].c_str(), menu_callbacks[0].c_str(), Mode::Medium),
			DBG_NEW Entry<Mode>(Rect(0,0,0,0), menu_infos[6].c_str(), menu_callbacks[0].c_str(), Mode::Hard)
		};
		for (const auto& it : mode_tab_entries) mode_tab->add(it);
		for (const auto& it : game_tab_entries) game_tab->add(it);
		builder_parts->add(game_tab);
		builder_parts->add(DBG_NEW Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[2].c_str(), nullptr));
#else	
		Tab* game_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		Tab* mode_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[3].c_str());
		vector<ImGuiComponent*> game_tab_entries =
		{
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), Mode::Easy),			// need the current mode
			mode_tab,
			new Entry<bool>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[1].c_str(), true)
		};
		vector<ImGuiComponent*> mode_tab_entries =
		{
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[4].c_str(), menu_callbacks[0].c_str(), Mode::Easy),
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[5].c_str(), menu_callbacks[0].c_str(), Mode::Medium),
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[6].c_str(), menu_callbacks[0].c_str(), Mode::Hard)
		};
		for (const auto& it : mode_tab_entries) mode_tab->add(it);
		for (const auto& it : game_tab_entries) game_tab->add(it);
		builder_parts->add(game_tab);
		builder_parts->add(new Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[2].c_str(), nullptr));
#endif
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildCanvas()
	{
		/// <summary>
		/// Main Window Canvas, holds the info_canvas & holds the Viewport for rendering the game
		/// </summary>
		Canvas* window_canvas = dynamic_cast<Window*>(builder_parts)->getWindowCanvas();
		int w = Screen::w;
		int h = Screen::h;
		int tile = Tile::size;
		int h_mult = 4;

		/// <summary>
		/// Window info Canvas, holds the Timer, Flag Count, Reset Button
		/// </summary>
		Canvas* window_info_canvas = new Canvas(Rect(0, 0, w, h_mult * tile));

		{
			int timer_w_mult = 3;
			int timer_h_mult = 2;
			int start_pos_w = tile;
			int start_pos_h = tile;
			int max_w = tile * timer_w_mult;
			int max_h = tile * timer_h_mult;
			Canvas* timer_canvas = new Canvas(Rect(start_pos_w, start_pos_h, max_w, max_h));
			/// <summary>
			/// Timer texture setup
			/// </summary>
			int timer_texture_height = tile * timer_h_mult;
			int timer_texture_width = tile;
			timer_canvas->add(new Image(Rect(timer_canvas->getComponentWidth(), 0, timer_texture_width, timer_texture_height)));
			timer_canvas->add(new Image(Rect(timer_canvas->getComponentWidth(), 0, timer_texture_width, timer_texture_height)));
			timer_canvas->add(new Image(Rect(timer_canvas->getComponentWidth(), 0, timer_texture_width, timer_texture_height)));

			window_info_canvas->add(timer_canvas);
		}

		{
			const string button_callbacks[1] = {
				"onNewGame"
			};

			int start_pos_w = (w / 2) - tile;
			int start_pos_h = tile;
			int button_texture_height = tile;
			int button_texture_width = tile;
			/// <summary>
			/// Game Reset setup
			/// </summary>
			Button* smiley_face_button = new ButtonImage(Rect(start_pos_w, start_pos_h, button_texture_width, button_texture_height), "", button_callbacks->c_str());

			window_info_canvas->add(smiley_face_button);
		}

		{
			int flag_w_mult = 3;
			int flag_h_mult = 2;
			int start_pos_w = w - tile - (flag_w_mult * tile);
			int start_pos_h = tile;
			int max_w = tile * flag_w_mult;
			int max_h = tile * flag_h_mult;
			Canvas* flag_canvas = new Canvas(Rect(start_pos_w, tile, max_w, max_h));
			/// <summary>
			/// Flag texture setup
			/// </summary>
			int flag_texture_height = tile * flag_h_mult;
			int flag_texture_width = tile;
			flag_canvas->add(new Image(Rect(flag_canvas->getComponentWidth(), 0, flag_texture_width, flag_texture_height)));
			flag_canvas->add(new Image(Rect(flag_canvas->getComponentWidth(), 0, flag_texture_width, flag_texture_height)));
			flag_canvas->add(new Image(Rect(flag_canvas->getComponentWidth(), 0, flag_texture_width, flag_texture_height)));

			window_info_canvas->add(flag_canvas);
		}

		window_canvas->add(window_info_canvas);
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildViewport(GraphicAPIsContext* sdl_context)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		SDLHandler* handler_ctx = static_cast<SDLHandler*>(sdl_context);
		int w = Screen::w;
		int h = Screen::h;
		SDL_Texture* texture_id = SDL_CreateTexture(handler_ctx->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		dynamic_cast<Window*>(builder_parts)->getWindowCanvas()->getCanvasViewport()->setTextureViewport((ImTextureID)texture_id, viewport->ID);
		texture_id = nullptr;
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::build(GraphicAPIsContext* sdl_context)
	{
		buildViewport(sdl_context);
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