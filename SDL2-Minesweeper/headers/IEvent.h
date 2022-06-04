#pragma once
#include <iostream>

using namespace std;
namespace Toolset {
	class IEvent {
		IEvent(const IEvent&) = delete;
		IEvent(IEvent&&) = delete;
	protected:
		IEvent() {};
	public:
		virtual ~IEvent() = 0 { cout << "IEvent Desctructor" << endl; };
	};
}