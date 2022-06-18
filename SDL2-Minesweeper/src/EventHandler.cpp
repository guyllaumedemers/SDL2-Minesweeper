#pragma once
#include "../headers/EventHandler.h"

namespace Toolset {
	/// <summary>
	/// Generic Event map
	/// </summary>
	unordered_map<string, IEvent*> EventHandler::pool_event = unordered_map<string, IEvent*>();

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
		/// <summary>
		/// erase call the destructor of each entry between first, last https://www.cplusplus.com/reference/unordered_map/unordered_map/erase/
		/// </summary>
		if (pool_event.find(key) != pool_event.end()) {
			delete pool_event[key];
			pool_event.erase(key);
		}
	}

	/// <summary>
	/// Flush memory
	/// </summary>
	void EventHandler::flush()
	{
		/// <summary>
		/// clear call the destructor of each entry  https://www.cplusplus.com/reference/unordered_map/unordered_map/clear/ , still have to delete manually pointer at key entry... weird.
		/// </summary>
		for (auto& it : pool_event) {
			delete it.second;
			it.second = nullptr;
		}
		pool_event.clear();
	}
}