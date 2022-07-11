#pragma once
#include "bridge/InputHandlerImp.h"
#include "bridge/InputHandlerImpSDL.h"
#include <type_traits>
//#ifdef SDL
#include <SDL.h>
//#endif

namespace Toolset {
	template<class GraphicAPIsEvent>
	class InputHandler {
	private:
		InputHandlerImp<GraphicAPIsEvent>* imp = nullptr;
	public:
		InputHandler(const InputHandler&) = delete;
		InputHandler(InputHandler&&) = delete;
		InputHandler();
		virtual ~InputHandler() = 0;
		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler& operator=(InputHandler&&) = delete;
		void pollEvents(GraphicAPIsEvent&);
		void getMouseState(int&, int&);
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsEvent>
	InputHandler<GraphicAPIsEvent>::InputHandler()
	{
		//#ifdef SDL
		if (is_same<GraphicAPIsEvent, SDL_Event>::value) imp = new InputHandlerImpSDL<GraphicAPIsEvent>();
		//#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsEvent>
	InputHandler<GraphicAPIsEvent>::~InputHandler()
	{
		delete imp;
		imp = nullptr;
	}

	/// <summary>
	/// Polling input events
	/// </summary>
	template<class GraphicAPIsEvent>
	void InputHandler<GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e)
	{
		imp->pollEvents(e);
	}

	/// <summary>
	/// Polling input events
	/// </summary>
	template<class GraphicAPIsEvent>
	void InputHandler<GraphicAPIsEvent>::getMouseState(int& x, int& y)
	{
		imp->getMouseState(x, y);
	}
}