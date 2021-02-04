#include <windows.h> // Include
#include <string>

LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM); // Declare existence
void WinMenus(HWND); // Declare existence
void InfoBar(HWND); // Declare existence
void FormulaMenu(HWND); //Declare existence
void ColorMenu(HWND); //Declare existence
void LocationMenu(HWND); //Declare existence

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

	CreateWindowW(L"MainWin", L"CMandel", WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME | WS_VISIBLE, 500, 200, 500+16, 500+76, NULL, NULL, NULL, NULL); // Create window with basic params
	
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
			FormulaMenu(hWnd); // Call formula menu
			break;
		case 2:
			ColorMenu(hWnd); // Call color menu
			break;
		case 3:
			LocationMenu(hWnd); // Call location menu
			break;
		case 4: // Help box
			CreateWindowW(L"static", L" About CMandel...   © 2021, Brendan Scott\n\n This is open source software :\n Github.com/BrendanScott105/CMandel\n\n Controls :\n W / A / S / D : Up / Left / Down / Right\n Mouse left : Zoom in\n Mouse right : Zoom out\n - / + : Increase / Decrease iterations\n\n Info bar :\n i - Iters | X - Real | Y - Imaginary | Z - Zoom\n\n Limitations :\n - Iterations does not exceed 999999\n - Zoom limited to 2^64\n - Precision limited to 64 Bits\n - Resolution locked at 500x500", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 95, 300, 310, hWnd, NULL, NULL, NULL);
			CreateWindowW(L"static", L" ╳", WS_VISIBLE | WS_BORDER | WS_CHILD, 379, 95, 21, 20, hWnd, NULL, NULL, NULL);
			CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 114, 300, 1, hWnd, NULL, NULL, NULL);
			break;
		case 5: // exit button
			exit(0); // exit with code 0
			break;
		}
		break;
	case WM_CREATE: // when window is created
		WinMenus(hWnd); // call menu function
		InfoBar(hWnd); // call info bar function
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
	AppendMenu(ConfigMenu, MF_POPUP, 1, "Formula");
	AppendMenu(ConfigMenu, MF_POPUP, 2, "Colors");
	AppendMenu(ConfigMenu, MF_POPUP, 3, "Location");
	AppendMenu(ConfigMenu, MF_SEPARATOR, NULL, NULL);
	AppendMenu(ConfigMenu, MF_STRING, 5, "Exit");

	// Appends items to Filter menu
	AppendMenu(FilterMenu, MF_STRING, NULL, "Decolorize");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Edge detect");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Inverse edge");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Grayscale");
	AppendMenu(FilterMenu, MF_STRING, NULL, "Inverse Grayscale");

	SetMenu(hWnd, hMenu); // Sets hMenu to be added to hWnd
}

void InfoBar(HWND hWnd) // add current view information bar
{
	CreateWindowW(L"static", L"i:200", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 500, 59, 19, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"X:0.0000000000000", WS_VISIBLE | WS_BORDER | WS_CHILD, 57, 500, 132, 19, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Y:0.0000000000000", WS_VISIBLE | WS_BORDER | WS_CHILD, 188, 500, 133, 19, hWnd, NULL, NULL, NULL);
	CreateWindowW(L"static", L"Z:4", WS_VISIBLE | WS_BORDER | WS_CHILD, 320, 500, 181, 19, hWnd, NULL, NULL, NULL);
}

void FormulaMenu(HWND hWnd) // Create formula menu
{
	HWND Formula = CreateWindowW(L"static", L" Select Formula...", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 150, 200, 200, hWnd, NULL, NULL, NULL);
}

void ColorMenu(HWND hWnd) // Create color menu
{
	HWND Color = CreateWindowW(L"static", L" Choose color preset...", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 150, 200, 200, hWnd, NULL, NULL, NULL);
}

void LocationMenu(HWND hWnd) // Create location menu
{
	HWND Location = CreateWindowW(L"static", L" Set location and zoom...", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 175, 200, 150, hWnd, NULL, NULL, NULL);
}
