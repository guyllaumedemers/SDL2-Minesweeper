
#ifndef INCLUDED_LEVELHANDLERIMPSDL
#define INCLUDED_LEVELHANDLERIMPSDL

#include "LevelHandlerImp.h"
#include "../builder/IBuilder.h"
#include "../builder/LevelBuilder.h"

namespace Toolset {
	template<class GraphicAPIsRendering>
	class LevelHandlerImpSDL final : public virtual LevelHandlerImp<GraphicAPIsRendering> {
	public:
		LevelHandlerImpSDL(const LevelHandlerImpSDL&) = delete;
		LevelHandlerImpSDL(LevelHandlerImpSDL&&) = delete;
		LevelHandlerImpSDL() = delete;
		explicit LevelHandlerImpSDL(IBuilder*);
		~LevelHandlerImpSDL() override;
		LevelHandlerImpSDL& operator=(const LevelHandlerImpSDL&) = delete;
		LevelHandlerImpSDL& operator=(LevelHandlerImpSDL&&) = delete;
		void update(const int&, const int&, const int&) override;
		void refresh(GraphicAPIsRendering*, const int&, const int&) override;
		void draw(GraphicAPIsRendering*) override;
	};

	template <class GraphicAPIsRendering>
	inline LevelHandlerImpSDL<GraphicAPIsRendering>::LevelHandlerImpSDL(IBuilder* builder_context) : LevelHandlerImp<GraphicAPIsRendering>(builder_context)
	{}

	template <class GraphicAPIsRendering>
	inline LevelHandlerImpSDL<GraphicAPIsRendering>::~LevelHandlerImpSDL()
	{}

	template <class GraphicAPIsRendering>
	inline void LevelHandlerImpSDL<GraphicAPIsRendering>::update(const int& mpx, const int& mpy, const int& lrm)
	{
		dynamic_cast<LevelBuilder*>(this->getLevelBuilder())->update(mpx, mpy, lrm);
	}

	template <class GraphicAPIsRendering>
	inline void LevelHandlerImpSDL<GraphicAPIsRendering>::refresh(GraphicAPIsRendering* renderer, const int& w, const int& h)
	{
		dynamic_cast<LevelBuilder*>(this->getLevelBuilder())->refresh(renderer, w, h);
	}

	template <class GraphicAPIsRendering>
	inline void LevelHandlerImpSDL<GraphicAPIsRendering>::draw(GraphicAPIsRendering* renderer)
	{
		dynamic_cast<LevelBuilder*>(this->getLevelBuilder())->draw(renderer);
	}
}
#endif