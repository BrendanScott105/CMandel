#include <windows.h> // Include
#include <string>

/*Window variables start*/
LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM); // Declare existence
std::wstring s2ws(const std::string& s);
void WinMenus(HWND); // Declare existence
void InfoBar(HWND); // Declare existence
void FormulaMenu(HWND); //Declare existence
void ColorMenu(HWND); //Declare existence
void LocationMenu(HWND); //Declare existence
void HelpMenu(HWND); //Decleare existence
void MouseLoc(HWND); //Decleare existence
void DestroyFormulaMenu(); //Decleare existence
void DestroyColorMenu(); //Decleare existence
void DestroyLocationMenu(); //Decleare existence
void DestroyHelpMenu(); //Decleare existence

HMENU hMenu; // define header menu

HWND Formula1, Formula2, Formula3, Formula4, Formula5, Formula6, Formula7, Formula8, Formula9; // Declare formula menu elements globally

HWND Location1, Location2, Location3, Location4, Location5, Location6, Location7, Location8; // Declare Location menu elements globally

HWND Color1, Color2, Color3, Color4, Color5, Color6, Color7, Color8, Color9; // Declare color menu elements globally

HWND HelpMenu1, HelpMenu2, HelpMenu3, HelpMenu4; // Declare help menu elements globally

BOOL FormulaOpen;
BOOL ColorOpen;
BOOL LocationOpen;
BOOL HelpOpen;

POINT Cursor;

HWND Info1;
/*Window variables end*/

int Iters = 200; // define iterations

/*######################################################
THIS IS WHERE THE WINDOW CREATION AND INTERFACING STARTS
######################################################*/

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

	CreateWindowW(L"MainWin", L"CMandel", (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME)&~WS_MAXIMIZEBOX | WS_VISIBLE, 500, 200, 500+16, 500+76, NULL, NULL, NULL, NULL); // Create window with basic params
	
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
		case 1: // Destroy other menus and create formula menu
			DestroyHelpMenu();
			DestroyLocationMenu();
			DestroyColorMenu();
			FormulaMenu(hWnd);
			break;
		case 2: // Destroy other menus and create color menu
			DestroyHelpMenu();
			DestroyLocationMenu();
			DestroyFormulaMenu();
			ColorMenu(hWnd); // Call color menu
			break;
		case 3: // Destroy other menus and create location menu
			DestroyHelpMenu();
			DestroyColorMenu();
			DestroyFormulaMenu();
			LocationMenu(hWnd); // Call location menu
			break;
		case 4: // Destroy other menus and create help menu
			DestroyLocationMenu();
			DestroyColorMenu();
			DestroyFormulaMenu();
			HelpMenu(hWnd); // Call help menu
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
	case WM_KEYDOWN:
		if (wp == VK_OEM_PLUS and Iters < 999999) // when "+" is hit
		{
			if (GetAsyncKeyState(VK_TAB) and wp == VK_OEM_PLUS) {
				Iters = Iters + 10; // increment by 10
			}
			else if (GetAsyncKeyState(VK_SHIFT) and wp == VK_OEM_PLUS) {
				Iters = Iters + 100; // by 100
			}
			else if (GetAsyncKeyState(VK_CONTROL) and wp == VK_OEM_PLUS) {
				Iters = Iters + 1000; // by 1000
			}
			else {
				Iters++; // by 1
			}
			if (Iters > 999999) { Iters = 999999; }
			std::wstring stemp = s2ws(std::to_string(Iters)); // to LPCWSTR
			HWND Info1 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 500, 59, 19, hWnd, NULL, NULL, NULL); // Change displayed value
		}
		if (wp == VK_OEM_MINUS and Iters > 0) // when "-" is hit
		{
			if (GetAsyncKeyState(VK_TAB) and wp == VK_OEM_MINUS) {
				Iters = Iters - 10; // decrement by 10
			}
			else if (GetAsyncKeyState(VK_SHIFT) and wp == VK_OEM_MINUS) {
				Iters = Iters - 100; // by 100
			}
			else if (GetAsyncKeyState(VK_CONTROL) and wp == VK_OEM_MINUS) {
				Iters = Iters - 1000; // by 1000
			}
			else {
				Iters--; // by 1
			}
			if (Iters < 0) { Iters = 0; }
			std::wstring stemp = s2ws(std::to_string(Iters)); // to LPCWSTR
			HWND Info1 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 500, 59, 19, hWnd, NULL, NULL, NULL); // Change displayed value
		}
	case WM_LBUTTONDOWN: // Left mouse button is clicked
	{
		RECT WinRect = { NULL };
		GetWindowRect(hWnd, &WinRect); // Get window position
		GetCursorPos(&Cursor); // Get cursor position
		int XWindowPosition = Cursor.x - WinRect.left - 7; // Calculate X position of cursor in the window
		int YWindowPosition = Cursor.y - WinRect.top - 50; // Calculate Y position of cursor in the window
		if (FormulaOpen == true) {  }
		if (ColorOpen == true) {  }
		if (LocationOpen == true) {  }
		if (HelpOpen == true) {  }
	}
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
	HWND Info1 = CreateWindowW(L"static", L"200", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 500, 59, 19, hWnd, NULL, NULL, NULL); // Display initially
	HWND Info2 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_BORDER | WS_CHILD, 57, 500, 132, 19, hWnd, NULL, NULL, NULL);
	HWND Info3 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_BORDER | WS_CHILD, 188, 500, 133, 19, hWnd, NULL, NULL, NULL);
	HWND Info4 = CreateWindowW(L"static", L"4", WS_VISIBLE | WS_BORDER | WS_CHILD, 320, 500, 181, 19, hWnd, NULL, NULL, NULL);
}

