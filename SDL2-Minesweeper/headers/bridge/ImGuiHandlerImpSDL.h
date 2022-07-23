/*
 *	Why use final? https://en.cppreference.com/w/cpp/language/final
 *
 */

#ifndef INCLUDED_IMGUIHANDLERIMPSDL
#define INCLUDED_IMGUIHANDLERIMPSDL

#include "ImGuiHandlerImp.h"
#include "../SDLHandler.h"
#include "../builder/ImGuiMinesweeperBuilder.h"     //Shouldn't be part of this as the ref is specific to this project
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

namespace Toolset {
    template <class GraphicAPIsRendering, class GraphicAPIsEvent>
    class ImGuiHandlerImpSDL final : virtual public ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent> {
        IBuilder* imgui_builder_context = nullptr;
        SDLHandler* sdl_context = nullptr;
    public:
        ImGuiHandlerImpSDL(const ImGuiHandlerImpSDL&) = delete;
        ImGuiHandlerImpSDL(ImGuiHandlerImpSDL&&) = delete;
        ImGuiHandlerImpSDL() = delete;
        ImGuiHandlerImpSDL(IBuilder*, SDLHandler* sdl_context);
        ~ImGuiHandlerImpSDL() override;
        ImGuiHandlerImpSDL& operator=(const ImGuiHandlerImpSDL&) = delete;
        ImGuiHandlerImpSDL& operator=(ImGuiHandlerImpSDL&&) = delete;
        int pollEvents(void (*)(GraphicAPIsEvent&)) override;
        void refresh(void (*)(GraphicAPIsRendering*)) override;
        void draw(void (*)(GraphicAPIsRendering*)) override;
    };

    template <class GraphicAPIsRendering, class GraphicAPIsEvent>
    inline ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::ImGuiHandlerImpSDL(IBuilder* builder_context, SDLHandler* sdl_context) : ImGuiHandlerImp<GraphicAPIsRendering, GraphicAPIsEvent>(),
        imgui_builder_context(builder_context),
        sdl_context(sdl_context)
    {
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGui::StyleColorsDark();
        ImGui_ImplSDL2_InitForSDLRenderer(sdl_context->getWindow(), sdl_context->getRenderer());
        ImGui_ImplSDLRenderer_Init(sdl_context->getRenderer());
    }

    template <class GraphicAPIsRendering, class GraphicAPIsEvent>
    inline ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::~ImGuiHandlerImpSDL()
    {
        ImGui_ImplSDLRenderer_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();
        delete imgui_builder_context;
        imgui_builder_context = nullptr;
        delete sdl_context;
        sdl_context = nullptr;
    }

    template <class GraphicAPIsRendering, class GraphicAPIsEvent>
    inline int ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::pollEvents(void (*inputs_callback)(GraphicAPIsEvent&))
    {
        SDL_Event e;
        if (SDL_WaitEvent(&e) > 0)
        {
            if (ImGui_ImplSDL2_ProcessEvent(&e) && ImGui::IsAnyItemHovered()) return 1;
            inputs_callback(e);
            return 1;
        }
        return 0;
    }

    template <class GraphicAPIsRendering, class GraphicAPIsEvent>
    inline void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::refresh(void (*refresh_callback)(GraphicAPIsRendering*))
    {
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();
        dynamic_cast<Minesweeper::ImGuiMinesweeperBuilder<SDLHandler>*>(imgui_builder_context)->build(sdl_context);   //How do we make this dynamic_cast not explicitly downcast to a project specific derived class
        ImGui::Render();
        sdl_context->refresh(refresh_callback);
    }

    template <class GraphicAPIsRendering, class GraphicAPIsEvent>
    inline void ImGuiHandlerImpSDL<GraphicAPIsRendering, GraphicAPIsEvent>::draw(void (*draw_callback)(GraphicAPIsRendering*))
    {
        ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());
        sdl_context->draw(draw_callback);
    }
}
#endif