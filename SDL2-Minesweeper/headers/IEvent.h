#pragma once
#include <iostream>

using namespace std;
namespace Toolset {
	/// <summary>
	/// base class for observer pattern, use to work around generic implementation in its derived child
	/// </summary>
	class IEvent {
		IEvent(const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
	protected:
		IEvent() = default;
	public:
		virtual ~IEvent() = 0 { cout << "IEvent Desctructor" << endl; };
	};
}