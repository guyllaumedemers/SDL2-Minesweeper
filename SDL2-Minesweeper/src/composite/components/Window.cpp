#pragma once
#include "../../../headers/composite/components/Window.h"

namespace Toolset {
	/// <summary>
	/// Constructor
	/// </summary>
	Window::Window(const Rect& rect, const char* name, Style* window_style) : ImGuiComplexComponent(rect), ImGuiComponent(rect), name(name), window_style(window_style)
	{
		this->p_open = true;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Window::~Window()
	{
		delete window_style;
		window_style = nullptr;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Window::refresh()
	{
		static float rounding_val = 0.0f;
		static float border_val = 0.0f;
		window_style->add(ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking);
		if (window_style->getfullscreen()) {

			const ImGuiViewport* viewport = ImGui::GetMainViewport();
			ImGui::SetNextWindowPos(viewport->WorkPos);
			ImGui::SetNextWindowSize(viewport->WorkSize);
			ImGui::SetNextWindowViewport(viewport->ID);
			window_style->push(ImGuiStyleVar_WindowRounding, (void*)&rounding_val);
			window_style->push(ImGuiStyleVar_WindowBorderSize, (void*)&border_val);
			window_style->add(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			window_style->add(ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar);
		}

		if (!window_style->getpadding()) ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		if (ImGui::Begin(name, &p_open, window_style->getwindowFlags())) {
			if (!window_style->getpadding()) window_style->pop();
			if (window_style->getfullscreen()) window_style->pop(2);
			if (ImGui::BeginMenuBar()) {
				ImGuiComplexComponent::refresh();
				ImGui::EndMenuBar();
			}
			ImGui::End();
		}
	}
}