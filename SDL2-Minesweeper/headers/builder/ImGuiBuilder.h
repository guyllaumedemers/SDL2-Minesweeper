#pragma once
#include "IBuilder.h"
#include "../composite/Rect.h"

namespace Toolset {
	/// <summary>
	/// base of builder pattern
	/// </summary>
	template<class GraphicAPIsContext>
	class ImGuiBuilder : virtual public IBuilder {
	private:
		ImGuiBuilder(const ImGuiBuilder&) = delete;
		ImGuiBuilder(ImGuiBuilder&&) = delete;
	protected:
		ImGuiBuilder() = default;
		virtual void buildApplicationMenu() = 0;
		virtual void buildGameplayMenu(GraphicAPIsContext*) = 0;
		virtual void buildGameplayUi(GraphicAPIsContext*) = 0;
	public:
		virtual ~ImGuiBuilder() override {};
		virtual void build(GraphicAPIsContext*) = 0;
		virtual void reset() = 0;
	};
}