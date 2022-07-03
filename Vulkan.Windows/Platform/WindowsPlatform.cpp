#include "WindowsPlatform.hpp"

#include "../Logger/Logger.hpp"
#include "../Events/Event_Impl.hpp"
#include "../Events/EventInvoker_Impl.hpp"

namespace Vulkwin {

	WindowsPlatform* WindowsPlatform::instance = 0;

	void OnWindowResized(WindowsPlatform& sender, WindowResizedEventArgs& args)
	{
		LOG_DEBUG("Width  - %d", args.Width);
		LOG_DEBUG("Height - %d", args.Height);
	}

	void OnWindowCreated(WindowsPlatform& sender, Window& window)
	{
		LOG_DEBUG("Window Title  - %s", window.GetTitle());
		LOG_DEBUG("Window Width  - %d", window.GetWidth());
		LOG_DEBUG("Window Height - %d", window.GetHeight());
	}

	WindowsPlatform::WindowsPlatform(Window* window)
	{
		//Required as single working way
		WindowResized = { &windowResizedInvoker };
		WindowCreated = { &windowCreatedInvoker };

		WindowResized.Subscribe(this, OnWindowResized);
		WindowCreated.Subscribe(this, OnWindowCreated);

		this->window = std::shared_ptr<Window>(window);

		windowInfo = { 0 };
		windowInfo.cbSize = sizeof(WNDCLASSEX);
		windowInfo.style = CS_DBLCLKS;
		windowInfo.lpfnWndProc = ProcessMessage;
		windowInfo.hInstance = GetModuleHandleA(0);
		windowInfo.lpszClassName = window->GetTitle();

		if (RegisterClassExA(&windowInfo) == NULL) {
			//TODO: assertion
		}

		windowHandle = CreateWindowExA(
			NULL,
			windowInfo.lpszClassName,
			window->GetTitle(),
			WS_OVERLAPPEDWINDOW,
			window->GetPosition().x,
			window->GetPosition().y,
			window->GetWidth(),
			window->GetHeight(),
			NULL,
			NULL,
			windowInfo.hInstance,
			this);

		if (windowHandle == NULL)
		{
			//TODO: assertion
		}
		else
		{
			ShowWindow(windowHandle, SW_SHOWDEFAULT);
		}

		//Clock initialization
		QueryPerformanceFrequency(&this->frequency);
		QueryPerformanceCounter(&this->startTime);
	}
	WindowsPlatform::~WindowsPlatform()
	{
		DestroyWindow(windowHandle);
		UnregisterClassA(windowInfo.lpszClassName, windowInfo.hInstance);
	}

	bool WindowsPlatform::IsWindowOpen()
	{
		return !window->ShouldClose();
	}
	bool WindowsPlatform::ProcessMessages()
	{
		MSG message = { 0 };
		while (PeekMessageA(&message, NULL, NULL, NULL, PM_REMOVE)) {
			TranslateMessage(&message);
			DispatchMessageA(&message);
		}

		return true;
	}
	LRESULT CALLBACK WindowsPlatform::ProcessMessage(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
	{
		switch (uMsg)
		{
		case WM_CREATE:
		{
			auto createInfo = (LPCREATESTRUCT)lParam;
			auto platformInstance = (WindowsPlatform*)createInfo->lpCreateParams;
			WindowsPlatform::instance = platformInstance;

			WindowsPlatform::instance->windowCreatedInvoker.Invoke(*WindowsPlatform::instance, *WindowsPlatform::instance->window);

			break;
		}
		case WM_SIZE:
		{
			auto width = LOWORD(lParam);
			auto height = HIWORD(lParam);
			WindowsPlatform::instance->window->SetWidth(width);
			WindowsPlatform::instance->window->SetHeight(height);

			WindowResizedEventArgs args{};
			args.Height = height;
			args.Width = width;
			WindowsPlatform::instance->windowResizedInvoker.Invoke(*WindowsPlatform::instance, args);

			break;
		}
		case WM_CLOSE:
		{
			WindowsPlatform::instance->window->Close();
			DestroyWindow(hwnd);
			break;
		}
		case WM_DESTROY:
		{
			PostQuitMessage(0);
			break;
		}
		case WM_KEYDOWN:
		{
			int KEY_Q = 0x51;
			int KEY_A = 0x41;

			if (wParam == KEY_Q) 
			{
				WindowsPlatform::instance->WindowResized.Subscribe(WindowsPlatform::instance, OnWindowResized);
				LOG_DEBUG("WindowsPlatform has subscribed to WindowResized event.");
			}
			if (wParam == KEY_A)
			{
				WindowsPlatform::instance->WindowResized.Unsubscribe(WindowsPlatform::instance);
				LOG_INFO("WindowsPlatform has unsubscribed from WindowResized event.");
			}
		}
		default:
			return DefWindowProcA(hwnd, uMsg, wParam, lParam);
		}

		return 0;
	}

	void* WindowsPlatform::Memory_Allocate(u64 size)
	{
		void* object = malloc(size);

		if (!object) {
			LOG_FATAL("Cannot allocate memory of size %llu", size);
		}

		return object;
	}
	void WindowsPlatform::Memory_Zero(void* object, u64 size)
	{
		memset(object, 0, size);
	}
	void WindowsPlatform::Memory_Free(void* object, u64 size)
	{
		free(object);
	}
	void WindowsPlatform::Memory_Copy(void* object, u64 size, void* outObject)
	{
		memcpy(outObject, object, size);
	}
	void WindowsPlatform::WriteToConsole(const char* message)
	{
		printf(message);
	}
	f64 WindowsPlatform::GetAbsoluteTime()
	{
		LARGE_INTEGER currentTime;
		QueryPerformanceCounter(&currentTime);
		return (currentTime.QuadPart - startTime.QuadPart) * (1.0 / frequency.QuadPart);
	}
}