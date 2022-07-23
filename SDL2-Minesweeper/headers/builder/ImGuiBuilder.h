#ifndef INCLUDED_IMGUIBUILDER
#define INCLUDED_IMGUIBUILDER

#include "IBuilder.h"

namespace Toolset {
    template <class GraphicAPIsContext>
    class ImGuiBuilder : virtual public IBuilder {
    protected:
        ImGuiBuilder() = default;
        virtual void buildApplicationMenu() = 0;
        virtual void buildCanvas() = 0;
        virtual void buildViewport(GraphicAPIsContext*) = 0;
    public:
        ImGuiBuilder(const ImGuiBuilder&) = delete;
        ImGuiBuilder(ImGuiBuilder&&) = delete;
        ~ImGuiBuilder() override;
        ImGuiBuilder& operator=(const ImGuiBuilder&) = delete;
        ImGuiBuilder& operator=(ImGuiBuilder&&) = delete;
        virtual void build(GraphicAPIsContext*) = 0;
        inline virtual int getMaxWidth()    { return 0; }
        inline virtual int getMaxHeight()   { return 0; }
        inline virtual void reset() {}
    };

    template <class GraphicAPIsContext>
    ImGuiBuilder<GraphicAPIsContext>::~ImGuiBuilder()
    {}
}
#endif
