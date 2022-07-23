#ifndef INCLUDED_IMGUIBUILDER
#define INCLUDED_IMGUIBUILDER

#include "IBuilder.h"
#include "../composite/ImGuiComplexComponent.h"

namespace Toolset {
    template <class GraphicAPIsContext>
    class ImGuiBuilder : virtual public IBuilder {
		ImGuiComplexComponent* builder_parts = nullptr;
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
        ImGuiComplexComponent* getBuilderParts() const                  { return builder_parts; }
        void setBuilderParts(ImGuiComplexComponent* builder_parts)      { this->builder_parts = builder_parts; }
        virtual int getMaxWidth()                                       { return 0; }
        virtual int getMaxHeight()                                      { return 0; }
        virtual void reset() {}
    };

    template <class GraphicAPIsContext>
    ImGuiBuilder<GraphicAPIsContext>::~ImGuiBuilder()
    {
        delete builder_parts;
        builder_parts = nullptr;
    }
}
#endif