void FormulaMenu(HWND hWnd) // Create formula menu
{
	Formula1 = CreateWindowW(L"static", L" Select Formula...\n\n\n\n\n             Mirror screen space\n\n             Julia set variant\n             [Position modifies C]", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 150, 200, 200, hWnd, NULL, NULL, NULL);
	Formula2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 170, 200, 1, hWnd, NULL, NULL, NULL);
	Formula3 = CreateWindowW(L"static", L"Mandelbrot set", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 190, 140, 20, hWnd, NULL, NULL, NULL);
	Formula4 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 190, 20, 20, hWnd, NULL, NULL, NULL);
	Formula5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 180, 234, 10, 10, hWnd, NULL, NULL, NULL);
	Formula6 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 180, 266, 10, 10, hWnd, NULL, NULL, NULL);
	Formula7 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 320, 80, 20, hWnd, NULL, NULL, NULL);
	Formula8 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 320, 80, 20, hWnd, NULL, NULL, NULL);
	Formula9 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 152, 17, 17, hWnd, NULL, NULL, NULL);
	FormulaOpen = true;
}

void ColorMenu(HWND hWnd) // Create color menu
{
	Color1 = CreateWindowW(L"static", L" Choose color preset...\n\n\n\n\n             Smooth coloring\n\n             Color Preview", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 150, 200, 200, hWnd, NULL, NULL, NULL);
	Color2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 170, 200, 1, hWnd, NULL, NULL, NULL);
	Color3 = CreateWindowW(L"static", L"Default colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 190, 140, 20, hWnd, NULL, NULL, NULL);
	Color4 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 190, 20, 20, hWnd, NULL, NULL, NULL);
	Color5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 180, 234, 10, 10, hWnd, NULL, NULL, NULL);
	Color6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 320, 80, 20, hWnd, NULL, NULL, NULL);
	Color7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 320, 80, 20, hWnd, NULL, NULL, NULL);
	Color8 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 285, 180, 20, hWnd, NULL, NULL, NULL);
	Color9 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 152, 17, 17, hWnd, NULL, NULL, NULL);
	ColorOpen = true;
}

