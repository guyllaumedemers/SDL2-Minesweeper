#pragma once
#include "Rect.h"
#include <imgui.h>
#include <imgui_internal.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>

#ifdef _DEBUG
#include "../CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
	/// <summary>
	/// base of composite pattern
	/// </summary>
	class ImGuiComponent {
	private:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
		ImGuiComponent() = delete;
	protected:
		Rect* rect;
		ImGuiComponent(const Rect&);
	public:
		virtual ~ImGuiComponent() = 0;
		virtual void refresh() = 0;
		virtual int getComponentHeight() = 0;
		const Rect& getRect() const;
	};
}