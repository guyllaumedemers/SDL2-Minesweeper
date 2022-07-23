
#ifndef INCLUDED_LEVELHANDLERIMP
#define INCLUDED_LEVELHANDLERIMP

namespace Toolset {
	template<class GraphicAPIsRendering>
    class LevelHandlerImp {
		IBuilder* level_builder_context = nullptr;
    public:
        LevelHandlerImp(const LevelHandlerImp&) = delete;
        LevelHandlerImp(LevelHandlerImp&&) = delete;
        LevelHandlerImp() = delete;
		explicit LevelHandlerImp(IBuilder*);
	    virtual ~LevelHandlerImp() = 0;
	    LevelHandlerImp& operator=(const LevelHandlerImp&) = delete;
	    LevelHandlerImp& operator=(LevelHandlerImp&&) = delete;
		IBuilder* getLevelBuilder() const { return level_builder_context; }
        virtual void update(const int&, const int&, const int&) = 0;
        virtual void refresh(GraphicAPIsRendering*, const int&, const int&) = 0;
        virtual void draw(GraphicAPIsRendering*) = 0;
    };


	template <class GraphicAPIsRendering>
	inline LevelHandlerImp<GraphicAPIsRendering>::LevelHandlerImp(IBuilder* builder_context) : level_builder_context(builder_context)
	{}

	template<class GraphicAPIsRendering>
	inline LevelHandlerImp<GraphicAPIsRendering>::~LevelHandlerImp()
	{
		delete level_builder_context;
		level_builder_context = nullptr;
	}
}
#endif
