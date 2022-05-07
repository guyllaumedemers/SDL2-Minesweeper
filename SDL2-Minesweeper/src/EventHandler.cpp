#pragma once
#include "../headers/EventHandler.h"

namespace Toolset {
	EventHandler::EventHandler() {}
	EventHandler::~EventHandler() { for (int i = subscribers.size() - 1; i >= 0; --i) delete subscribers[i]; }

	void EventHandler::add(Subscriber* subscriber)
	{
		subscribers.push_back(subscriber);
	}

	void EventHandler::remove(Subscriber* subscriber)
	{
		auto it = find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end()) subscribers.erase(it);
	}

	void EventHandler::invoke()
	{
		for (int i = subscribers.size() - 1; i >= 0; --i) subscribers[i]->invoke();
	}
}