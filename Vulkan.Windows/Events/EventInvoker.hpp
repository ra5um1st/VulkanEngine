#pragma once

#include "EventLisener.hpp"

namespace Vulkwin {

	template <typename TSender, typename TArgs>
	class EventInvoker
	{
	public:

		EventInvoker() : Listeners(new EventListener<TSender, TArgs>(nullptr, nullptr)) { }
		~EventInvoker();

		bool Invoke(TSender sender, TArgs args);

		EventListener<TSender, TArgs>* Listeners;
	};
}
