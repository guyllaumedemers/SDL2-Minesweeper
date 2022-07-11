#pragma once
#include "IEvent.h"
#include "Subscriber.h"
#include <vector>

using namespace std;
namespace Toolset {
	template<class T>
	class Event final : virtual public IEvent {
	private:
		vector<ISubscriber*> subscribers = vector<ISubscriber*>();
	public:
		Event(const Event&) = delete;
		Event(Event&&) = delete;
		Event() = default;
		~Event() override;
		Event& operator=(const Event&) = delete;
		Event& operator=(Event&&) = delete;
		void add(ISubscriber*);
		void remove(ISubscriber*);
		void invoke(const T& data);
	};

	/// <summary>
	/// Destructor
	/// </summary>
	template<class T>
	Event<T>::~Event()
	{
		for (auto& it : subscribers) {
			delete it;
			it = nullptr;
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
		auto it = find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end()) subscribers.erase(it);
	}

	/// <summary>
	/// invoke event
	/// </summary>
	template<class T>
	void Event<T>::invoke(const T& data)
	{
		/// <summary>
		/// do not convert int -> size_t, it goes out of scope
		/// </summary>
		for (int i = subscribers.size() - 1; i >= 0; --i) dynamic_cast<Subscriber<T>*>(subscribers[i])->invoke(data);
	}
}