#pragma once

#include "../Types.hpp"
#include "../Platform/Platform.hpp"

#include <typeinfo>

namespace Vulkwin {

	enum AllocationType
	{
		DATA_STRUCTURE,
		OBJECT,
		APPLICATION,
		EVENT,
		WINDOW,
		GRAPHICS_OBJECT,
		PLATFORM,

		ALLOCATION_TYPE_MAX_VALUE
	};

	class MemoryManager
	{
	public:

		MemoryManager(Platform* platform) : platform(platform)
		{
			u64 platformSize = sizeof(platform);
			u64 memoryManagerSize = sizeof(this);
			totalMemoryUsage += platformSize;
			totalMemoryUsage += memoryManagerSize;
			memoryUsageType[PLATFORM] += platformSize;
			memoryUsageType[OBJECT] += memoryManagerSize;
		}

		template <typename T>
		T* Allocate(AllocationType allocationType)
		{
			if (!platform) {
				LOG_FATAL("Cannot allocate memory of %s. Platform has not been set.", typeid(T).name());
				return nullptr;
			}

			u32 objectSize = sizeof(T);
			void* objectMemory = platform->Memory_Allocate(objectSize);
			platform->Memory_Zero(objectMemory, objectSize);

			memoryUsageType[allocationType] += objectSize;
			totalMemoryUsage += objectSize;

			return (T*)objectMemory;
		}

		template <typename T>
		void Free(T* object, AllocationType allocationType)
		{
			u32 objectSize = sizeof(T);
			platform->Memory_Free(object);
			totalMemoryUsage -= objectSize;
			memoryUsageType[allocationType] -= objectSize;
		}

		u64 GetTotalMemoryUsage();
		u64 GetMemoryUsageByType(AllocationType allocationType);

	private:

		Platform* platform;
		u64 memoryUsageType[ALLOCATION_TYPE_MAX_VALUE] = {};
		u64 totalMemoryUsage = {};
	};
}
