
#ifndef INCLUDED_IMGUICOMPLEXCOMPONENT
#define INCLUDED_IMGUICOMPLEXCOMPONENT

#include "ImGuiComponent.h"
#include <vector>

namespace Toolset {
	class ImGuiComplexComponent : virtual public ImGuiComponent {
		std::vector<ImGuiComponent*> components;
	protected:
		explicit ImGuiComplexComponent(const Rect&);
	public:
		ImGuiComplexComponent(const ImGuiComplexComponent&) = delete;
		ImGuiComplexComponent(ImGuiComplexComponent&&) = delete;
		ImGuiComplexComponent() = delete;
		~ImGuiComplexComponent() override;
		ImGuiComplexComponent& operator=(const ImGuiComplexComponent&) = delete;
		ImGuiComplexComponent& operator=(ImGuiComplexComponent&&) = delete;
		float getComponentWidth() override;
		float getComponentHeight() override;
		void add(ImGuiComponent*);
		void remove(ImGuiComponent*);
		void refresh() override;
	};
	
	inline ImGuiComplexComponent::ImGuiComplexComponent(const Rect& rect) : ImGuiComponent(rect),
		components(std::vector<ImGuiComponent*>())
	{}

	inline ImGuiComplexComponent::~ImGuiComplexComponent()
	{
		for (auto& it : components) {
			delete it;
			it = nullptr;
		}
		components.clear();
	}
}
#endif