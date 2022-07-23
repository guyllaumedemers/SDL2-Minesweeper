
#ifndef INCLUDED_GAMEMANAGERIMP
#define INCLUDED_GAMEMANAGERIMP

#include "../LevelHandler.h"
#include "../InputHandler.h"

namespace Toolset {
	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	class GameManagerImp final {
		LevelHandler<GraphicAPIsRendering>* level_context = nullptr;
		InputHandler<GraphicAPIsEvent>* input_context = nullptr;
	public:
		GameManagerImp(const GameManagerImp&) = delete;
		GameManagerImp(GameManagerImp&&) = delete;
		GameManagerImp() = delete;
		GameManagerImp(IBuilder*, void(*)(const int&, const int&));
		~GameManagerImp();
		GameManagerImp& operator=(const GameManagerImp&) = delete;
		GameManagerImp& operator=(GameManagerImp&&) = delete;
		void pollEvents(GraphicAPIsEvent&);
		void processInputs(const int&);
		void refresh(GraphicAPIsRendering*, const int&, const int&);
		void draw(GraphicAPIsRendering*);
	};

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::GameManagerImp(IBuilder* level_builder, void(*screen_callback)(const int&, const int&))
	{
		level_context = new LevelHandler<GraphicAPIsRendering>(level_builder);
		input_context = new InputHandler<GraphicAPIsEvent>();

		/*int w = dynamic_cast<LevelBuilder<GraphicAPIsRendering>>(level_context->getLevel().getLevelBuilder()).getLevelWidth();
		int h = dynamic_cast<LevelBuilder<GraphicAPIsRendering>>(level_context->getLevel().getLevelBuilder()).getLevelHeight();*/
		screen_callback(0, 0);
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::~GameManagerImp()
	{
		delete level_context;
		level_context = nullptr;
		delete input_context;
		input_context = nullptr;
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(GraphicAPIsEvent& e)
	{
		input_context->pollEvents(e);
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::processInputs(const int& lrm)
	{
		/// <summary>
		/// Mouse Y axis direction would be inverted depending on the graphical lib used 
		/// </summary>
		int mousePosX = 0;
		int mousePosY = 0;
		input_context->getMouseState(mousePosX, mousePosY);																// These offset should be equals to the
		// level_context->update((mousePosY - Tile::size) / Tile::size, mousePosX / Tile::size, lrm);			// ImGuiComponents total Heights, Replace Tile::size by getComponentHeight instead of subtracting
		level_context->update(mousePosX, mousePosY, lrm);
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(GraphicAPIsRendering* renderer, const int& w, const int& h)
	{
		level_context->refresh(renderer, w, h);
	}

	template<class GraphicAPIsRendering, class GraphicAPIsEvent>
	inline void GameManagerImp<GraphicAPIsRendering, GraphicAPIsEvent>::draw(GraphicAPIsRendering* renderer)
	{
		level_context->draw(renderer);
	}
}
#endif