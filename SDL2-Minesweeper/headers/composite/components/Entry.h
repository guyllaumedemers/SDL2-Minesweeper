
#ifndef INCLUDED_ENTRY
#define INCLUDED_ENTRY

#include "../ImGuiSimpleComponent.h"
#include "../../EventHandler.h"
#include <imgui.h>

namespace Toolset {
	template<class T>
	class Entry final : virtual public ImGuiSimpleComponent {
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

	template<class T>
	inline Entry<T>::Entry(const Rect& rect, const char* name, const char* event_key, const T& data) : ImGuiSimpleComponent(rect), ImGuiComponent(rect),
		data(new T(data)),
		name(name),
		event_key(event_key)
	{}

	template<class T>
	inline Entry<T>::~Entry()
	{
		delete data;
		data = nullptr;
	}

	template<class T>
	inline void Entry<T>::refresh()
	{
		if (name != nullptr && ImGui::MenuItem(name)) { EventHandler::invoke(event_key, *data); }
	}
}
#endif