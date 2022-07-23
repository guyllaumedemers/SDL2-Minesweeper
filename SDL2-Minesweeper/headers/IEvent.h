
#ifndef INCLUDED_IEVENT
#define INCLUDED_IEVENT

namespace Toolset {
	class IEvent {
	protected:
		IEvent() = default;
	public:
		IEvent(const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
		virtual ~IEvent() = 0;
		IEvent& operator=(const IEvent&) = delete;
		IEvent& operator=(IEvent&&) = delete;
	};

	inline IEvent::~IEvent()
	{}
}
#endif