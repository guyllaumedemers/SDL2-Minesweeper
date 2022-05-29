#pragma once

namespace Toolset {
	class ISubscriber {
		ISubscriber(const ISubscriber&) = delete;
		ISubscriber(ISubscriber&&) = delete;
	protected:
		ISubscriber() {};
	public:
		virtual ~ISubscriber() = 0 {};
	};
}