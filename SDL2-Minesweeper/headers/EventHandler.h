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
		EventHandler(const EventHandler&) = delete;
		EventHandler(EventHandler&&) = delete;
		EventHandler() = delete;
		EventHandler& operator=(const EventHandler&) = delete;
		EventHandler& operator=(EventHandler&&) = delete;
		static void create(string key, IEvent*);
		static void destroy(string key);
		static void flush();
		template<class T> static void add(string key, ISubscriber*);
		template<class T> static void remove(string key, ISubscriber*);
		template<class T> static void invoke(string key, const T&);
	};

	/// <summary>
	/// Add new Subscriber to the Event at key
	/// </summary>
	template<class T>
	void EventHandler::add(string key, ISubscriber* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>*>(pool_event[key])->add(subscriber);
	}

	/// <summary>
	/// Remove Subscriber to the Event at key
	/// </summary>
	template<class T>
	void EventHandler::remove(string key, ISubscriber* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>*>(pool_event[key])->remove(subscriber);
	}

	/// <summary>
	/// Invoke event passing args data
	/// </summary>
	template<class T>
	void EventHandler::invoke(string key, const T& data)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>*>(pool_event[key])->invoke(data);
	}
}