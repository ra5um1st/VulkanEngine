#include "Window.hpp"
#include "../Logger/Logger.hpp"

namespace Vulkwin {

	Window::Window(POINT position, UINT width, UINT height, const char* title) :
		position(position), width(width), height(height), title(title)
	{
		shouldClose = 0;
	}
	const char* const Window::GetTitle()
	{
		return title;
	}
	bool Window::SetTitle(const char* const title)
	{
		if (this->title == title) 
		{
			return false;
		}
		this->title = title;
		return true;
	}
	UINT Window::GetWidth()
	{
		return this->width;
	}
	bool Window::SetWidth(UINT width)
	{
		if (this->width == width)
		{
			return false;
		}
		this->width = width;
		return true;
	}
	UINT Window::GetHeight()
	{
		return this->height;
	}
	bool Window::SetHeight(UINT height)
	{
		if (this->height == height)
		{
			return false;
		}
		this->height = height;
		return true;
	}
	POINT Window::GetPosition()
	{
		return this->position;
	}
	bool Window::SetPosition(POINT position)
	{
		if (this->position.y == position.y && 
			this->position.x == position.x)
		{
			return false;
		}
		this->position = position;
		return true;
	}
	void Window::Close()
	{
		shouldClose = true;
	}
	bool Window::ShouldClose()
	{
		return shouldClose;
	}
}