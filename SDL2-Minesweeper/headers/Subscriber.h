#pragma once
#include "EventHandler.h"

using namespace std;
namespace Toolset {
	/// <summary>
	/// forward declaration
	/// </summary>
	class EventHandler;

	class Subscriber {
	private:
		void(*action)() = nullptr;
		EventHandler* subject = nullptr;
		Subscriber() = delete;
		Subscriber(const Subscriber&) = delete;
		Subscriber(Subscriber&&) = delete;
	public:
		Subscriber(EventHandler*, void(*)());
		~Subscriber();
		void invoke();
	};
}