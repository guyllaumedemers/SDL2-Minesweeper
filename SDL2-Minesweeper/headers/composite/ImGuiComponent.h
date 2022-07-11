#pragma once
#include "Rect.h"

/*
 *	Benefits of explicitly defaulted and deleted functions
 *	https://docs.microsoft.com/en-us/cpp/cpp/explicitly-defaulted-and-deleted-functions?view=msvc-170
 *
 */

using namespace std;
namespace Toolset {
	/// <summary>
	/// base of composite pattern
	/// </summary>
	class ImGuiComponent {
	protected:
		Rect* rect = nullptr;
		ImGuiComponent(const Rect&);
	public:
		ImGuiComponent(const ImGuiComponent&) = delete;
		ImGuiComponent(ImGuiComponent&&) = delete;
		ImGuiComponent() = delete;
		/// <summary>
		/// See .cpp for destructor imp
		/// </summary>
		virtual ~ImGuiComponent() = 0;
		ImGuiComponent& operator=(const ImGuiComponent&) = delete;
		ImGuiComponent& operator=(ImGuiComponent&&) = delete;
		virtual void refresh() = 0;
		virtual int getComponentWidth() = 0;
		virtual int getComponentHeight() = 0;
		const Rect& getRect() const;
	};
}