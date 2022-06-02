#pragma once
#include "../composite/Rect.h"

namespace Toolset {
	/// <summary>
	/// base of builder pattern
	/// </summary>
	class ImGuiBuilder {
	private:
		ImGuiBuilder(const ImGuiBuilder&) = delete;
		ImGuiBuilder(ImGuiBuilder&&) = delete;
	protected:
		ImGuiBuilder() {};
	public:
		virtual ~ImGuiBuilder() = 0 {};
		virtual void buildApplicationMenu() = 0;
		virtual void buildGameplayMenu() = 0;
		virtual void buildGameplayUi() = 0;
		virtual void reset() = 0;
	};
}