#pragma once
#include "builder/ImGuiBuilder.h"
#include "composite/ImGuiComponent.h"
#include <vector>

using namespace Toolset;
namespace Minesweeper {
	/// <summary>
	/// concrete builder
	/// </summary>
	class ImGuiMinesweeperBuilder : virtual public ImGuiBuilder {
	private:
		vector<ImGuiComponent*> builder_parts;
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