#pragma once
#include "../../../headers/composite/components/Style.h"
#include <typeinfo>

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Style::Style(const ImGuiWindowFlags& window_flags, const bool& opt_fullscreen, const bool& opt_padding) : window_flags(window_flags), opt_fullscreen(opt_fullscreen), opt_padding(opt_padding)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Style::~Style()
	{
	}

	/// <summary>
	/// add style to bitmask
	/// </summary>
	void Style::add(const ImGuiWindowFlags& imgui_window_flag)
	{
		window_flags |= imgui_window_flag;
	}

	/// <summary>
	/// remove style from bitmask
	/// </summary>
	void Style::remove(const ImGuiWindowFlags& imgui_window_flag)
	{
		window_flags &= ~imgui_window_flag;
	}

	/// <summary>
	/// get window fullscreen opt
	/// </summary>
	bool Style::getfullscreen()
	{
		return opt_fullscreen;
	}

	/// <summary>
	/// get window padding opt
	/// </summary>
	bool Style::getpadding()
	{
		return opt_padding;
	}

	/// <summary>
	/// push style variable
	/// </summary>
	void Style::push(const ImGuiStyleVar& imgui_style_var, const float& val)
	{
		ImGui::PushStyleVar(imgui_style_var, val);
	}

	/// <summary>
	/// push style variable overload
	/// </summary>
	void Style::push(const ImGuiStyleVar& imgui_style_var, const ImVec2& val)
	{
		ImGui::PushStyleVar(imgui_style_var, val);
	}

	/// <summary>
	/// pop style variable
	/// </summary>
	void Style::pop(const int& val)
	{
		ImGui::PopStyleVar(val);
	}

	/// <summary>
	/// return window_flags
	/// </summary>
	/// <returns></returns>
	const ImGuiWindowFlags& Style::getwindowFlags() const
	{
		return window_flags;
	}
}