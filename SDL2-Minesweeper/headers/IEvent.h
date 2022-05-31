#pragma once

namespace Toolset {
	class IEvent {
		IEvent(const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
	protected:
		IEvent() {};
	public:
		virtual ~IEvent() = 0 {};
	};
}