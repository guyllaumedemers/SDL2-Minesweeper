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
	public:
		ImGuiComplexComponent();
		~ImGuiComplexComponent();
		void add(ImGuiComponent*);
		void remove(ImGuiComponent*);
		int getcomponentHeight() override;
	};
}