#pragma once
#include "../builder/IBuilder.h"

using namespace std;
namespace Toolset {
	/// <summary>
	/// Generic Type class using bridge pattern to pass args data to grahic APIs lib
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandlerImp {
	private:
		ImGuiHandlerImp(const ImGuiHandlerImp&) = delete;
		ImGuiHandlerImp(ImGuiHandlerImp&&) = delete;
		ImGuiHandlerImp() = delete;
	protected:
		IBuilder* builder_context = nullptr;
		ImGuiHandlerImp(IBuilder*);
	public:
		virtual ~ImGuiHandlerImp() = 0;
		virtual void pollEvents(GraphicAPIsEvent&, void(*)(GraphicAPIsEvent&)) = 0;
		virtual void refresh(void (*)(GraphicAPIsRendering*), const int&, const int&) = 0;
		virtual void draw(void (*)(GraphicAPIsRendering*)) = 0;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImp(IBuilder* builder_context) : builder_context(builder_context)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandlerImp()
	{
		delete builder_context;
		builder_context = nullptr;
	}
}