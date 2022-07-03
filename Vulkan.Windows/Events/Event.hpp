#pragma once

#include <Windows.h>

#include "EventInvoker.hpp"

#include "../Logger/Logger.hpp"

namespace Vulkwin {

	template <typename TSender, typename TArgs>
	class Event
	{
	public:

		Event() : listeners(nullptr) { }
		Event(const EventInvoker<TSender, TArgs>* invoker) : listeners(invoker->Listeners) { }

		bool Subscribe(const void* listener, const EventHandler<TSender, TArgs>& handler);
		bool Unsubscribe(const void* listener);

	protected:

		EventListener<TSender, TArgs>* listeners;
	};

}