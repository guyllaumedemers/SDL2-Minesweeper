#pragma once
#include "../../../headers/composite/components/Style.h"

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
	/// return window_flags
	/// </summary>
	/// <returns></returns>
	const ImGuiWindowFlags& Style::getwindowFlags() const
	{
		return window_flags;
	}
}