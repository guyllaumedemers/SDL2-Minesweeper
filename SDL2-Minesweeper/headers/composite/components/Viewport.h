#pragma once
#include <imgui.h>
#include <imgui_internal.h>

/// <summary>
/// dev later as we currently have a single viewport inside the main window, would be useful to break down section of the screen
/// </summary>
namespace Toolset {
	class Viewport {
	private:
		ImGuiID work_id;
		ImVec2 work_pos;
		ImVec2 work_size;
		Viewport(const Viewport&) = delete;
		Viewport(Viewport&&) = delete;
		Viewport();
	public:
		Viewport(const ImVec2&, const ImVec2&, const ImGuiID&);
		~Viewport();
	};
}