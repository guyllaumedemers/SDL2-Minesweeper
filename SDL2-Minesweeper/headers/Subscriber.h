#pragma once
#include "EventHandler.h"

/// <summary>
/// Currently unsure of how I want this Observer Setup to behave. Do I want composition, inheritance and how would I implement different invoke callback if a class register to more than 1x event?
/// </summary>
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