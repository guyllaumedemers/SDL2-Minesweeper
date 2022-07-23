/*
 *	Why use final? https://en.cppreference.com/w/cpp/language/final
 *
 */

#ifndef INCLUDED_INPUTHANDLERIMPSDL
#define INCLUDED_INPUTHANDLERIMPSDL

#include "InputHandlerImp.h"
#include "../EventHandler.h"
#include <SDL.h>
#include <string>

namespace Toolset {
	template<class GraphicAPIsEvent>
	class InputHandlerImpSDL final : virtual public InputHandlerImp<GraphicAPIsEvent> {
	public:
		InputHandlerImpSDL(const InputHandlerImpSDL&) = delete;
		InputHandlerImpSDL(InputHandlerImpSDL&&) = delete;
		InputHandlerImpSDL() = default;
		~InputHandlerImpSDL() override;
		InputHandlerImpSDL& operator=(const InputHandlerImpSDL&) = delete;
		InputHandlerImpSDL& operator=(InputHandlerImpSDL&&) = delete;
		void pollEvents(GraphicAPIsEvent&) override;
		void getMouseState(int&, int&) override;
	};

	template<class GraphicAPIsEvent>
	inline InputHandlerImpSDL<GraphicAPIsEvent>::~InputHandlerImpSDL()
	{}

	template<class GraphicAPIsEvent>
	inline void InputHandlerImpSDL<GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e)
	{
		static const std::string keys[] = {
			"onApplicationQuit",
			"onMouseDown"
		};

		switch (e.type)
		{
		case SDL_QUIT:
			EventHandler::invoke<bool>(keys[0], true);
			break;
		case SDL_MOUSEBUTTONDOWN:
			switch (e.button.button)
			{
			case SDL_BUTTON_LEFT:
				EventHandler::invoke<int>(keys[1], 0);
				break;
			case SDL_BUTTON_RIGHT:
				EventHandler::invoke<int>(keys[1], 1);
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
	}

	template<class GraphicAPIsEvent>
	inline void InputHandlerImpSDL<GraphicAPIsEvent>::getMouseState(int& x, int& y)
	{
		SDL_GetMouseState(&x, &y);
	}
}
#endif