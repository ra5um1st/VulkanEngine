#pragma once

#include "Event.hpp"

namespace Vulkwin {

	template <typename TSender, typename TArgs>
	bool Event<TSender, TArgs>::Subscribe(const void* listener, const EventHandler<TSender, TArgs>& handler)
	{
		if (listeners->Listener == nullptr)
		{
			listeners->Listener = listener;
			listeners->Handler = handler;
		}
		else
		{
			for (EventListener<TSender, TArgs>* currentListener = listeners; currentListener != nullptr; currentListener = currentListener->Next)
			{
				if (currentListener->Listener == listener)
				{
					LOG_WARN("Listener has not subscribed [%p] to event [%p]. It has already subscribed.", &listener, this);
					return false;
				}
				if (currentListener->Next == nullptr)
				{
					currentListener->Next = new EventListener<TSender, TArgs>(listener, handler);
					break;
				}
			}
		}

		return true;
	}

	template <typename TSender, typename TArgs>
	bool Event<TSender, TArgs>::Unsubscribe(const void* listener)
	{
		EventListener<TSender, TArgs>* prevListener = nullptr;
		for (EventListener<TSender, TArgs>* currentListener = listeners; currentListener != nullptr; currentListener = currentListener->Next)
		{
			if (currentListener->Listener == listener)
			{
				if (prevListener) {

					//Node
					prevListener->Next = currentListener->Next;
					delete currentListener;
				}

				//Head
				currentListener->Listener = nullptr;
				currentListener->Handler = nullptr;

				break;
			}

			EventListener<TSender, TArgs>* prevListener = currentListener;

			if (prevListener->Listener == nullptr)
			{
				LOG_WARN("Listener [%p] has not unsubscribed from event [%p]. It has not subscribed before.", listener, this);
			}
		}

		return true;
	}
}