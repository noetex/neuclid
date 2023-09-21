static void
enable_dpi_awareness(void)
{
	HMODULE Winuser = LoadLibraryA("user32.dll");
	void* Function = GetProcAddress(Winuser, "SetProcessDpiAwarenessContext");
	if(Function)
	{
		typedef BOOL dpi_function(DPI_AWARENESS_CONTEXT);
		dpi_function* SetProcessDpiAwarenessContext = (dpi_function*)Function;
		if(!SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2))
		{
			SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE);
		}
		return;
	}
	HMODULE ShellCore = LoadLibraryA("shcore.dll");
	Function = GetProcAddress(ShellCore, "SetProcessDpiAwareness");
	if(Function)
	{
		typedef HRESULT dpi_function(PROCESS_DPI_AWARENESS);
		dpi_function* SetProcessDpiAwareness = (dpi_function*)Function;
		SetProcessDpiAwareness(PROCESS_PER_MONITOR_DPI_AWARE);
		return;
	}
	Function = GetProcAddress(Winuser, "SetProcessDPIAware");
	if(Function)
	{
		typedef BOOL dpi_function(void);
		dpi_function* SetProcessDPIAware = (dpi_function*)Function;
		SetProcessDPIAware();
	}
}

static LRESULT CALLBACK
window_proc(HWND Window, UINT Message, WPARAM wParam, LPARAM lParam)
{
	LRESULT Result = 0;
	switch(Message)
	{
		case WM_CLOSE:
		case WM_DESTROY:
		{
			PostQuitMessage(0);
		} break;
		default:
		{
			Result = DefWindowProcW(Window, Message, wParam, lParam);
		} break;
	}
	return Result;
}

static HWND
create_the_window(void)
{
	WNDCLASSEXW WindowClass = {0};
	WindowClass.cbSize = sizeof(WindowClass);
	WindowClass.lpfnWndProc = window_proc;
	WindowClass.lpszClassName = WNDCLASS_NAME;
	RegisterClassExW(&WindowClass);
	DWORD WindowStyle = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
	HWND Result = CreateWindowExW(0, WNDCLASS_NAME, WINDOW_TITLE, WindowStyle, 50, 50, 1280, 720, 0, 0, 0, 0);
	return Result;
}

int WINAPI
wWinMain(HINSTANCE, HINSTANCE, WCHAR*, int)
{
	enable_dpi_awareness();
	HWND Window = create_the_window();

	MSG Message;
	while(GetMessageW(&Message, 0, 0, 0) > 0)
	{
		DispatchMessageW(&Message);
	}
	return 0;
}
