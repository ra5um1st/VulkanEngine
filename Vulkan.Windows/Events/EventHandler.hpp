#pragma once

namespace Vulkwin {

	template <typename TSender, typename TArgs>
	class EventHandler
	{
	public:

		EventHandler(void (*eventHandler)(TSender sender, TArgs args)) : eventHandler(eventHandler) { }

		virtual void operator()(TSender sender, TArgs args)
		{
			if (eventHandler)
			{
				eventHandler(sender, args);
			}
		}
		virtual bool operator==(const EventHandler& handler)
		{
			return this->eventHandler == handler.eventHandler;
		}
		virtual bool operator!=(const EventHandler& handler)
		{
			return this->eventHandler != handler.eventHandler;
		}

	protected:

		void (*eventHandler)(TSender sender, TArgs args);
	};
}