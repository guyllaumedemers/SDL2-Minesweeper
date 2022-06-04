#pragma once
#include <iostream>

using namespace std;
namespace Toolset {
	class IBuilder {
	private:
		IBuilder(const IBuilder&) = delete;
		IBuilder(IBuilder&&) = delete;
	protected:
		IBuilder() {};
	public:
		virtual ~IBuilder() = 0 { cout << "IEvent Desctructor" << endl; }
	};
}