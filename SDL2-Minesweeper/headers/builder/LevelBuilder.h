
#ifndef INCLUDED_LEVELBUILDER
#define INCLUDED_LEVELBUILDER

#include "IBuilder.h"

namespace Toolset {
    template<class GraphicAPIsRendering>
    class LevelBuilder : public virtual IBuilder {
        int level_width = 0, level_height = 0;
    public:
        LevelBuilder(const LevelBuilder&) = delete;
        LevelBuilder(LevelBuilder&&) = delete;
        LevelBuilder() = default;
        ~LevelBuilder() override;
        LevelBuilder& operator=(const LevelBuilder&) = delete;
        LevelBuilder& operator=(LevelBuilder&&) = delete;
        const int getLevelWidth() const     { return level_width; }
        const int getLevelHeight() const    { return level_height; }
        void setLevelWidth(const int& w)    { level_width = w; }
        void setLevelHeight(const int& h)   { level_height = h; }
        virtual void update(const int&, const int&, const int&) = 0;
        virtual void refresh(GraphicAPIsRendering*, const int&, const int&) = 0;
        virtual void draw(GraphicAPIsRendering*) = 0;
    };

    template <class GraphicAPIsRendering>
    inline LevelBuilder<GraphicAPIsRendering>::~LevelBuilder()
    {}
}
#endif