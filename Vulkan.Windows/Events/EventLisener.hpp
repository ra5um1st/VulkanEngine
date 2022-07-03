#pragma once

#include "EventHandler.hpp"

namespace Vulkwin {

	template <typename TSender, typename TArgs>
	class EventListener
	{
	public:

		const void* Listener;
		EventHandler<TSender, TArgs> Handler;
		EventListener<TSender, TArgs>* Next;

		EventListener(const void* listener, EventHandler<TSender, TArgs> handler)
			: Listener(listener), Handler(handler), Next(nullptr)
		{
		}
	};
}