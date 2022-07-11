#pragma once

using namespace std;
namespace Toolset {
	/// <summary>
	/// base class for observer pattern, use to work around generic implementation in its derived child
	/// </summary>
	class ISubscriber {
	protected:
		ISubscriber() = default;
	public:
		ISubscriber(const ISubscriber&) = delete;
		ISubscriber(ISubscriber&&) = delete;
		virtual ~ISubscriber() = 0 {};
		ISubscriber& operator=(const ISubscriber&) = delete;
		ISubscriber& operator=(ISubscriber&&) = delete;
	};
}