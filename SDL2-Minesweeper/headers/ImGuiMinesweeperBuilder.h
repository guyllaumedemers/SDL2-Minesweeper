#pragma once
#include "builder/ImGuiBuilder.h"
#include "composite/ImGuiComplexComponent.h"
#include <vector>

using namespace Toolset;
namespace Minesweeper {
	/// <summary>
	/// concrete builder
	/// </summary>
	class ImGuiMinesweeperBuilder : virtual public ImGuiBuilder {
	private:
		ImGuiComplexComponent* builder_parts = nullptr;
		ImGuiMinesweeperBuilder(const ImGuiMinesweeperBuilder&) = delete;
		ImGuiMinesweeperBuilder(ImGuiMinesweeperBuilder&&) = delete;
	public:
		ImGuiMinesweeperBuilder();
		~ImGuiMinesweeperBuilder();
		void buildApplicationMenu() override;
		void buildGameplayMenu() override;
		void buildGameplayUi() override;
		void reset() override;
	};
}