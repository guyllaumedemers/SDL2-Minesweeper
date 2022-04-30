#pragma once
#include <vector>
#include "Subscriber.h"

using namespace std;
namespace Minesweeper {
	class EventHandler {
	private:
		vector<Subscriber> subscribers;
		EventHandler(const EventHandler&) = delete;
		EventHandler(EventHandler&&) = delete;
	public:
		EventHandler();
		~EventHandler();
		void add(Subscriber&);
		void remove(Subscriber&);
		void invoke();
	};
}