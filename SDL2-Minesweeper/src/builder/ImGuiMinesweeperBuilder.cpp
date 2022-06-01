#pragma once
#include "../../headers/ImGuiMinesweeperBuilder.h"
#include "../../headers/composite/components/Frame.h"

#ifdef _DEBUG
#include "../../headers/CRTMemoryLeak.h"
#endif

namespace Minesweeper {
	ImGuiMinesweeperBuilder::ImGuiMinesweeperBuilder() : builder_parts(nullptr)
	{
	}

	ImGuiMinesweeperBuilder::~ImGuiMinesweeperBuilder()
	{
		delete builder_parts;
		builder_parts = nullptr;
	}

	void ImGuiMinesweeperBuilder::buildApplicationMenu()
	{
		//Add top menu bar
	}

	void ImGuiMinesweeperBuilder::buildGameplayMenu()
	{
		//Add header menu for timer display with game reset
	}

	void ImGuiMinesweeperBuilder::buildGameplayUi()
	{
		//Print SDL_Renderer ctx on ImGui image
	}

	void ImGuiMinesweeperBuilder::reset()
	{
		delete builder_parts;
#ifdef _DEBUG
		builder_parts = DBG_NEW Frame(Rect(0, 0, 0, 0));
#else
		builder_parts = new Frame(Rect(0, 0, 0, 0));
#endif
	}
}
