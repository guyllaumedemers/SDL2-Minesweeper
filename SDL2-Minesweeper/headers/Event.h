#pragma once

namespace Toolset {
	template<class T>
	class Event {
	private:
		void(*)(T&) callback;
		Event(const Event&) = delete;
		Event(Event&&) = delete;
	public:
		Event(void(*)(T&));
		~Event();
	};
}