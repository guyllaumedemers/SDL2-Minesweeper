#include "../../../headers/composite/components/Window.h"
#include <imgui.h>

namespace Toolset {
	void Window::refresh()
	{
		window_style->add(ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoScrollWithMouse);
		if (window_style->getFullscreen()) {

			window_style->push(ImGuiStyleVar_WindowRounding, 0.0f);
			window_style->push(ImGuiStyleVar_WindowBorderSize, 0.0f);
			window_style->add(ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove);
			window_style->add(ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus | ImGuiWindowFlags_NoScrollbar);
		}

		if (!window_style->getPadding()) window_style->push(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

		if (name != nullptr && ImGui::Begin(name, &p_open, window_style->getWindowFlags())) {
			if (!window_style->getPadding()) window_style->pop();
			if (window_style->getFullscreen()) window_style->pop(2);
			if (ImGui::BeginMenuBar()) {
				ImGuiComplexComponent::refresh();
				ImGui::EndMenuBar();
			}
			window_canvas->refresh();
			ImGui::End();
		}
	}
}