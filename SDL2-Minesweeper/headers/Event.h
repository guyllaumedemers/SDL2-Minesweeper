
#ifndef INCLUDED_EVENT
#define INCLUDED_EVENT

#include "ISubscriber.h"
#include "Subscriber.h"
#include <vector>

namespace Toolset {
	template<class T>
	class Event final : virtual public IEvent {
		std::vector<ISubscriber*> subscribers;
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

	template<class T>
	inline Event<T>::~Event()
	{
		for (auto it : subscribers) {
			delete it;
			it = nullptr;
		}
		subscribers.clear();
	}

	template<class T>
	inline void Event<T>::add(ISubscriber* subscriber)
	{
		subscribers.push_back(subscriber);
	}

	template<class T>
	inline void Event<T>::remove(ISubscriber* subscriber)
	{
		const auto it = find(subscribers.begin(), subscribers.end(), subscriber);
		if (it != subscribers.end()) subscribers.erase(it);
	}

	template<class T>
	inline void Event<T>::invoke(const T& data)
	{
		for (int i = subscribers.size() - 1; i >= 0; --i) dynamic_cast<Subscriber<T>*>(subscribers[i])->invoke(data);
	}
}
#endif