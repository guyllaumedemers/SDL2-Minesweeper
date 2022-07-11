#pragma once
#include "ISubscriber.h"

using namespace std;
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

	/// <summary>
	/// Constructor
	/// </summary>
	template<class T>
	Subscriber<T>::Subscriber(void(*event_callback)(const T&))
	{
		func_ptr = event_callback;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class T>
	Subscriber<T>::~Subscriber()
	{
		func_ptr = nullptr;
	}

	/// <summary>
	/// invoke event
	/// </summary>
	template<class T>
	void Subscriber<T>::invoke(const T& data)
	{
		func_ptr(data);
	}
}