void LocationMenu(HWND hWnd) // Create location menu and create textboxes
{
	Location1 = CreateWindowW(L"static", L" Set location and zoom...", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 175, 200, 150, hWnd, NULL, NULL, NULL);
	Location2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 195, 200, 1, hWnd, NULL, NULL, NULL);
	Location3 = CreateWindowW(L"edit", L"Real position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 205, 180, 20, hWnd, NULL, NULL, NULL);
	Location4 = CreateWindowW(L"edit", L"Imaginary position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 235, 180, 20, hWnd, NULL, NULL, NULL);
	Location5 = CreateWindowW(L"edit", L"Zoom level", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 265, 180, 20, hWnd, NULL, NULL, NULL);
	Location6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 295, 80, 20, hWnd, NULL, NULL, NULL);
	Location7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 295, 80, 20, hWnd, NULL, NULL, NULL);
	Location8 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 177, 17, 17, hWnd, NULL, NULL, NULL);
	LocationOpen = true;
}

void HelpMenu(HWND hWnd) // Create help menu
{
	HelpMenu1 = CreateWindowW(L"static", L" About CMandel...    © 2021, Brendan Scott\n\n This is open source software :\n Github.com/BrendanScott105/CMandel\n\n Controls :\n W / A / S / D : Up / Left / Down / Right\n Q / E : CCW / CW rotate\n Mouse left : Zoom in\n Mouse right : Zoom out\n - / + : Increase / Decrease iterations\n [Tab - 10 | Shift - 100 | Control - 1000]\n\n Info bar :\n 1 - Iters | 2 - Real | 3 - Imaginary | 4 - Zoom\n\n Limitations :\n - Iterations does not exceed 999999\n - Zoom limited to 2^64\n - Precision limited to 64 Bits\n - Resolution locked at 500x500", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 80, 300, 340, hWnd, NULL, NULL, NULL);
	HelpMenu2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 100, 300, 1, hWnd, NULL, NULL, NULL);
	HelpMenu3 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 381, 82, 17, 17, hWnd, NULL, NULL, NULL);
	HelpMenu4 = CreateWindowW(L"static", L"Ok", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 315, 395, 80, 20, hWnd, NULL, NULL, NULL);
	HelpOpen = true;
}

std::wstring s2ws(const std::string& s) // CONVERT STRING TO LPCWSTR
{
	int len;
	int slength = (int)s.length() + 1;
	len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, 0, 0);
	wchar_t* buf = new wchar_t[len];
	MultiByteToWideChar(CP_ACP, 0, s.c_str(), slength, buf, len);
	std::wstring r(buf);
	delete[] buf;
	return r;
}

void DestroyFormulaMenu()
{
	DestroyWindow(Formula1);
	DestroyWindow(Formula2);
	DestroyWindow(Formula3);
	DestroyWindow(Formula4);
	DestroyWindow(Formula5);
	DestroyWindow(Formula6);
	DestroyWindow(Formula7);
	DestroyWindow(Formula8);
	DestroyWindow(Formula9);
	FormulaOpen = false;
}

void DestroyColorMenu()
{
	DestroyWindow(Color1);
	DestroyWindow(Color2);
	DestroyWindow(Color3);
	DestroyWindow(Color4);
	DestroyWindow(Color5);
	DestroyWindow(Color6);
	DestroyWindow(Color7);
	DestroyWindow(Color8);
	DestroyWindow(Color9);
	ColorOpen = false;
}

void DestroyLocationMenu()
{
	DestroyWindow(Location1);
	DestroyWindow(Location2);
	DestroyWindow(Location3);
	DestroyWindow(Location4);
	DestroyWindow(Location5);
	DestroyWindow(Location6);
	DestroyWindow(Location7);
	DestroyWindow(Location8);
	LocationOpen = false;
}

void DestroyHelpMenu()
{
	DestroyWindow(HelpMenu1);
	DestroyWindow(HelpMenu2);
	DestroyWindow(HelpMenu3);
	DestroyWindow(HelpMenu4);
	HelpOpen = false;
}
