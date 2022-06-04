#pragma once
#include "InputHandlerImp.h"
#include "../EventHandler.h"
#include <string>
#include <SDL.h>

using namespace std;
namespace Toolset {
	template<class GraphicAPIsEvent>
	class InputHandlerImpSDL : virtual public InputHandlerImp<GraphicAPIsEvent> {
	private:
		InputHandlerImpSDL(const InputHandlerImpSDL&) = delete;
		InputHandlerImpSDL(InputHandlerImpSDL&&) = delete;
	public:
		InputHandlerImpSDL();
		~InputHandlerImpSDL();
		void pollEvents(GraphicAPIsEvent&);
		void getMouseState(int&, int&);
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsEvent>
	InputHandlerImpSDL<GraphicAPIsEvent>::InputHandlerImpSDL()
	{
	}

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