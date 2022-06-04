#pragma once
#include <iostream>

using namespace std;
namespace Toolset {
	class ISubscriber {
		ISubscriber(const ISubscriber&) = delete;
		ISubscriber(ISubscriber&&) = delete;
	protected:
		ISubscriber() {};
	public:
		virtual ~ISubscriber() = 0 { cout << "ISubscriber Desctructor" << endl; };
	};
}