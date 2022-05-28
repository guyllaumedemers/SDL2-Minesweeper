#pragma once
#include "ImGuiHandlerImp.h"
#include "ImGuiHandlerImpSDL.h"

#include <SDL.h>

#ifdef _DEBUG
#include "CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandler {
	private:
		ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>* imp = nullptr;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
	public:
		ImGuiHandler(const int&, const int&);
		~ImGuiHandler();
		void processInputs(GraphicAPIsEvent&, void(*)(GraphicAPIsEvent&));
		void refresh(void (*)(GraphicAPIsRendering*), const int&, const int&);
		void draw(void (*)(GraphicAPIsRendering*));
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandler(const int& w, const int& h)
	{
#ifdef _DEBUG
		imp = DBG_NEW ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>(w, h);
#else
		imp = new ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>(w, h);
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandler()
	{
		delete imp;
		imp = nullptr;
	}

	/// <summary>
	/// Game logic for input processing
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::processInputs(GraphicAPIsEvent& e, void(*input_callback)(GraphicAPIsEvent&))
	{
		imp->processInputs(e, input_callback);
	}

	/// <summary>
	/// Game logic for refreshing
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(void(*refresh_callback)(GraphicAPIsRendering*), const int& w, const int& h)
	{
		imp->refresh(refresh_callback, w, h);
	}

	/// <summary>
	/// Game logic for drawing 
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::draw(void(*draw_callback)(GraphicAPIsRendering*))
	{
		imp->draw(draw_callback);
	}
}