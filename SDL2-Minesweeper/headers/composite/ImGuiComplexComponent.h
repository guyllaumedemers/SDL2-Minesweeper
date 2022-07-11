#pragma once
#include "ImGuiComponent.h"
#include <vector>

using namespace std;
namespace Toolset {
	class ImGuiComplexComponent : virtual public ImGuiComponent {
	private:
		/// <summary>
		/// pointers are required because of the Rect composition dependency during constructor initialization stage, and the fact that all class are deleting their copy constructor, default, move
		/// </summary>
		vector<ImGuiComponent*> components = vector<ImGuiComponent*>();
	public:
		ImGuiComplexComponent(const ImGuiComplexComponent&) = delete;
		ImGuiComplexComponent(ImGuiComplexComponent&&) = delete;
		ImGuiComplexComponent() = delete;
		ImGuiComplexComponent(const Rect&);
		~ImGuiComplexComponent() override;
		ImGuiComplexComponent& operator=(const ImGuiComplexComponent&) = delete;
		ImGuiComplexComponent& operator=(ImGuiComplexComponent&&) = delete;
		void add(ImGuiComponent*);
		void remove(ImGuiComponent*);
		void refresh() override;
		int getComponentWidth() override;
		int getComponentHeight() override;
	};
}