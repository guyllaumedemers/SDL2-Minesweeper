#pragma once
#include "../ImGuiComplexComponent.h"

namespace Toolset {
	class Tab : virtual public ImGuiComplexComponent {
	private:
		const char* name = nullptr;
		Tab(const Tab&) = delete;
		Tab(Tab&&) = delete;
		Tab() = delete;
	public:
		Tab(const Rect&, const char*);
		~Tab();
		void refresh() override;
	};

	/// <summary>
	/// Constructor overload
	/// </summary>
	Tab::Tab(const Rect& rect, const char* name) : ImGuiComplexComponent(rect), ImGuiComponent(rect)
	{
		this->name = name;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	Tab::~Tab()
	{
		delete name;
		name = nullptr;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void Tab::refresh()
	{
		if (ImGui::BeginMenu(name)) {
			ImGuiComplexComponent::refresh();
			ImGui::EndMenu();
		}
	}
}