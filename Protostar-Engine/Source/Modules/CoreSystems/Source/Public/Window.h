#pragma once

#include "Array.h"
#include "CoreSystems.h"
#include "GlobalDefinitions.h"
#include "MainCore.h"
#include "UniquePtr.h"
#include "Vector.h"

#include <Windows.h>
#define NOMINMAX
#include <utility>
#include <string>
#include <functional>
#include <unordered_map>

namespace Protostar::Core
{
	class InputProcessor;

	struct CORESYSTEMS_API WindowDimensions
	{
		Vector2D<s32> Size;
		Vector2D<s32> Position;
	};

	struct CORESYSTEMS_API WindowClassParams
	{
		LPCWSTR ClassName;
		HINSTANCE HInstance;
		HBRUSH BackgroundColor;
		u32 Style;
	};

	struct CORESYSTEMS_API WindowCreationParams
	{
		LPCWSTR WindowName;
		u64 DwExStyle;
		u64 DwStyle;
		HWND ParentWindow;
		HMENU Menu;
		LPVOID LpParam;
	};

	struct CORESYSTEMS_API WindowInfo
	{
		WindowClassParams ClassParams;
		WindowDimensions DimParams;
		WindowCreationParams CreationParams;
	};

#define REGISTER_EVENT_CALLBACK(EVENT, CLASS, FUNC)\
	RegisterEventCallback(EVENT, std::bind(FUNC, CLASS, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4));

#define REGISTER_INPUT_DOWN_CALLBACK(KEY, CLASS, FUNC)\
	GetInputProcessor()->RegisterInputDownCallback(KEY, std::bind(FUNC, CLASS));

#define REGISTER_INPUT_UP_CALLBACK(KEY, CLASS, FUNC)\
	GetInputProcessor()->RegisterInputUpCallback(KEY, std::bind(FUNC, CLASS));

	class CORESYSTEMS_API Window
	{
	public:

		void ShowWindow(const s32 _nCmdShow);

		void UpdateWindow();

		bool Run(MSG& _msg);

		void UpdateWindowPos(const s32 _x, const s32 _y);

		void UpdateWindowSize(const s32 _width, const s32 _height);

		void RegisterEventCallback(const u32 _wmEvent, const std::function<s32(HWND, u32, WPARAM, LPARAM)>& _func);

		InputProcessor* GetInputProcessor() const;

		HWND GetWindowHandle() const;

		const WindowDimensions& GetCurrentDimensions() const;

		const Array<std::function<s32(HWND, u32, WPARAM, LPARAM)>>& GetEventFunctions(u32 _eventKey) const
		{
			return m_eventMap.at(_eventKey);
		}
	private:
		friend class WindowManager;

		Window(const WindowInfo& _windowInfo, InputProcessor* _inputProcessor = nullptr);

		bool TryCreate(std::string& _errorMsg);

		WindowInfo m_windowInfo;
		std::unordered_map<
			u32, 
			Array<
				std::function<s32(HWND _hwnd, u32 _msg, WPARAM _wParam, LPARAM _lParam)>
				>
			> m_eventMap;
		UniquePtr<InputProcessor> m_inputProcessor;
		HWND m_wndHandle;
	};
}