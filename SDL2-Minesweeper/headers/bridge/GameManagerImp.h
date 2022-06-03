#pragma once
#include "../Mode.h"
#include "../LevelHandler.h"
#include "../InputHandler.h"

#ifdef _DEBUG
#include "../CRTMemoryLeak.h"
#endif

namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class GameManagerImp {
	private:
		LevelHandler<GraphicAPIsRendering>* level_context = nullptr;
		InputHandler<GraphicAPIsEvent>* input_context = nullptr;
		GameManagerImp(const GameManagerImp&) = delete;
		GameManagerImp(GameManagerImp&&) = delete;
		GameManagerImp() = delete;
	public:
		GameManagerImp(const Mode&, void(*)(const int&, const int&));
		~GameManagerImp();
		void pollEvents(GraphicAPIsEvent&);
		void processInputs(const int&);
		void refresh(GraphicAPIsRendering*, const int&, const int&);
		void draw(GraphicAPIsRendering*);
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::GameManagerImp(const Mode& mode, void(*screen_callback)(const int&, const int&))
	{
#ifdef _DEBUG
		level_context = DBG_NEW LevelHandler<GraphicAPIsRendering>(mode);
		input_context = DBG_NEW InputHandler<GraphicAPIsEvent>();
#else
		level_context = new LevelHandler<GraphicAPIsRendering>(mode);
		input_context = new InputHandler<GraphicAPIsEvent>();
#endif
		int w = level_context->getLevel()->getCols() * Tile::size;
		int h = level_context->getLevel()->getRows() * Tile::size;
		screen_callback(w, h);
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::~GameManagerImp()
	{
		delete level_context;
		level_context = nullptr;
	}

	/// <summary>
	/// Polling input events
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e)
	{
		input_context->pollEvents(e);
	}

	/// <summary>
	/// Processing inputs
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::processInputs(const int& lrm)
	{
		/// <summary>
		/// Mouse Y axis direction would be inverted depending on the graphical lib used 
		/// </summary>
		int mousePosX = 0;
		int mousePosY = 0;
		input_context->getMouseState(mousePosX, mousePosY);
		if (mousePosY - Tile::size < 0) return;																	// These offset should be equals to the
		else level_context->update((mousePosY - Tile::size) / Tile::size, mousePosX / Tile::size, lrm);			// ImGuiComponents total Heights, Replace Tile::size by getComponentHeight instead of subtracting
	}

	/// <summary>
	/// Refreshing renderer APIs context
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(GraphicAPIsRendering* renderer, const int& w, const int& h)
	{
		level_context->refresh(renderer, w, h);
	}

	/// <summary>
	/// Updating/Swapping buffers
	/// </summary>
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::draw(GraphicAPIsRendering* renderer)
	{
		level_context->draw(renderer);
	}
}