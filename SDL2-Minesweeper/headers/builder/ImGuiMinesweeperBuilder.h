#pragma once
#include "ImGuiBuilder.h"
#include "../composite/ImGuiComplexComponent.h"

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
	protected:
		void buildApplicationMenu() override;
		void buildGameplayMenu() override;
		void buildGameplayUi() override;
	public:
		ImGuiMinesweeperBuilder();
		~ImGuiMinesweeperBuilder();
		void build() override;
		void reset() override;
	};
}