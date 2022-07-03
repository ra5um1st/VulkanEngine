#pragma once

#include "EventInvoker.hpp"

namespace Vulkwin {

	template<typename TSender, typename TArgs>
	EventInvoker<TSender, TArgs>::~EventInvoker()
	{
		if (Listeners->Next)
		{
			EventListener<TSender, TArgs>* prevListener = Listeners;
			for (EventListener<TSender, TArgs>* currentListener = Listeners->Next; currentListener != nullptr; currentListener = currentListener->Next)
			{
				delete prevListener;
				prevListener = currentListener;
			}
		}
		else
		{
			delete Listeners;
		}
	}

	template<typename TSender, typename TArgs>
	bool EventInvoker<TSender, TArgs>::Invoke(TSender sender, TArgs args)
	{
		for (EventListener<TSender, TArgs>* currentListener = this->Listeners; currentListener != nullptr; currentListener = currentListener->Next)
		{
			if (currentListener->Handler != nullptr) 
			{
				currentListener->Handler(sender, args);
			}
		}

		return true;
	}
}