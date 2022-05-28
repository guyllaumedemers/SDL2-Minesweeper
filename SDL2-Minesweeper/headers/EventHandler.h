#pragma once
#include "Event.h"
#include "Subscriber.h"

#include <unordered_map>
#include <string>

using namespace std;
namespace Toolset {
	class EventHandler {
	private:
		template<class T> static unordered_map<string, Event<T>*> pool_event;
	public:
		template<class T> static void create(string key, Event<T>*);
		template<class T> static void destroy(string key);
		template<class T> static void add(string key, Subscriber<T>*);
		template<class T> static void remove(string key, Subscriber<T>*);
		template<class T> static void invoke(string key, T&);
	};

	/// <summary>
	/// Generic Event map
	/// </summary>
	template<class T>
	unordered_map<string, Event<T>*> EventHandler::pool_event;

	/// <summary>
	/// Create a new Event<T>
	/// </summary>
	template<class T>
	void EventHandler::create(string key, Event<T>* _event)
	{
		if (pool_event.find(key) != pool_event.end()) pool_event.insert({ key, _event });
	}

	/// <summary>
	/// Destroy element at key
	/// </summary>
	template<class T>
	void EventHandler::destroy(string key)
	{
		if (pool_event.find(key) != pool_event.end()) {
			delete pool_event[key];
			pool_event[key] = nullptr;
			pool_event.erase(key);
		}
	}

	/// <summary>
	/// Add new Subscriber to the Event at key
	/// </summary>
	template<class T>
	void EventHandler::add(string key, Subscriber<T>* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) pool_event[key].add(subscriber);
	}

	/// <summary>
	/// Remove Subscriber to the Event at key
	/// </summary>
	template<class T>
	void EventHandler::remove(string key, Subscriber<T>* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) pool_event[key].remove(subscriber);
	}

	/// <summary>
	/// Invoke event passing args data
	/// </summary>
	template<class T>
	void EventHandler::invoke(string key, T& data)
	{
		if (pool_event.find(key) != pool_event.end()) pool_event[key].invoke(data);
	}
}