#include "MemoryManager.hpp"

namespace Vulkwin {

	u64 MemoryManager::GetTotalMemoryUsage()
	{
		return totalMemoryUsage;
	}

	u64 MemoryManager::GetMemoryUsageByType(AllocationType allocationType)
	{
		return memoryUsageType[allocationType];
	}
}