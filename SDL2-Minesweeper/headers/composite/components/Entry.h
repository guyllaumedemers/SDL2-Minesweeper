#pragma once
#include "../ImGuiSimpleComponent.h"
#include "../../EventHandler.h"

#include <imgui.h>
#include <imgui_internal.h>

namespace Toolset {
	template<class T>
	class Entry final : virtual public ImGuiSimpleComponent {
	private:
		T* data = nullptr;
		const char* name = nullptr;
		const char* event_key = nullptr;
	public:
		Entry(const Entry&) = delete;
		Entry(Entry&&) = delete;
		Entry() = delete;
		Entry(const Rect& rect, const char* name, const char* event_key, const T& data);
		~Entry() override;
		Entry& operator=(const Entry&) = delete;
		Entry& operator=(Entry&&) = delete;
		void refresh() override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class T>
	Entry<T>::Entry(const Rect& rect, const char* name, const char* event_key, const T& data) : ImGuiSimpleComponent(rect), ImGuiComponent(rect), name(name), event_key(event_key)
	{
		this->data = new T(data);
	}

	/// <summary>
	/// Destructor;
	/// </summary>
	template<class T>
	Entry<T>::~Entry()
	{
		delete data;
		data = nullptr;
	}

	/// <summary>
	/// Refresh ImGui
	/// </summary>
	template<class T>
	void Entry<T>::refresh()
	{
		if (name != nullptr && ImGui::MenuItem(name)) { EventHandler::invoke(event_key, *data); }
	}
}