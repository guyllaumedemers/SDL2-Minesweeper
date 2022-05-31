#pragma once
#include "IEvent.h"
#include "Subscriber.h"
#include <vector>

using namespace std;
namespace Toolset {
	template<class T>
	class Event : virtual public IEvent {
	private:
		vector<ISubscriber*> subscribers;
		Event(const Event&) = delete;
		Event(Event&&) = delete;
	public:
		Event();
		~Event();
		void add(ISubscriber*);
		void remove(ISubscriber*);
		void invoke(const T& data);
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
	void Event<T>::add(ISubscriber* subscriber)
	{
		subscribers.push_back(subscriber);
	}

	/// <summary>
	/// unregister subscriber
	/// </summary>
	template<class T>
	void Event<T>::remove(ISubscriber* subscriber)
	{
		vector<ISubscriber*>::iterator it = find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end()) subscribers.erase(it);
	}

	/// <summary>
	/// invoke event
	/// </summary>
	template<class T>
	void Event<T>::invoke(const T& data)
	{
		for (int i = subscribers.size() - 1; i >= 0; --i) dynamic_cast<Subscriber<T>&>(*subscribers[i]).invoke(data);
	}
}