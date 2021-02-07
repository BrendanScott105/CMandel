#include <windows.h> // Include
#include <string>

/*Window variables start*/
LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM); // Declare existence
std::wstring s2ws(const std::string& s);
void WinMenus(HWND); // Declare existence
void TitleBar(HWND); // Declare existence
void InfoBar(HWND); // Declare existence
void FormulaMenu(HWND); //Declare existence
void ColorMenu(HWND); //Declare existence
void LocationMenu(HWND); //Declare existence
void HelpMenu(HWND); //Decleare existence
void MouseLoc(HWND); //Decleare existence
void LinkBox(HWND); // Declare existence
void ConfigDrop(HWND); // Declare existence
void DestroyFormulaMenu(); //Decleare existence
void DestroyColorMenu(); //Decleare existence
void DestroyLocationMenu(); //Decleare existence
void DestroyHelpMenu(); //Decleare existence
void DestroyLinkNotif(); //Declare existence
void DestroyConfigDrop(HWND); //Declare existence
void DestroyAll(HWND); //Declare existence

//HMENU hMenu; // define header menu

HWND Formula1, Formula2, Formula3, Formula4, Formula5, Formula6, Formula7, Formula8, Formula9; // Declare formula menu elements globally

HWND Location1, Location2, Location3, Location4, Location5, Location6, Location7, Location8; // Declare Location menu elements globally

HWND Color1, Color2, Color3, Color4, Color5, Color6, Color7, Color8, Color9; // Declare color menu elements globally

HWND HelpMenu1, HelpMenu2, HelpMenu3, HelpMenu4, HelpMenu5, HelpMenu6; // Declare help menu elements globally

HWND Top1, Top2, Top3, Top4, Top5, Top6, Top7, Top8, Top9, Top0; // Declare top level menu elements globally
HWND Top1a, Top2a, Top3a, Top4a, Top5a, Top6a, Top7a, Top8a, Top9a;

HWND Info1, Info2, Info3, Info4; // Declare info elements globally

HWND Link1, Link2, Link3; // Declare link notif elements globally

BOOL FormulaOpen;
BOOL ColorOpen;
BOOL LocationOpen;
BOOL HelpOpen;
BOOL LinkNotif;
BOOL ConfigureDrop;

