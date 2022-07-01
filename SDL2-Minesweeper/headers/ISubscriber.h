#pragma once
#include <iostream>

using namespace std;
namespace Toolset {
	/// <summary>
	/// base class for observer pattern, use to work around generic implementation in its derived child
	/// </summary>
	class ISubscriber {
		ISubscriber(const ISubscriber&) = delete;
		ISubscriber(ISubscriber&&) = delete;
	protected:
		ISubscriber() {};
	public:
		virtual ~ISubscriber() = 0 { cout << "ISubscriber Desctructor" << endl; };
	};
}