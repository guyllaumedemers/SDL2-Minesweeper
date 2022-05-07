#pragma once
#include "../headers/Subscriber.h"

namespace Toolset {
	Subscriber::Subscriber(EventHandler* target, void(*callback)()) : subject(target), action(callback) { subject->add(this); }
	Subscriber::~Subscriber() { subject->remove(this); subject = nullptr; }

	void Subscriber::invoke()
	{
		action();
	}
}