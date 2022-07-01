#pragma once
#include "IBuilder.h"

namespace Toolset {
	/// <summary>
	/// builder pattern interface
	/// </summary>
	template<class GraphicAPIsContext>
	class ImGuiBuilder : virtual public IBuilder {
	private:
		ImGuiBuilder(const ImGuiBuilder&) = delete;
		ImGuiBuilder(ImGuiBuilder&&) = delete;
	protected:
		ImGuiBuilder();
		virtual void buildApplicationMenu() = 0;
		virtual void buildCanvas() = 0;
		virtual void buildViewport(GraphicAPIsContext*) = 0;
	public:
		virtual ~ImGuiBuilder() override;
		virtual void build(GraphicAPIsContext*) = 0;
		virtual void reset() = 0;
		virtual int getMaxWidth() = 0;
		virtual int getMaxHeight() = 0;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsContext>
	ImGuiBuilder<GraphicAPIsContext>::ImGuiBuilder() : IBuilder()
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsContext>
	ImGuiBuilder<GraphicAPIsContext>::~ImGuiBuilder()
	{
	}
}