
#ifndef INCLUDED_INPUTHANDLER
#define INCLUDED_INPUTHANDLER

#include "bridge/InputHandlerImp.h"
#include "bridge/InputHandlerImpSDL.h"
#include <type_traits>

namespace Toolset {
	template<class GraphicAPIsEvent>
	class InputHandler {
		InputHandlerImp<GraphicAPIsEvent>* input_imp = nullptr;
	public:
		InputHandler(const InputHandler&) = delete;
		InputHandler(InputHandler&&) = delete;
		InputHandler();
		~InputHandler();
		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler& operator=(InputHandler&&) = delete;
		void pollEvents(GraphicAPIsEvent&);
		void getMouseState(int&, int&);
	};

	template<class GraphicAPIsEvent>
	inline InputHandler<GraphicAPIsEvent>::InputHandler()
	{
		if (std::is_same<GraphicAPIsEvent, SDL_Event>::value) input_imp = new InputHandlerImpSDL<GraphicAPIsEvent>();
	}

	template<class GraphicAPIsEvent>
	inline InputHandler<GraphicAPIsEvent>::~InputHandler()
	{
		delete input_imp;
		input_imp = nullptr;
	}

	template<class GraphicAPIsEvent>
	inline void InputHandler<GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e)
	{
		input_imp->pollEvents(e);
	}

	template<class GraphicAPIsEvent>
	inline void InputHandler<GraphicAPIsEvent>::getMouseState(int& x, int& y)
	{
		input_imp->getMouseState(x, y);
	}
}
#endif