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
	protected:
		ImGuiHandlerImp();
	public:
		virtual ~ImGuiHandlerImp() = 0;
		virtual int pollEvents(void(*)(GraphicAPIsEvent&)) = 0;
		virtual void refresh(void (*)(GraphicAPIsRendering*)) = 0;
		virtual void draw(void (*)(GraphicAPIsRendering*)) = 0;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImp()
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandlerImp()
	{
	}
}