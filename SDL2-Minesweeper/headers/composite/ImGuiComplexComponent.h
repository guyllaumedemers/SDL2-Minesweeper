#pragma once
#include "ImGuiComponent.h"
#include <vector>

using namespace std;
namespace Toolset {
	class ImGuiComplexComponent : virtual public ImGuiComponent {
	private:
		vector<ImGuiComponent*> components;
		ImGuiComplexComponent(const ImGuiComplexComponent&) = delete;
		ImGuiComplexComponent(ImGuiComplexComponent&&) = delete;
		ImGuiComplexComponent() = delete;
	protected:
		ImGuiComplexComponent(Rect& rect) : ImGuiComponent(rect) { };
	public:
		virtual ~ImGuiComplexComponent() = 0
		{
			for (auto& it : components) {
				delete it;
				it = nullptr;
			}
		};
		void add(ImGuiComponent*);
		void remove(ImGuiComponent*);
		int getcomponentHeight() override;
	};

	void ImGuiComplexComponent::add(ImGuiComponent* component)
	{
		this->components.push_back(component);
	}

	void ImGuiComplexComponent::remove(ImGuiComponent* component)
	{
		vector<ImGuiComponent*>::iterator it = find(components.begin(), components.end(), component);
		if (it != components.end()) components.erase(it);
	}

	int ImGuiComplexComponent::getcomponentHeight()
	{
		int result = 0;
		for (const auto& it : components) result += it->rect.h;
		return result;
	}
}