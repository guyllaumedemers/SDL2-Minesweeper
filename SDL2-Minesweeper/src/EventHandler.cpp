#include "../headers/EventHandler.h"

namespace Toolset {
	void EventHandler::create(std::string key, IEvent* _event)
	{
		if (pool_event.find(key) == pool_event.end()) pool_event.insert({ key, _event });
	}

	void EventHandler::destroy(std::string key)
	{
		if (pool_event.find(key) != pool_event.end()) {
			delete pool_event[key];
			pool_event.erase(key);
		}
	}

	void EventHandler::flush()
	{
		for (auto& it : pool_event) {
			delete it.second;
			it.second = nullptr;
		}
		pool_event.clear();
	}
}