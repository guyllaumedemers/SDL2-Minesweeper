#pragma once
#include "Rect.h"

using namespace std;
namespace Toolset {
	/// <summary>
	/// base of composite pattern
	/// </summary>
	class ImGuiComponent {
	private:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
		ImGuiComponent() = delete;
	protected:
		ImGuiComponent(Rect& rect) : rect(rect) {};
	public:
		/// <summary>
		/// Alias
		/// </summary>
		Rect& rect;
		virtual ~ImGuiComponent() = 0 {};
		virtual int getcomponentHeight() = 0;
	};
}