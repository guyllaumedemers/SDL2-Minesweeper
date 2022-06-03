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
}