POINT Cursor;

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

	CreateWindowW(L"MainWin", L"CMandel", (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME)&~WS_MAXIMIZEBOX&~WS_CAPTION | WS_VISIBLE | WS_BORDER | WS_POPUP, 500, 200, 502, 540, NULL, NULL, NULL, NULL); // Create window with basic params
	
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
	case WM_CREATE: // when window is created
		//WinMenus(hWnd); // call menu function
		InfoBar(hWnd); // call info bar function
		TitleBar(hWnd); // Call title bar function
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
			DestroyWindow(Info1);
			HWND Info1 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 520, 59, 19, hWnd, NULL, NULL, NULL); // Change displayed value
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
			DestroyWindow(Info1);
			HWND Info1 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 520, 59, 19, hWnd, NULL, NULL, NULL); // Change displayed value
		}
	case WM_LBUTTONDOWN: // Left mouse button is clicked
	{
		RECT WinRect = { NULL };
		GetWindowRect(hWnd, &WinRect); // Get window position
		GetCursorPos(&Cursor); // Get cursor position
		int XWindowPosition = Cursor.x - WinRect.left; // Calculate X position of cursor in the window
		int YWindowPosition = Cursor.y - WinRect.top-20; // Calculate Y position of cursor in the window
		std::wstring stemp = s2ws(std::to_string(XWindowPosition)); // to LPCWSTR
		std::wstring stemp2 = s2ws(std::to_string(YWindowPosition)); // to LPCWSTR
		HWND Info2 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, 57, 520, 132, 19, hWnd, NULL, NULL, NULL);
		HWND Info3 = CreateWindowW(L"static", stemp2.c_str(), WS_VISIBLE | WS_BORDER | WS_CHILD, 188, 520, 133, 19, hWnd, NULL, NULL, NULL);
		if (((XWindowPosition > 155) and (XWindowPosition < 447)) and ((YWindowPosition > -19) and (YWindowPosition < -2))) // Enable window dragging
		{
			while (DragDetect(hWnd, Cursor)) {
				GetCursorPos(&Cursor); // Get cursor position
				MoveWindow(hWnd, Cursor.x - XWindowPosition, Cursor.y - YWindowPosition - 20, 502, 540, TRUE);
			}
		}
		if (ConfigureDrop == TRUE) {
			if (((XWindowPosition > 72) and (XWindowPosition < 85)) and ((YWindowPosition > -18) and (YWindowPosition < -3))) { DestroyConfigDrop(hWnd); break; } // Destroy configure dropdown menu
		}
		if (ConfigureDrop == FALSE) {
			if (((XWindowPosition > 72) and (XWindowPosition < 85)) and ((YWindowPosition > -18) and (YWindowPosition < -3))) { ConfigDrop(hWnd); break; } // Trigger open configure dropdown
		}
		if (FormulaOpen == TRUE) {  }
		if (ColorOpen == TRUE) {  }
		if (LocationOpen == TRUE) {  }
		if (HelpOpen == TRUE) {
			if (((XWindowPosition > 358) and (XWindowPosition < 375) and ((YWindowPosition > 130) and (YWindowPosition < 145)))) { ShellExecute(NULL, NULL, "https://github.com/BrendanScott105/CMandel", NULL, NULL, SW_SHOWNORMAL); LinkBox(hWnd); } // Open URL in browser
			if (((XWindowPosition > 318) and (XWindowPosition < 396) and ((YWindowPosition > 397) and (YWindowPosition < 415)))) { DestroyAll(hWnd); } // Destroy help menu from OK
			if (((XWindowPosition > 383) and (XWindowPosition < 398) and ((YWindowPosition > 83) and (YWindowPosition < 98)))) { DestroyAll(hWnd); } // Destroy help menu from X
			break;
		}
		if (LinkNotif == TRUE) {
			if (((XWindowPosition > 152) and (XWindowPosition < 166) and ((YWindowPosition > 453) and (YWindowPosition < 467)))) { DestroyLinkNotif(); break; }
		}
		if (((XWindowPosition > 484) and (XWindowPosition < 499)) and ((YWindowPosition > -18) and (YWindowPosition < -3))) { exit(0); break; } // Close application button
		if (((XWindowPosition > 467) and (XWindowPosition < 482)) and ((YWindowPosition > -18) and (YWindowPosition < -3))) { ShowWindow(hWnd, SW_MINIMIZE); break; } // Minimize window button
		if (((XWindowPosition > 450) and (XWindowPosition < 466)) and ((YWindowPosition > -18) and (YWindowPosition < -3))) // Help button
		{
			DestroyAll(hWnd);
			HelpMenu(hWnd); // Call help menu
			break;
		}
	}
	default: // default case for all others
		return DefWindowProcW(hWnd, defmsg, wp, lp); // return
	}
}
void InfoBar(HWND hWnd) // add current view information bar
{
	Info1 = CreateWindowW(L"static", L"200", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 520, 59, 19, hWnd, NULL, NULL, NULL); // Display initially
	Info2 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_BORDER | WS_CHILD, 57, 520, 132, 19, hWnd, NULL, NULL, NULL);
	Info3 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_BORDER | WS_CHILD, 188, 520, 133, 19, hWnd, NULL, NULL, NULL);
	Info4 = CreateWindowW(L"static", L"4", WS_VISIBLE | WS_BORDER | WS_CHILD, 320, 520, 181, 19, hWnd, NULL, NULL, NULL);
}

void TitleBar(HWND hWnd) // Create title bar
{
	Top1 = CreateWindowW(L"static", L" CMandel 0.22", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, -1, -1, 502, 20, hWnd, NULL, NULL, NULL); // Display initially
	Top2 = CreateWindowW(L"static", L" Configure", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, -1, 89, 20, hWnd, NULL, NULL, NULL);
	Top3 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 70, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top4 = CreateWindowW(L"static", L" Filters", WS_VISIBLE | WS_BORDER | WS_CHILD, 87, -1, 67, 20, hWnd, NULL, NULL, NULL);
	Top5 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 136, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top6 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 483, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top7 = CreateWindowW(L"static", L"⎽⎽", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 466, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top8 = CreateWindowW(L"static", L"?", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 449, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top9 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 470, 12, 8, 2, hWnd, NULL, NULL, NULL);
	Top0 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 447, -1, 1, 20, hWnd, NULL, NULL, NULL);
}

