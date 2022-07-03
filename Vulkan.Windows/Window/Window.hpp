#pragma once

#include <Windows.h>
#include <string>

namespace Vulkwin {

	class Window
	{
	public:
		const char* const GetTitle();
		bool SetTitle(const char* title);
		UINT GetWidth();
		bool SetWidth(UINT width);
		UINT GetHeight();
		bool SetHeight(UINT height);
		POINT GetPosition();
		bool SetPosition(POINT position);
		void Close();
		bool ShouldClose();

		Window() {}
		Window(POINT position, UINT width, UINT height, const char* title);

		Window(const Window&) = delete;
		Window& operator =(const Window&) = delete;

	private:
		POINT position = {};
		UINT width = {};
		UINT height = {};
		const char* title = {};
		bool shouldClose = {};
	};
}