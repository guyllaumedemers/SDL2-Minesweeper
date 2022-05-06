#include "../../headers/imgui/TopMenuBarImp.h"
#include <imgui_single_file.h>

namespace GraphicalToolset {
	TopMenuBarImp::TopMenuBarImp() {}
	TopMenuBarImp::~TopMenuBarImp() {}

	void TopMenuBarImp::refresh()
	{
		bool my_tool_active = true;
		ImGui::Begin("My First Tool", &my_tool_active, ImGuiWindowFlags_MenuBar);
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Open..", "Ctrl+O")) { /* Do stuff */ }
				if (ImGui::MenuItem("Save", "Ctrl+S")) { /* Do stuff */ }
				if (ImGui::MenuItem("Close", "Ctrl+W")) { my_tool_active = false; }
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::End();
		if (!my_tool_active) {/*Trigger Event Callback*/ }
	}
}
