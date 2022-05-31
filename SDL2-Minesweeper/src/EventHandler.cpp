#pragma once
#include "../headers/EventHandler.h"

namespace Toolset {
	/// <summary>
	/// Generic Event map
	/// </summary>
	unordered_map<string, IEvent*> EventHandler::pool_event;

	/// <summary>
	/// Create a new Event<T>
	/// </summary>
	void EventHandler::create(string key, IEvent* _event)
	{
		if (pool_event.find(key) == pool_event.end()) pool_event.insert({ key, _event });
	}

	/// <summary>
	/// Destroy element at key
	/// </summary>
	void EventHandler::destroy(string key)
	{
		if (pool_event.find(key) != pool_event.end()) {
			delete pool_event[key];
			pool_event[key] = nullptr;
			pool_event.erase(key);
		}
	}

	/// <summary>
	/// Flush memory
	/// </summary>
	void EventHandler::flush()
	{
		for (auto& it : pool_event) {
			delete it.second;
			it.second = nullptr;
		}
		pool_event.clear();
	}
}