void FormulaMenu(HWND hWnd) // Create formula menu
{
	Formula1 = CreateWindowW(L"static", L" Select Formula...\n\n\n\n\n             Mirror screen space\n\n             Julia set variant\n             [Position modifies C]", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 150, 200, 200, hWnd, NULL, NULL, NULL);
	Formula2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 190, 200, 1, Formula1, NULL, NULL, NULL);
	Formula3 = CreateWindowW(L"static", L"Mandelbrot set", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 210, 140, 20, Formula1, NULL, NULL, NULL);
	Formula4 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, Formula1, NULL, NULL, NULL);
	Formula5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 180, 254, 10, 10, Formula1, NULL, NULL, NULL);
	Formula6 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 180, 286, 10, 10, Formula1, NULL, NULL, NULL);
	Formula7 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 340, 80, 20, Formula1, NULL, NULL, NULL);
	Formula8 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 340, 80, 20, Formula1, NULL, NULL, NULL);
	Formula9 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 172, 17, 17, Formula1, NULL, NULL, NULL);
	FormulaOpen = TRUE;
}

void ColorMenu(HWND hWnd) // Create color menu
{
	Color1 = CreateWindowW(L"static", L" Choose color preset...\n\n\n\n\n             Smooth coloring\n\n             Color Preview", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 150, 200, 200, hWnd, NULL, NULL, NULL);
	Color2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 190, 200, 1, hWnd, NULL, NULL, NULL);
	Color3 = CreateWindowW(L"static", L"Default colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 210, 140, 20, hWnd, NULL, NULL, NULL);
	Color4 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	Color5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 180, 254, 10, 10, hWnd, NULL, NULL, NULL);
	Color6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 340, 80, 20, hWnd, NULL, NULL, NULL);
	Color7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 340, 80, 20, hWnd, NULL, NULL, NULL);
	Color8 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 305, 180, 20, hWnd, NULL, NULL, NULL);
	Color9 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 172, 17, 17, hWnd, NULL, NULL, NULL);
	ColorOpen = TRUE;
}

void LocationMenu(HWND hWnd) // Create location menu and create textboxes
{
	Location1 = CreateWindowW(L"static", L" Set location and zoom...", WS_VISIBLE | WS_BORDER | WS_CHILD , 150, 195, 200, 150, hWnd, NULL, NULL, NULL);
	Location2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 215, 200, 1, hWnd, NULL, NULL, NULL);
	Location3 = CreateWindowW(L"edit", L"Real position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 225, 180, 20, hWnd, NULL, NULL, NULL);
	Location4 = CreateWindowW(L"edit", L"Imaginary position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 255, 180, 20, hWnd, NULL, NULL, NULL);
	Location5 = CreateWindowW(L"edit", L"Zoom level", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 285, 180, 20, hWnd, NULL, NULL, NULL);
	Location6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 315, 80, 20, hWnd, NULL, NULL, NULL);
	Location7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 315, 80, 20, hWnd, NULL, NULL, NULL);
	Location8 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 197, 17, 17, hWnd, NULL, NULL, NULL);
	LocationOpen = TRUE;
}

void HelpMenu(HWND hWnd) // Create help menu
{
	HelpMenu1 = CreateWindowW(L"static", L" About CMandel....   © 2021, Brendan Scott\n\n This is open source software :\n Github.com/BrendanScott105/CMandel\n\n Controls :\n W / A / S / D : Up / Left / Down / Right\n Q / E : CCW / CW rotate\n Mouse left : Zoom in\n Mouse right : Zoom out\n - / + : Increase / Decrease iterations\n [Tab - 10 | Shift - 100 | Control - 1000]\n\n Info bar :\n 1 - Iters | 2 - Real | 3 - Imaginary | 4 - Zoom\n\n Limitations :\n - Iterations does not exceed 999999\n - Zoom limited to 2^64\n - Precision limited to 64 Bits\n - Resolution locked at 500x500", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 100, 300, 340, hWnd, NULL, NULL, NULL);
	HelpMenu2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 19, 300, 1, HelpMenu1, NULL, NULL, NULL);
	HelpMenu3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 278, 0, 1, 20, HelpMenu1, NULL, NULL, NULL);
	HelpMenu4 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 280, 1, 17, 17, HelpMenu1, NULL, NULL, NULL);
	HelpMenu5 = CreateWindowW(L"static", L"Ok", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 215, 315, 80, 20, HelpMenu1, NULL, NULL, NULL);
	HelpMenu6 = CreateWindowW(L"static", L"🡭", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 256, 48, 17, 17, HelpMenu1, NULL, NULL, NULL);
	HelpOpen = TRUE;
}

