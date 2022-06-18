#pragma once
#include "../../../headers/composite/components/Window.h"

#include <imgui.h>
#include <imgui_internal.h>

#ifdef _DEBUG
#include "../../../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Window::Window(const Rect& rect, const char* name, Style* window_style) : ImGuiComplexComponent(rect), ImGuiComponent(rect), name(name), window_style(window_style), p_open(true)
	{
#ifdef _DEBUG
		this->window_canvas = DBG_NEW Canvas(rect);
#else
		this->window_canvas = new Canvas(rect);
#endif
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Window::~Window()
	{
		delete window_style;
		window_style = nullptr;
		delete window_canvas;
		window_canvas = nullptr;
	}

	/// <summary>
	/// Get Canvas instance
	/// </summary>
	Canvas* Window::getWindowCanvas() const
	{
		return window_canvas;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Window::refresh()
	{
		window_style->add(ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration);
		if (window_style->getfullscreen()) {

			window_style->push(ImGuiStyleVar_WindowRounding, 0.0f);
			window_style->push(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_style->add(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			window_style->add(ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar);
		}

		if (!window_style->getpadding()) window_style->push(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		if (name != nullptr && ImGui::Begin(name, &p_open, window_style->getwindowFlags())) {
			if (!window_style->getpadding()) window_style->pop();
			if (window_style->getfullscreen()) window_style->pop(2);
			if (ImGui::BeginMenuBar()) {
				ImGuiComplexComponent::refresh();
				ImGui::EndMenuBar();
			}
			window_canvas->refresh();
			ImGui::End();
		}
	}
}