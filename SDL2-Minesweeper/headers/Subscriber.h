#pragma once

namespace Toolset {
	template<class T>
	class Subscriber {
		void(*)(T&) event_callback;
		Subscriber(const Subscriber&) = delete;
		Subscriber(Subscriber&&) = delete;
	public:
		Subscriber(void(*)(T&));
		~Subscriber();
		void invoke(T& data);
	};

	/// <summary>
	/// Constructor
	/// </summary>
	template<class T>
	Subscriber<T>::Subscriber(void(*event_callback)(T&))
	{
		this->event_callback = event_callback;
	}

	/// <summary>
	/// Destructor
	/// </summary>
	template<class T>
	Subscriber<T>::~Subscriber()
	{
		event_callback = nullptr;
	}

	/// <summary>
	/// invoke event
	/// </summary>
	template<class T>
	void Subscriber<T>::invoke(T& data)
	{
		event_callback(data);
	}
}