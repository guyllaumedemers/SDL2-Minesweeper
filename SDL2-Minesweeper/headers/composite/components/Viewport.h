#pragma once
#include "../Rect.h"
#include "Image.h"
#include <imgui.h>
#include <imgui_internal.h>

/// <summary>
/// dev later as we currently have a single viewport inside the main window, would be useful to break down section of the screen
/// </summary>
namespace Toolset {
	class Viewport {
	private:
		ImVec2 work_pos;
		ImVec2 work_size;
		Image* texture_viewport = nullptr;
		Viewport(const Viewport&) = delete;
		Viewport(Viewport&&) = delete;
		Viewport() = delete;
	public:
		Viewport(const Rect&);
		~Viewport();
		void setTextureViewport(const ImTextureID&, const ImGuiID&);
		void refresh();
	};
}