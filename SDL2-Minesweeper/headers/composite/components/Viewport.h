#pragma once
#include "../Rect.h"
#include "Image.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	class Viewport {
	private:
		ImVec2 work_pos = ImVec2();
		ImVec2 work_size = ImVec2();
		Image* viewport_texture = nullptr;
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