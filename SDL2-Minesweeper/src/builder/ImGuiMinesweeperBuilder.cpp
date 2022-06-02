#pragma once
#include "../../headers/ImGuiMinesweeperBuilder.h"
#include "../../headers/composite/Rect.h"
#include "../../headers/composite/components/Entry.h"
#include "../../headers/composite/components/Frame.h"
#include "../../headers/composite/components/Tab.h"

#include <vector>
#include <string>

#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

using namespace std;
namespace Minesweeper {
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

	ImGuiMinesweeperBuilder::ImGuiMinesweeperBuilder() : builder_parts(nullptr)
	{
		reset();
		buildApplicationMenu();
		buildGameplayMenu();
		buildGameplayUi();
	}

	ImGuiMinesweeperBuilder::~ImGuiMinesweeperBuilder()
	{
		delete builder_parts;
		builder_parts = nullptr;
	}

	void ImGuiMinesweeperBuilder::buildApplicationMenu()
	{
#ifdef _DEBUG
		Tab* game_tab = DBG_NEW Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		vector<Entry<void*>*> entries =
		{
			DBG_NEW Entry<void*>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), nullptr),
			DBG_NEW Entry<void*>(Rect(0,0,0,0), menu_infos[3].c_str(), menu_callbacks[1].c_str(), nullptr),
			DBG_NEW Entry<void*>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[2].c_str(), nullptr)
		};
		for (const auto& it : entries) game_tab->add(it);
		builder_parts->add(game_tab);
		builder_parts->add(DBG_NEW Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[3].c_str(), nullptr));
#else	
		Tab* game_tab = new Tab(Rect(0, 0, 0, 0), menu_infos[1].c_str());
		vector<Entry<void*>*> entries =
		{
			new Entry<void*>(Rect(0,0,0,0), menu_infos[2].c_str(), menu_callbacks[0].c_str(), nullptr),
			new Entry<void*>(Rect(0,0,0,0), menu_infos[3].c_str(), menu_callbacks[1].c_str(), nullptr),
			new Entry<void*>(Rect(0,0,0,0), menu_infos[7].c_str(), menu_callbacks[2].c_str(), nullptr)
		};
		for (const auto& it : entries) game_tab->add(it);
		builder_parts->add(game_tab);
		builder_parts->add(new Entry<void*>(Rect(0, 0, 0, 0), menu_infos[8].c_str(), menu_callbacks[3].c_str(), nullptr));
#endif
	}

	void ImGuiMinesweeperBuilder::buildGameplayMenu()
	{
		//Display Timer and Game Reset Button
	}

	void ImGuiMinesweeperBuilder::buildGameplayUi()
	{

		/// <summary>
		/// sdl rendering in imgui window
		/// </summary>
		/*const ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(ImVec2(viewport->WorkPos.x, viewport->WorkPos.y + ImGui::GetFrameHeightWithSpacing()));
		SDL_Texture* rendererTexture = SDL_CreateTexture(sdl_context->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
		ImGui::Image((ImTextureID)rendererTexture, ImVec2(w, h));
		rendererTexture = nullptr;*/
	}

	void ImGuiMinesweeperBuilder::build()
	{
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

		/// <summary>
		/// imgui window begin
		/// </summary>
		ImGui::Begin(menu_infos[0].c_str(), &p_open, window_flags);

		if (!opt_padding)
			ImGui::PopStyleVar();

		if (opt_fullscreen)
			ImGui::PopStyleVar(2);

		builder_parts->refresh();

		ImGui::End();
	}

	void ImGuiMinesweeperBuilder::reset()
	{
		delete builder_parts;
		builder_parts = nullptr;
#ifdef _DEBUG
		builder_parts = DBG_NEW Frame(Rect(0, 0, 0, 0));
#else
		builder_parts = new Frame(Rect(0, 0, 0, 0));
#endif
	}
	}
