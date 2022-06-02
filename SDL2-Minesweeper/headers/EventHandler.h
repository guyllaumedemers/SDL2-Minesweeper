#pragma once
#include "Event.h"
#include "Subscriber.h"
#include <unordered_map>
#include <string>

using namespace std;
namespace Toolset {
	class EventHandler {
	private:
		static unordered_map<string, IEvent*> pool_event;
	public:
		static void create(string key, IEvent*);
		static void destroy(string key);
		static void flush();
		template<class T> static void add(string key, ISubscriber*);
		template<class T> static void remove(string key, ISubscriber*);
		template<class T> static void invoke(string key, const T&);
	};

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

	/// <summary>
	/// Add new Subscriber to the Event at key
	/// </summary>
	template<class T>
	void EventHandler::add(string key, ISubscriber* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>&>(*pool_event[key]).add(subscriber);
	}

	/// <summary>
	/// Remove Subscriber to the Event at key
	/// </summary>
	template<class T>
	void EventHandler::remove(string key, ISubscriber* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>&>(*pool_event[key]).remove(subscriber);
	}

	/// <summary>
	/// Invoke event passing args data
	/// </summary>
	template<class T>
	void EventHandler::invoke(string key, const T& data)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>&>(*pool_event[key]).invoke(data);
	}
}