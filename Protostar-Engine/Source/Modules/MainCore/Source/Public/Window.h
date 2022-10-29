#pragma once

#include "GlobalDefinitions.h"
#include "MainCore.h"
#include "Vector.h"
#include "Array.h"

#include <Windows.h>
#include <utility>
#include <string>
#include <functional>
#include <unordered_map>

namespace Protostar::Core
{
	class InputProcessor;

	struct MAINCORE_API WindowDimensions
	{
		Vector2D<s32> Size;
		Vector2D<s32> Position;
	};

	struct MAINCORE_API WindowClassParams
	{
		LPCWSTR ClassName;
		HINSTANCE HInstance;
		HBRUSH BackgroundColor;
		u32 Style;
	};

	struct MAINCORE_API WindowCreationParams
	{
		LPCWSTR WindowName;
		u64 DwExStyle;
		u64 DwStyle;
		HWND ParentWindow;
		HMENU Menu;
		LPVOID LpParam;
	};

	struct MAINCORE_API WindowInfo
	{
		WindowClassParams ClassParams;
		WindowDimensions DimParams;
		WindowCreationParams CreationParams;
	};

	class MAINCORE_API Window
	{
	public:
		void ShowWindow(const s32 _nCmdShow);

		void UpdateWindow();

		bool Run(MSG& _msg);

		void UpdateWindowPos(const s32 _x, const s32 _y);

		void UpdateWindowSize(const s32 _width, const s32 _height);

		void RegisterEventCallback(const u32 _wmEvent, const std::function<s32(HWND, u32, WPARAM, LPARAM)>& _func);

		HWND GetWindowHandle() const;

		const WindowDimensions& GetCurrentDimensions() const;

		const Array<std::function<s32(HWND, u32, WPARAM, LPARAM)>>& GetEventFunctions(u32 _eventKey) const
		{
			return m_eventMap.at(_eventKey);
		}
	private:
		friend class WindowManager;

		Window(const WindowInfo& _windowInfo, InputProcessor* _inputProcessor = nullptr);


		bool Create(std::string& _errorMsg);

		WindowInfo m_windowInfo;
		std::unordered_map<u32, Array<std::function<s32(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam)>>> m_eventMap;
		std::unique_ptr<InputProcessor> m_inputProcessor;
		HWND m_wndHandle;
	};
}
