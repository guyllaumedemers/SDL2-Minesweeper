#pragma once
#include "Subscriber.h"
#include <vector>

using namespace std;
namespace Toolset {
	template<class T>
	class Event {
	private:
		vector<Subscriber<T>*> subscribers;
		Event(const Event&) = delete;
		Event(Event&&) = delete;
		Event() = delete;
	public:
		Event();
		~Event();
		void add(Subscriber<T>*);
		void remove(Subscriber<T>*);
		void invoke(T& data);
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class T>
	Event<T>::Event()
	{
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class T>
	Event<T>::~Event()
	{
		for (int i = subscribers.size() - 1; i >= 0; --i) {
			delete subscribers[i];
			subscribers[i] = nullptr;
		}
		subscribers.clear();
	}

	/// <summary>
	/// register subscriber
	/// </summary>
	template<class T>
	void Event<T>::add(Subscriber<T>* subscriber)
	{
		subscribers.push_back(subscriber);
	}

	/// <summary>
	/// unregister subscriber
	/// </summary>
	template<class T>
	void Event<T>::remove(Subscriber<T>* subscriber)
	{
		if (auto it = subscribers.find(subscriber) != subscribers.end()) {
			delete it;
			it = nullptr;
		}
	}

	/// <summary>
	/// invoke event
	/// </summary>
	template<class T>
	void Event<T>::invoke(T& data)
	{
		for (int i = subscribers.size() - 1; i >= 0; --i) subscribers[i].invoke(data);
	}
}