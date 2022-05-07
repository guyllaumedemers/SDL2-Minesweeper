#pragma once
#include <vector>
#include "Subscriber.h"

using namespace std;
namespace Toolset {
	/// <summary>
	/// forward declaration
	/// </summary>
	class Subscriber;

	class EventHandler {
	private:
		vector<Subscriber*> subscribers;
		EventHandler(const EventHandler&) = delete;
		EventHandler(EventHandler&&) = delete;
	public:
		EventHandler();
		~EventHandler();
		void add(Subscriber*);
		void remove(Subscriber*);
		void invoke();
	};
}