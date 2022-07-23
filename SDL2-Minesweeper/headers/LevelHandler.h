
#ifndef INCLUDED_LEVELHANDLER
#define INCLUDED_LEVELHANDLER

#include "bridge/LevelHandlerImp.h"
#include "bridge/LevelHandlerImpSDL.h"

namespace Toolset {
	template<class GraphicAPIsRendering>
	class LevelHandler {
		LevelHandlerImp<GraphicAPIsRendering>* level_imp = nullptr;
	public:
		LevelHandler(const LevelHandler&) = delete;
		LevelHandler(LevelHandler&&) = delete;
		LevelHandler() = delete;
		LevelHandler(IBuilder*);
		~LevelHandler();
		LevelHandler& operator=(const LevelHandler&) = delete;
		LevelHandler& operator=(LevelHandler&&) = delete;
		const LevelHandlerImp<GraphicAPIsRendering>& getLevel() const { return *level_imp; }
		void update(const int&, const int&, const int&);
		void refresh(GraphicAPIsRendering*, const int&, const int&);
		void draw(GraphicAPIsRendering*);
	};

	template<class GraphicAPIsRendering>
	inline LevelHandler<GraphicAPIsRendering>::LevelHandler(IBuilder* builder_context)
	{
		if (std::is_same_v<GraphicAPIsRendering, SDL_Event>)
			level_imp = new LevelHandlerImpSDL<GraphicAPIsRendering>(builder_context);
	}

	template<class GraphicAPIsRendering>
	inline LevelHandler<GraphicAPIsRendering>::~LevelHandler()
	{
		delete level_imp;
		level_imp = nullptr;
	}

	template<class GraphicAPIsRendering>
	inline void LevelHandler<GraphicAPIsRendering>::update(const int& mpx, const int& mpy, const int& lrm)
	{
		level_imp->update(mpx, mpy, lrm);
	}

	template<class GraphicAPIsRendering>
	inline void LevelHandler<GraphicAPIsRendering>::refresh(GraphicAPIsRendering* renderer, const int& w, const int& h)
	{
		level_imp->refresh(renderer, w, h);
	}

	template<class GraphicAPIsRendering>
	inline void LevelHandler<GraphicAPIsRendering>::draw(GraphicAPIsRendering* renderer)
	{
		level_imp->draw(renderer);
	}
}
#endif