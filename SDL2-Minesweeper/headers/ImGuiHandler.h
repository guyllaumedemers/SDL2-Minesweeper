
#ifndef INCLUDED_IMGUIHANDLER
#define INCLUDED_IMGUIHANDLER

#include "bridge/ImGuiHandlerImp.h"
#include "bridge/ImGuiHandlerImpSDL.h"
#include "builder/IBuilder.h"
#include "SDLHandler.h"

namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class ImGuiHandler {
		ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>* imgui_imp = nullptr;
	public:
		ImGuiHandler(const ImGuiHandler&) = delete;
		ImGuiHandler(ImGuiHandler&&) = delete;
		ImGuiHandler() = delete;
		ImGuiHandler(IBuilder*, const int&, const int&);
		~ImGuiHandler();
		ImGuiHandler& operator=(const ImGuiHandler&) = delete;
		ImGuiHandler& operator=(ImGuiHandler&&) = delete;
		int pollEvents(void(*)(GraphicAPIsEvent&));
		void refresh(void(*)(GraphicAPIsRendering*));
		void draw(void(*)(GraphicAPIsRendering*));
	};

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandler(IBuilder* builder, const int& w, const int& h)
	{
		if (std::is_same_v<GraphicAPIsRendering, SDL_Renderer>)
			imgui_imp = new ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>(builder, new SDLHandler(w, h));
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandler()
	{
		delete imgui_imp;
		imgui_imp = nullptr;
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline int ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(void(*input_callback)(GraphicAPIsEvent&))
	{
		return imgui_imp->pollEvents(input_callback);
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(void(*refresh_callback)(GraphicAPIsRendering*))
	{
		imgui_imp->refresh(refresh_callback);
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void ImGuiHandler<GraphicAPIsRendering, GraphicAPIsEvent>::draw(void(*draw_callback)(GraphicAPIsRendering*))
	{
		imgui_imp->draw(draw_callback);
	}
}
#endif