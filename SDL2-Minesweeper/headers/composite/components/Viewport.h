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
	public:
		Viewport(const Viewport&) = delete;
		Viewport(Viewport&&) = delete;
		Viewport() = delete;
		Viewport(const Rect&);
		~Viewport();
		Viewport& operator=(const Viewport&) = delete;
		Viewport& operator=(Viewport&&) = delete;
		void setTextureViewport(const ImTextureID&, const ImGuiID&);
		void refresh();
	};
}