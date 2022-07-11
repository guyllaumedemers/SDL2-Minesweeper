#pragma once
#include "IBuilder.h"

namespace Toolset {
	/// <summary>
	/// builder pattern interface
	/// </summary>
	template<class GraphicAPIsContext>
	class ImGuiBuilder : virtual public IBuilder {
	protected:
		ImGuiBuilder() = default;
		virtual void buildApplicationMenu() = 0;
		virtual void buildCanvas() = 0;
		virtual void buildViewport(GraphicAPIsContext*) = 0;
	public:
		ImGuiBuilder(const ImGuiBuilder&) = delete;
		ImGuiBuilder(ImGuiBuilder&&) = delete;
		virtual ~ImGuiBuilder() = 0 {};
		ImGuiBuilder& operator=(const ImGuiBuilder&) = delete;
		ImGuiBuilder& operator=(ImGuiBuilder&&) = delete;
		virtual void build(GraphicAPIsContext*) = 0;
		virtual void reset() = 0;
		virtual int getMaxWidth() = 0;
		virtual int getMaxHeight() = 0;
	};
}