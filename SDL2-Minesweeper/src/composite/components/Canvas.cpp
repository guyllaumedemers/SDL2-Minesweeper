#pragma once
#include "../../../headers/composite/components/Canvas.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Canvas::Canvas(const Rect& rect) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
#ifdef _DEBUG
		this->canvas_viewport = DBG_NEW Viewport(rect);
#else
		this->canvas_viewport = new Viewport(rect);
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Canvas::~Canvas()
	{
		delete canvas_viewport;
		canvas_viewport = nullptr;
	}

	/// <summary>
	/// return the viewport instance
	/// </summary>
	Viewport* Canvas::getCanvasViewport() const
	{
		return canvas_viewport;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Canvas::refresh()
	{
		/// <summary>
		/// We might not want a viewport, lets say we display a texture that fills the canvas, no background is required in that case
		/// </summary>
		if (canvas_viewport) canvas_viewport->refresh();
		ImGuiComplexComponent::refresh();
	}
}