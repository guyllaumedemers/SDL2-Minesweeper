#pragma once
#include <vector>

using namespace std;
namespace Toolset {
	/// <summary>
	/// base of composite pattern
	/// </summary>
	class ImGuiComponent {
	private:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
	protected:
		ImGuiComponent() {};
	public:
		/// <summary>
		/// unsafe but cannot access via pointer in protected
		/// </summary>
		int component_height = 0;
		virtual ~ImGuiComponent() = 0 {};
		virtual int getcomponentHeight() = 0;
	};
}