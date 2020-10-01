#include <iostream>
#include <Windows.h>
#include <ShellScalingApi.h>
#include <WinUser.h>
#include <conio.h>
#include <vector>
#include <string>

bool Contains(std::vector<std::wstring> container, std::wstring element)
{
	for (auto& it : container)
	{
		if (it == element)
		{
			return true;
		}
	}

	return false;
}

int main(int argc, char* argv[])
{
	int old_dpi = 0;
	DEVMODE dev, new_Dev;
	ZeroMemory(&dev, sizeof(dev));
	dev.dmSize = sizeof(DEVMODEA);
	dev.dmDriverExtra = 0;
	new_Dev.dmSize = sizeof(DEVMODE);
	new_Dev.dmDriverExtra = 0;
	std::vector<DISPLAY_DEVICE> disp_dev;

	DISPLAY_DEVICE disp;
	DISPLAY_DEVICEA disp1, disp2;
	int index = 0;
	disp.cb = sizeof(DISPLAY_DEVICE);
	disp1.cb = sizeof(DISPLAY_DEVICEA);
	disp2.cb = sizeof(DISPLAY_DEVICEA);
	
	EnumDisplayDevicesA(NULL, 0, &disp1, EDD_GET_DEVICE_INTERFACE_NAME);
	EnumDisplayDevicesA(disp1.DeviceString, 0, &disp2, EDD_GET_DEVICE_INTERFACE_NAME);

	while (EnumDisplayDevices(NULL, index, &disp, EDD_GET_DEVICE_INTERFACE_NAME))
	{
		disp_dev.push_back(disp);
		++index;
	}
	index = 0;

	std::vector<std::wstring> DeviceString;

	for (auto& disp_str : disp_dev)
	{
		if (!Contains(DeviceString, disp_str.DeviceString))
		{
			DeviceString.emplace_back(disp_str.DeviceString);
		}
	}
	
	while (EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &new_Dev))
	{
		if (dev.dmPelsHeight != new_Dev.dmPelsHeight || dev.dmPelsWidth != new_Dev.dmPelsWidth || dev.dmLogPixels != new_Dev.dmLogPixels)
		{
			system("cls");
			dev = new_Dev;
			std::cout << dev.dmPelsWidth << 'x' << dev.dmPelsHeight << std::endl << new_Dev.dmLogPixels / 96 * 100 << '%' << std::endl;
		}

		if (_kbhit())
		{
			char EXIT_KEY = _getch();
			if (EXIT_KEY == 'r' || EXIT_KEY == ' ')
			{
				break;
			}
		}

		Sleep(2000);
	}

	return 0;
}