void LinkBox(HWND hWnd) // Create link notif box
{
	Link1 = CreateWindowW(L"static", L"Link opened in browser tab ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_RIGHT, 148, 470, 204, 20, hWnd, NULL, NULL, NULL);
	Link2 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 150, 472, 16, 16, hWnd, NULL, NULL, NULL);
	Link3 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 167, 470, 1, 20, hWnd, NULL, NULL, NULL);
	LinkNotif = TRUE;
}

void ConfigDrop(HWND hWnd) // Create configure dropdown
{
	DestroyWindow(Top3);
	Top1a = CreateWindowW(L"static", L"▲", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 70, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top2a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 18, 89, 77, hWnd, NULL, NULL, NULL);
	Top3a = CreateWindowW(L"static", L" Formula", WS_VISIBLE | WS_CHILD, -1, 19, 88, 20, hWnd, NULL, NULL, NULL);
	Top4a = CreateWindowW(L"static", L" Colors", WS_VISIBLE | WS_CHILD, -1, 38, 88, 20, hWnd, NULL, NULL, NULL);
	Top5a = CreateWindowW(L"static", L" Location", WS_VISIBLE | WS_CHILD, -1, 57, 88, 20, hWnd, NULL, NULL, NULL);
	Top6a = CreateWindowW(L"static", L" Exit", WS_VISIBLE | WS_CHILD, -1, 77, 88, 17, hWnd, NULL, NULL, NULL);
	Top7a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 1, 38, 84, 1, hWnd, NULL, NULL, NULL);
	Top8a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 1, 57, 84, 1, hWnd, NULL, NULL, NULL);
	Top9a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, -1, 74, 88, 3, hWnd, NULL, NULL, NULL);
	ConfigureDrop = TRUE;
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

void DestroyFormulaMenu() // Destroy formula menu
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
	FormulaOpen = FALSE;
}

void DestroyColorMenu() // Destroy color menu
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
	ColorOpen = FALSE;
}

void DestroyLocationMenu() // Destroy location menu
{
	DestroyWindow(Location1);
	DestroyWindow(Location2);
	DestroyWindow(Location3);
	DestroyWindow(Location4);
	DestroyWindow(Location5);
	DestroyWindow(Location6);
	DestroyWindow(Location7);
	DestroyWindow(Location8);
	LocationOpen = FALSE;
}

void DestroyHelpMenu() // Destroy help menu
{
	DestroyWindow(HelpMenu1);
	DestroyWindow(HelpMenu2);
	DestroyWindow(HelpMenu3);
	DestroyWindow(HelpMenu4);
	HelpOpen = FALSE;
}

void DestroyLinkNotif() // Destroy link notif
{
	DestroyWindow(Link1);
	DestroyWindow(Link2);
	DestroyWindow(Link3);
	LinkNotif = FALSE;
}

void DestroyConfigDrop(HWND hWnd) // Destroy configuration dropdown menu
{
	DestroyWindow(Top1a);
	DestroyWindow(Top2a);
	DestroyWindow(Top3a);
	DestroyWindow(Top4a);
	DestroyWindow(Top5a);
	DestroyWindow(Top6a);
	DestroyWindow(Top7a);
	DestroyWindow(Top8a);
	DestroyWindow(Top9a);
	Top3 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 70, 1, 16, 16, hWnd, NULL, NULL, NULL);
	ConfigureDrop = FALSE;
}

void DestroyAll(HWND hWnd) // Destroy all menus
{
	DestroyFormulaMenu();
	DestroyColorMenu();
	DestroyLocationMenu();
	DestroyHelpMenu();
	DestroyLinkNotif();
	DestroyConfigDrop(hWnd);
}
