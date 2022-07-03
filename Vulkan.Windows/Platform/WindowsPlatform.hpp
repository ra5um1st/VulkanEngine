#pragma once

#include <Windows.h>
#include <memory>

#include "Platform.hpp"
#include "../Window/Window.hpp"
#include "../Events/Event.hpp"
#include "../Events/WindowResizedEvent/WindowResizedEvent.hpp"

namespace Vulkwin {

	class WindowsPlatform : public Platform
	{
	public:

		Event<WindowsPlatform&, WindowResizedEventArgs&> WindowResized;
		Event<WindowsPlatform&, Window&> WindowCreated;

		bool IsWindowOpen();
		bool ProcessMessages() override;


		void* Memory_Allocate(u64 size) override;
		void Memory_Zero(void* object, u64 size) override;
		void Memory_Free(void* object, u64 size) override;
		void Memory_Copy(void* object, u64 size, void* outObject) override;

		void WriteToConsole(const char* message) override;
		f64 GetAbsoluteTime()override;


		WindowsPlatform(Window* window);
		~WindowsPlatform();

	private:

		HWND windowHandle;
		WNDCLASSEXA windowInfo;
		LARGE_INTEGER startTime;
		LARGE_INTEGER frequency;

		EventInvoker<WindowsPlatform&, WindowResizedEventArgs&> windowResizedInvoker;
		EventInvoker<WindowsPlatform&, Window&> windowCreatedInvoker;

		std::shared_ptr<Window> window;
		static WindowsPlatform* instance;

		static LRESULT ProcessMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
	};
}