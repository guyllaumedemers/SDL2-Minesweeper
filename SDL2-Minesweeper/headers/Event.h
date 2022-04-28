#pragma once
#include <vector>
#include <function>
#include "Subscriber.h"

using namespace std;
namespace Minesweeper {
	class EventHandler {
	private:
		vector<Subscriber> subscribers;
		EventHandler() = delete;
		EventHandler(const EventHandler&) = delete;
		EventHandler(EventHandler&&) = delete;
	public:
		EventHandler();
		~EventHandler();
		void add(Subscriber&);
		void remove(Subscriber&);
		void Invoke();
	};
}