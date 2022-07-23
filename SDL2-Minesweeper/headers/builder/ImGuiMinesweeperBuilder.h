
#ifndef INCLUDED_IMGUIMINESWEEPERBUILDER
#define INCLUDED_IMGUIMINESWEEPERBUILDER

#include "IBuilder.h"
#include "ImGuiBuilder.h"
#include "../SDLHandler.h"
#include "../composite/ImGuiComplexComponent.h"
#include "../composite/components/Tab.h"
#include "../composite/components/Entry.h"
#include "../composite/components/Window.h"
#include "../composite/components/Canvas.h"
#include "../composite/components/ButtonImage.h"
#include "../Mode.h"		//Shouldn't be here -> bad idea
#include "../Screen.h"		//Shouldn't be here -> bad idea
#include "../game/Tile.h"	//Shouldn't be here -> bad idea
#include <vector>
#include <string>

using namespace Toolset;
namespace Minesweeper {
	template<class GraphicAPIsContext>
	class ImGuiMinesweeperBuilder final : virtual public ImGuiBuilder<GraphicAPIsContext> {
	protected:
		ImGuiComplexComponent* builder_parts = nullptr;			//Shouldn't be here -> bad idea
		void buildApplicationMenu() override;
		void buildCanvas() override;
		void buildViewport(GraphicAPIsContext*) override;
	public:
		ImGuiMinesweeperBuilder(const ImGuiMinesweeperBuilder&) = delete;
		ImGuiMinesweeperBuilder(ImGuiMinesweeperBuilder&&) = delete;
		ImGuiMinesweeperBuilder();
		~ImGuiMinesweeperBuilder() override;
		ImGuiMinesweeperBuilder& operator=(const ImGuiMinesweeperBuilder&) = delete;
		ImGuiMinesweeperBuilder& operator=(ImGuiMinesweeperBuilder&&) = delete;
		void build(GraphicAPIsContext*) override;
		void reset() override;
		int getMaxWidth() override;
		int getMaxHeight() override;
	};

	inline static const std::string menu_infos[9] = {
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
	ImGuiMinesweeperBuilder<GraphicAPIsContext>::ImGuiMinesweeperBuilder() : ImGuiBuilder<GraphicAPIsContext>(), IBuilder()
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
		static const std::string menu_callbacks[4] = {
			"onNewGame",
			"onApplicationQuit",
			"onHelpDocumentRequested"
		};

		Tab* game_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		Tab* mode_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[3].c_str());

		std::vector<ImGuiComponent*> game_tab_entries =
		{
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), Mode::Easy),			// need the current mode
			mode_tab,
			new Entry<bool>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[1].c_str(), true)
		};

		std::vector<ImGuiComponent*> mode_tab_entries =
		{
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[4].c_str(), menu_callbacks[0].c_str(), Mode::Easy),
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[5].c_str(), menu_callbacks[0].c_str(), Mode::Medium),
			new Entry<Mode>(Rect(0,0,0,0), menu_infos[6].c_str(), menu_callbacks[0].c_str(), Mode::Hard)
		};

		for (const auto& it : mode_tab_entries) mode_tab->add(it);
		for (const auto& it : game_tab_entries) game_tab->add(it);

		builder_parts->add(game_tab);
		builder_parts->add(new Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[2].c_str(), nullptr));
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildCanvas()
	{
		/// <summary>
		/// Main Window Canvas, holds the info_canvas & holds the Viewport for rendering the game
		/// </summary>
		Canvas& window_canvas = dynamic_cast<Window*>(builder_parts)->getWindowCanvas();
		int w = Screen::w;
		int h = Screen::h;
		int tile = Tile::getTileSize();
		int h_mult = 4;

		/// <summary>
		/// Window info Canvas, holds the Timer, Flag Count, Reset Button -> Rect Total Size : 80px, BUT ImGuiComponents Total Size : 100px //TODO Fix Height Calculation
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
			const std::string button_callbacks[1] = {
				"onNewGame"
			};

			int start_pos_w = (w / 2) - tile;
			int start_pos_h = tile;
			int button_texture_height = tile;
			int button_texture_width = tile;
			/// <summary>
			/// Game Reset setup
			/// </summary>
			ButtonImage* smiley_face_button = new ButtonImage(
				Rect(start_pos_w, start_pos_h, button_texture_width, button_texture_height),
				nullptr,
				button_callbacks->c_str()
				);

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

		window_canvas.add(window_info_canvas);
	}

	template<class GraphicAPIsContext>
	void ImGuiMinesweeperBuilder<GraphicAPIsContext>::buildViewport(GraphicAPIsContext* sdl_context)
	{
		const ImGuiViewport* viewport = ImGui::GetMainViewport();
		SDLHandler* handler_ctx = static_cast<SDLHandler*>(sdl_context);
		int w = Screen::w;
		int h = Screen::h;
		SDL_Texture* texture_id = SDL_CreateTexture(handler_ctx->getRenderer(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		dynamic_cast<Window*>(builder_parts)->getWindowCanvas().getCanvasViewport().setTextureViewport((ImTextureID)texture_id, viewport->ID);
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

		builder_parts = new Window(
			Rect(0, 0, w, h),
			menu_infos[0].c_str(),
			new Style(window_flags, opt_fullscreen, opt_padding)
		);
	}

	template<class GraphicAPIsContext>
	int ImGuiMinesweeperBuilder<GraphicAPIsContext>::getMaxWidth()
	{
		return dynamic_cast<Window*>(builder_parts)->getWindowCanvas().getComponentWidth();
	}

	template<class GraphicAPIsContext>
	int ImGuiMinesweeperBuilder<GraphicAPIsContext>::getMaxHeight()
	{
		return dynamic_cast<Window*>(builder_parts)->getWindowCanvas().getComponentHeight();
	}
}
#endif