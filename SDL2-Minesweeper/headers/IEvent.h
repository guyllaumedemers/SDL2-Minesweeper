#pragma once

namespace Toolset {
	/// <summary>
	/// base class for observer pattern, use to work around generic implementation in its derived child
	/// </summary>
	class IEvent {
	protected:
		IEvent() = default;
	public:
		IEvent(const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
		virtual ~IEvent() = 0 {};
		IEvent& operator=(const IEvent&) = delete;
		IEvent& operator=(IEvent&&) = delete;
	};
}