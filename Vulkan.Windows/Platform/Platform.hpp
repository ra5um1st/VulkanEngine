#pragma once

#include "../Types.hpp"

namespace Vulkwin {


	class Platform 
	{
	public:
		virtual bool ProcessMessages() = 0;
		
		virtual void* Memory_Allocate(u64 size) = 0;
		virtual void Memory_Zero(void* object, u64 size) = 0;
		virtual void Memory_Free(void* object, u64 size) = 0;
		virtual void Memory_Copy(void* object, u64 size, void* outObject) = 0;

		virtual void WriteToConsole(const char* message) = 0;
		virtual f64 GetAbsoluteTime() = 0;
	};
}