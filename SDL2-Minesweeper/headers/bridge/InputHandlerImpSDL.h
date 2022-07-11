#pragma once
#include "InputHandlerImp.h"
#include "../EventHandler.h"
#include <string>
#include <SDL.h>

/*
 *	Why use final? https://en.cppreference.com/w/cpp/language/final
 *
 */

using namespace std;
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

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsEvent>
	InputHandlerImpSDL<GraphicAPIsEvent>::~InputHandlerImpSDL()
	{
	}

	/// <summary>
	/// Polling input events
	/// </summary>
	template<class GraphicAPIsEvent>
	void InputHandlerImpSDL<GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e)
	{
		static const string keys[] = {
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
			}
			break;
		default:
			break;
		}
	}

	/// <summary>
	/// Polling input events
	/// </summary>
	template<class GraphicAPIsEvent>
	void InputHandlerImpSDL<GraphicAPIsEvent>::getMouseState(int& x, int& y)
	{
		SDL_GetMouseState(&x, &y);
	}
}