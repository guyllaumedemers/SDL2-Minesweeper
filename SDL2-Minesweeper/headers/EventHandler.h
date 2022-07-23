
#ifndef INCLUDED_EVENTHANDLER
#define INCLUDED_EVENTHANDLER

#include "IEvent.h"
#include "Event.h"
#include "ISubscriber.h"
#include <unordered_map>
#include <string>

namespace Toolset {
	class EventHandler {
		static inline std::unordered_map<std::string, IEvent*> pool_event;
	public:
		EventHandler(const EventHandler&) = delete;
		EventHandler(EventHandler&&) = delete;
		EventHandler() = delete;
		EventHandler& operator=(const EventHandler&) = delete;
		EventHandler& operator=(EventHandler&&) = delete;
		static void create(std::string key, IEvent*);
		static void destroy(std::string key);
		static void flush();
		template<class T> static void add(std::string key, ISubscriber*);
		template<class T> static void remove(std::string key, ISubscriber*);
		template<class T> static void invoke(std::string key, const T&);
	};

	template<class T>
	void EventHandler::add(std::string key, ISubscriber* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>*>(pool_event[key])->add(subscriber);
	}

	template<class T>
	void EventHandler::remove(std::string key, ISubscriber* subscriber)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>*>(pool_event[key])->remove(subscriber);
	}

	template<class T>
	void EventHandler::invoke(std::string key, const T& data)
	{
		if (pool_event.find(key) != pool_event.end()) dynamic_cast<Event<T>*>(pool_event[key])->invoke(data);
	}
}
#endif