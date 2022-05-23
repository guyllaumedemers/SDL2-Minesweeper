#pragma once
#include "../headers/EventManager.h"
#ifdef _DEBUG
#include "../headers/CRTMemoryLeak.h"
#endif

namespace Toolset {
	/// <summary>
	/// event keys
	/// </summary>
	string EventManager::event_pool[5] = {
		"onApplicationQuitEvent",
		"onMouseDownEvent",
		"onNewGameSelectedEvent",
		"onModeSelectionChangedEvent",
		"onHelpDocumentSelectedEvent"
	};

	unordered_map<string, EventHandler*> EventManager::events;

	void EventManager::create()
	{
#ifdef _DEBUG
		for (const auto& it : event_pool) events.insert({ it, DBG_NEW EventHandler() });
#else
		for (const auto& it : event_pool) events.insert({ it, new EventHandler() });
#endif
	}

	void EventManager::destroy()
	{
		for (auto& it : event_pool) delete events[it];
		events.clear();
	}

	EventHandler* EventManager::get(string key)
	{
		if (events.find(key) != events.end()) return events[key];
		else return nullptr;
	}
}