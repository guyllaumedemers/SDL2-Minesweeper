#pragma once
#include "../../headers/ImGuiMinesweeperBuilder.h"

namespace Minesweeper {
	ImGuiMinesweeperBuilder::ImGuiMinesweeperBuilder()
	{
	}

	ImGuiMinesweeperBuilder::~ImGuiMinesweeperBuilder()
	{
		for (auto& it : builder_parts) {
			delete it;
			it = nullptr;
		}
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
		for (auto& it : builder_parts) {
			delete it;
			it = nullptr;
		}
		builder_parts.clear();
	}
}
