#pragma once
#include "bridge/ImGuiHandlerImp.h"
#include "bridge/ImGuiHandlerImpSDL.h"
#include "builder/IBuilder.h"
#include <type_traits>
#include <functional>
//#ifdef SDL
#include <SDL.h>
//#endif

using namespace std;
namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandler {
	private:
		ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>* imp = nullptr;
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
	public:
		ImGuiHandler(IBuilder*, const int&, const int&);
		~ImGuiHandler();
		int pollEvents(void(*)(GraphicAPIsEvent&));
		void refresh(void(*)(GraphicAPIsRendering*));
		void draw(void(*)(GraphicAPIsRendering*));
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandler(IBuilder* builder, const int& w, const int& h)
	{
		//#ifdef SDL
		if (is_same<GraphicAPIsRendering, SDL_Renderer>::value)
			imp = new ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>(builder, new SDLHandler(w, h));
		//#endif
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
	int ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(void(*input_callback)(GraphicAPIsEvent&))
	{
		return imp->pollEvents(input_callback);
	}

	/// <summary>
	/// Game logic for refreshing
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(void(*refresh_callback)(GraphicAPIsRendering*))
	{
		imp->refresh(refresh_callback);
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