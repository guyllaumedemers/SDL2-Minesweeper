#pragma once
#include "ImGuiComponent.h"
#include <vector>

using namespace std;
namespace Toolset {
	class ImGuiComplexComponent : virtual public ImGuiComponent {
	private:
		/// <summary>
		/// pointers are required because of the Rect composition dependency during constructor initialization stage
		/// </summary>
		vector<ImGuiComponent*> components;
		ImGuiComplexComponent(const ImGuiComplexComponent&) = delete;
		ImGuiComplexComponent(ImGuiComplexComponent&&) = delete;
		ImGuiComplexComponent() = delete;
	public:
		ImGuiComplexComponent(const Rect&);
		~ImGuiComplexComponent();
		void add(ImGuiComponent*);
		void remove(ImGuiComponent*);
		virtual void refresh() override;
		int getComponentHeight() override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	ImGuiComplexComponent::ImGuiComplexComponent(const Rect& rect) : ImGuiComponent(rect)
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	ImGuiComplexComponent::~ImGuiComplexComponent()
	{
		for (auto& it : components) {
			delete it;
			it = nullptr;
		}
		components.clear();
	}

	/// <summary>
	/// Adding component to pool
	/// </summary>
	void ImGuiComplexComponent::add(ImGuiComponent* component)
	{
		this->components.push_back(component);
	}

	/// <summary>
	/// Removing component to pool
	/// </summary>
	void ImGuiComplexComponent::remove(ImGuiComponent* component)
	{
		vector<ImGuiComponent*>::iterator it = find(components.begin(), components.end(), component);
		if (it != components.end()) components.erase(it);
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	void ImGuiComplexComponent::refresh()
	{
		for (const auto& it : components) it->refresh();
	}

	/// <summary>
	/// Get total components height
	/// </summary>
	int ImGuiComplexComponent::getComponentHeight()
	{
		int result = 0;
		for (const auto& it : components) result += it->getRect().h;
		return result;
	}
}