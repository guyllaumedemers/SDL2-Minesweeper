
#ifndef INCLUDED_ISUBSCRIBER
#define INCLUDED_ISUBSCRIBER

namespace Toolset {
	class ISubscriber {
	protected:
		ISubscriber() = default;
	public:
		ISubscriber(const ISubscriber&) = delete;
		ISubscriber(ISubscriber&&) = delete;
		virtual ~ISubscriber() = 0;
		ISubscriber& operator=(const ISubscriber&) = delete;
		ISubscriber& operator=(ISubscriber&&) = delete;
	};
	
	inline ISubscriber::~ISubscriber()
	{}
}
#endif