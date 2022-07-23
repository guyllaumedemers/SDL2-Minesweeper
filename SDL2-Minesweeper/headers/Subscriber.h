
#ifndef INCLUDED_SUBSCRIBER
#define INCLUDED_SUBSCRIBER

#include "ISubscriber.h"

namespace Toolset {
	template<class T>
	class Subscriber final : virtual public ISubscriber {
		typedef void(*FunctionPtr)(const T&);
		FunctionPtr func_ptr = nullptr;
	public:
		Subscriber(const Subscriber&) = delete;
		Subscriber(Subscriber&&) = delete;
		Subscriber() = delete;
		Subscriber(void(*)(const T&));
		~Subscriber() override;
		Subscriber& operator=(const Subscriber&) = delete;
		Subscriber& operator=(Subscriber&&) = delete;
		void invoke(const T& data);
	};

	template<class T>
	inline Subscriber<T>::Subscriber(void(*event_callback)(const T&))
	{
		func_ptr = event_callback;
	}

	template<class T>
	inline Subscriber<T>::~Subscriber()
	{
		func_ptr = nullptr;
	}

	template<class T>
	inline void Subscriber<T>::invoke(const T& data)
	{
		func_ptr(data);
	}
}
#endif