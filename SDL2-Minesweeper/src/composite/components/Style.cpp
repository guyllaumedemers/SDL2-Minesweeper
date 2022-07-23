#include "../../../headers/composite/components/Style.h"

namespace Toolset {
	void Style::add(const ImGuiWindowFlags& imgui_window_flag)
	{
		window_flags |= imgui_window_flag;
	}

	void Style::remove(const ImGuiWindowFlags& imgui_window_flag)
	{
		window_flags &= ~imgui_window_flag;
	}

	void Style::push(const ImGuiStyleVar& imgui_style_var, const float& val)
	{
		ImGui::PushStyleVar(imgui_style_var, val);
	}

	void Style::push(const ImGuiStyleVar& imgui_style_var, const ImVec2& val)
	{
		ImGui::PushStyleVar(imgui_style_var, val);
	}

	void Style::pop(const int& val)
	{
		ImGui::PopStyleVar(val);
	}
}