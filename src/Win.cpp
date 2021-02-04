#include <windows.h> // Include

LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM); // Define window procedure function

void WinMenus(HWND); // Define function to add menus

HMENU hMenu; // define header menu

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) // Enter
{
	WNDCLASSW win = { 0 }; // win class

	win.hbrBackground = (HBRUSH)COLOR_WINDOW ; // background
	win.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor
	win.hInstance = hInst;
	win.lpszClassName = L"MainWin"; // define window class name
	win.lpfnWndProc = Proc; // Set procedure name

	if (!RegisterClassW(&win)) // Register win class
		return -1;

	CreateWindowW(L"MainWin", L"CMandel", WS_OVERLAPPEDWINDOW | WS_VISIBLE, 500, 200, 500, 500, NULL, NULL, NULL, NULL); // Create window with basic params
	
	// TEMPORARY, CALL AND INTERFACE WITH OTHER CPP FILES AND FUNCTIONS HERE
	MSG defmsg = { 0 }; // define empty message
	while (GetMessage(&defmsg, NULL, NULL, NULL)) // keep window open
	{
		TranslateMessage(&defmsg);
		DispatchMessage(&defmsg);
	}

	return 0;
}

LRESULT CALLBACK Proc(HWND hWnd, UINT defmsg, WPARAM wp, LPARAM lp) // window procedure code
{
	switch (defmsg)
	{
	case WM_COMMAND: // selected when any menu item is clicked
		switch (wp) // chooses code based on which menu is clicked
		{
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4: // Help box
			MessageBox(hWnd, "© 2021 Brendan Scott\n\nWASD : Location\nMouse 1/2 : Zoom\n+/- : iterations", "CMandel 0.1", MB_OK);
			break;
		}
		break;
	case WM_CREATE: // when window is created
		WinMenus(hWnd); // call menu function
		break;
	case WM_DESTROY: // when close is hit
		PostQuitMessage(0); // close and send exit code 0
		break;
	default: // default case for all others
		return DefWindowProcW(hWnd, defmsg, wp, lp); // return
	}
}

void WinMenus(HWND hWnd) // window menu code
{
	hMenu = CreateMenu(); // creates top menu
	HMENU ConfigMenu = CreateMenu(); // creates menu identifiers
	HMENU FractMenu = CreateMenu();
	HMENU FilterMenu = CreateMenu();
	HMENU RenderMenu = CreateMenu();
	HMENU ColorMenu = CreateMenu();

	// Appends items to top level menu
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)ConfigMenu, "Configure");
	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)FilterMenu, "Filters");
	AppendMenu(hMenu, MF_RIGHTJUSTIFY | MF_STRING, 4, "?");

	// Appends items to Configure menu
	AppendMenu(ConfigMenu, MF_POPUP, NULL, "Formula");
	AppendMenu(ConfigMenu, MF_POPUP, NULL, "Colors");
	AppendMenu(ConfigMenu, MF_POPUP, NULL, "Location");
	AppendMenu(ConfigMenu, MF_POPUP, NULL, "Window size");
	AppendMenu(ConfigMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(ConfigMenu, MF_STRING, NULL, "Exit");

	//Creates FilterMenu submenu
	AppendMenu(FilterMenu, MF_STRING, NULL, "Decolorize");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Edge detect");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Inverse edge");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Grayscale");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Inverse Grayscale");

	SetMenu(hWnd, hMenu); // Sets hMenu to be added to hWnd
}
