#pragma once
#include "bridge/ImGuiHandlerImp.h"
#include "bridge/ImGuiHandlerImpSDL.h"
#include "builder/ImGuiBuilder.h"

#include <SDL.h>
#include <type_traits>

#ifdef _DEBUG
#include "CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandler {
	private:
		ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>* imp = nullptr;
		ImGuiBuilder* builder = nullptr;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
	public:
		ImGuiHandler(ImGuiBuilder*, const int&, const int&);
		~ImGuiHandler();
		void processInputs(GraphicAPIsEvent&, void(*)(GraphicAPIsEvent&));
		void refresh(void (*)(GraphicAPIsRendering*), const int&, const int&);
		void draw(void (*)(GraphicAPIsRendering*));
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandler(ImGuiBuilder* builder, const int& w, const int& h)
	{
#ifdef _DEBUG
		if (is_same<GraphicAPIsRendering, SDL_Renderer>::value) imp = DBG_NEW ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>(w, h);
#else
		if (is_same<GraphicAPIsRendering, SDL_Renderer>::value) imp = new ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>(w, h);
#endif
		this->builder = builder;
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