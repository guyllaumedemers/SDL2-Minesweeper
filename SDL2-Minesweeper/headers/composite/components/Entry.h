#pragma once
#include "../ImGuiSimpleComponent.h"
#include "../../EventHandler.h"
#include <imgui.h>
#include <imgui_internal.h>

#ifdef _DEBUG
#include "../../CRTMemoryLeak.h"
#endif

using namespace std;
namespace Toolset {
	template<class T>
	class Entry : virtual public ImGuiSimpleComponent {
	private:
		T* data = nullptr;
		const char* name = nullptr;
		const char* event_key = nullptr;
		Entry(const Entry&) = delete;
		Entry(Entry&&) = delete;
		Entry() = delete;
	public:
		Entry(const Rect& rect, const char* name, const char* event_key, const T& data);
		~Entry();
		void refresh() override;
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class T>
	Entry<T>::Entry(const Rect& rect, const char* name, const char* event_key, const T& data) : ImGuiSimpleComponent(rect), ImGuiComponent(rect)
	{
		this->name = name;
		this->event_key = event_key;
#ifdef _DEBUG
		this->data = DBG_NEW T(data);
#else
		this->data = new T(data);
#endif
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
		if (ImGui::MenuItem(name)) { EventHandler::invoke(event_key, *data); }
	}
}