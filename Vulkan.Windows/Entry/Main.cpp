#include "../Window/Window.hpp"
#include "../Platform/WindowsPlatform.hpp"
#include "../Application/Application.hpp"
#include "../MemoryManager/MemoryManager.hpp"

int main()
{
	auto window = new Vulkwin::Window({ 0, 0 }, 800, 600, "Окно");
	auto platform = new Vulkwin::WindowsPlatform(window);

	Vulkwin::MemoryManager memoryManager = { platform };
	auto window1 = memoryManager.Allocate<Vulkwin::Window>(Vulkwin::AllocationType::WINDOW);
	printf("Total memory usage:    %llu\n", memoryManager.GetTotalMemoryUsage());
	printf("Windows memory usage:  %llu\n", memoryManager.GetMemoryUsageByType(Vulkwin::AllocationType::WINDOW));
	printf("Platform memory usage: %llu\n", memoryManager.GetMemoryUsageByType(Vulkwin::AllocationType::PLATFORM));

	while (platform->IsWindowOpen()) {
		platform->ProcessMessages();
		Sleep(1);
	}
	return 0;
}