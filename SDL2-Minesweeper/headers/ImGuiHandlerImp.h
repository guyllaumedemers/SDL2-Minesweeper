#pragma once
#include <iostream>

using namespace std;
namespace Toolset {
	/// <summary>
	/// Generic Type class using bridge pattern to pass args data to grahic APIs lib
	/// </summary>
	/// <typeparam name="GraphicAPIsRendering"></typeparam>
	/// <typeparam name="GraphicAPIsEvent"></typeparam>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandlerImp {
	private:
		ImGuiHandlerImp(const ImGuiHandlerImp&) = delete;
		ImGuiHandlerImp(ImGuiHandlerImp&&) = delete;
	protected:
		ImGuiHandlerImp();
	public:
		virtual ~ImGuiHandlerImp() = 0;
		virtual void processInputs(GraphicAPIsEvent&, void(*)(GraphicAPIsEvent&)) = 0;
		virtual void refresh(void (*)(GraphicAPIsRendering*), const int&, const int&) = 0;
		virtual void draw(void (*)(GraphicAPIsRendering*)) = 0;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImp()
	{
		cout << "Base Constructor" << endl;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandlerImp()
	{
		cout << "Base Destructor" << endl;
	}
}