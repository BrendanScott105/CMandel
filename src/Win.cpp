#include <windows.h> // Include
#include <gdiplus.h>
#include <string>
#include <thread>

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
void FilterDrop(HWND); //Declare existence
void ConfigDrop(HWND); // Declare existence
void IncorrectNumBox(HWND); // Declare existence
void FractDropdown(HWND); // Declare existence
void ColorDropdown(HWND); // Declare existence
void DestroyFormulaMenu(); //Decleare existence
void DestroyColorMenu(); //Decleare existence
void DestroyLocationMenu(); //Decleare existence
void DestroyHelpMenu(); //Decleare existence
void DestroyLinkNotif(); //Declare existence
void DestroyConfigDrop(HWND); //Declare existence
void DestroyIncorrectNumberNotif(); //Declare existence
void DestroyFiltersDrop(HWND); //Declare existence
void DestroyFractDropdown(HWND); // Declare existence
void DestroyColorDropdown(HWND); // Declare existence
void DestroyAll(HWND); //Declare existence

HMENU hMenu; // define header menu

HWND Formula1, Formula2, Formula3, Formula4, Formula5, Formula6, Formula7, Formula8, Formula9; // Declare formula menu elements globally

HWND Location1, Location2, Location3, Location4, Location5, Location6, Location7, Location8; // Declare Location menu elements globally

HWND Color1, Color2, Color3, Color4, Color5, Color6, Color7, Color8; // Declare color menu elements globally

HWND HelpMenu1, HelpMenu2, HelpMenu3, HelpMenu4, HelpMenu5, HelpMenu6, HelpMenu7; // Declare help menu elements globally

HWND Top1, Top2, Top3, Top4, Top5, Top6, Top7, Top8, Top9, Top0; // Declare top level menu elements globally
HWND Top1a, Top2a, Top3a, Top4a, Top5a, Top6a, Top7a, Top8a, Top9a;
HWND Top1b, Top2b, Top3b, Top4b, Top5b, Top6b, Top7b, Top8b, Top9b, Top0b, TopAb, TopBb, TopCb, TopDb, TopEb, TopFb;

HWND Info0a, Info0, Info1a, Info1, Info2a, Info2, Info3a, Info3, Info4a, Info4, Info5a, Info5, Info6a, Info6, Info7a, Info7, Info8a, Info8, Info9a, Info9; // Declare info elements globally

HWND Link1, Link2, Link3; // Declare link notif elements globally

HWND IN1, IN2, IN3; // Declare Incorrect Number notif elements globally

HWND FDdrop1, FDdrop2, FDdrop3, FDdrop4, FDdrop5, FDdrop6, FDdrop7, FDdrop8, FDdrop9, FDdropA, FDdropB, FDdropC; // Declare fractal dropdown elements globally
HWND CDdrop1, CDdrop2, CDdrop3, CDdrop4, CDdrop5, CDdrop6, CDdrop7, CDdrop8; // Declare color dropdown elements globally

HWND RealWinMain; // Declare main window

BOOL FormulaOpen;
BOOL ColorOpen;
BOOL LocationOpen;
BOOL HelpOpen;
BOOL LinkNotif;
BOOL ConfigureDrop;
BOOL FiltersDrop;
BOOL IncorrectNumberNotif;
BOOL FractDrop = FALSE;
BOOL ColorDrop = FALSE;
BOOL SmoothColor = FALSE;

POINT Cursor;

Gdiplus::GdiplusStartupInput gdiStart;
ULONG_PTR GdiToken;

BOOL ScreenMirror = FALSE;
BOOL JuliaMode = FALSE;
INT FractalType = 1;
INT ColorType = 0;
/*Window variables end*/

/*Fractal variable definitions start*/
int Iters = 200; // define iterations
BOOL Filters[5] = { FALSE,FALSE,FALSE,FALSE,FALSE }; // Decolorize, Edge detect, Inverse edge, Grayscale, Inverse Grayscale
double NewReal = 0; double NewImag = 0; unsigned long long NewZoom = 0;
INT RealFractalType = 1;
/*Fractal variables end*/

/*######################################################
THIS IS WHERE THE WINDOW CREATION AND INTERFACING STARTS
######################################################*/

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR args, int ncmdshow) // Enter
{
	WNDCLASSW win = { 0 }; // win class

	win.hbrBackground = (HBRUSH)COLOR_WINDOW; // background
	win.hCursor = LoadCursor(NULL, IDC_ARROW); // Cursor
	win.hInstance = hInst;
	win.lpszClassName = L"MainWin"; // define window class name
	win.lpfnWndProc = Proc; // Set procedure name

	if (!RegisterClassW(&win)) // Register win class
		return -1;

	RealWinMain = CreateWindowW(L"MainWin", L"CMandel", (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_MAXIMIZEBOX & ~WS_CAPTION | WS_VISIBLE | WS_BORDER | WS_POPUP, 500, 200, 502, 558, NULL, NULL, NULL, NULL); // Create window with basic params

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
	HDC hdc;
	PAINTSTRUCT ps;
	switch (defmsg)
	{
	case WM_CREATE: // when window is created
		InfoBar(hWnd); // call info bar function
		TitleBar(hWnd); // Call title bar function
		break;
	case WM_PAINT:
		Gdiplus::GdiplusStartup(&GdiToken, &gdiStart, nullptr);
		hdc = BeginPaint(hWnd, &ps);
		// Call main render function here
		EndPaint(hWnd, &ps);
		return 0;
	case WM_DESTROY: // when close is hit
		Gdiplus::GdiplusShutdown(GdiToken);
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
			HWND Info1 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_CHILD, 73, 521, 48, 17, hWnd, NULL, NULL, NULL); // Change displayed value
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
			HWND Info1 = CreateWindowW(L"static", stemp.c_str(), WS_VISIBLE | WS_CHILD, 73, 521, 48, 17, hWnd, NULL, NULL, NULL); // Change displayed value
		}
	case WM_LBUTTONDOWN: // Left mouse button is clicked
	{
		RECT WinRect = { NULL };
		GetWindowRect(hWnd, &WinRect); // Get window position
		GetCursorPos(&Cursor); // Get cursor position
		int XWindowPosition = Cursor.x - WinRect.left; // Calculate X position of cursor in the window
		int YWindowPosition = Cursor.y - WinRect.top - 20; // Calculate Y position of cursor in the window
		if (((XWindowPosition > 155) and (XWindowPosition < 448)) and ((YWindowPosition > -19) and (YWindowPosition < -3))) // Enable window dragging
		{
			while (DragDetect(hWnd, Cursor)) {
				GetCursorPos(&Cursor); // Get cursor position
				MoveWindow(hWnd, Cursor.x - XWindowPosition, Cursor.y - YWindowPosition - 20, 502, 558, TRUE);
				UpdateWindow(hWnd);
			}
		}
		if (FiltersDrop == TRUE) { // When filters menu is open
			if (((XWindowPosition > 139) and (XWindowPosition < 153)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyFiltersDrop(hWnd); break; } // Destroy filters dropdown
			if (((XWindowPosition > 5) and (XWindowPosition < 16)) and ((YWindowPosition > 3) and (YWindowPosition < 14))) { // If decolorize option is selected
				if (Filters[0] == FALSE) { // if decolorize is false
					Filters[0] = TRUE; // make true
					Filters[1] = FALSE; Filters[2] = FALSE; Filters[3] = FALSE; Filters[4] = FALSE; // make others false
					DestroyFiltersDrop(hWnd);
					FilterDrop(hWnd); // rerender
				}
				else { Filters[0] = FALSE; DestroyFiltersDrop(hWnd); FilterDrop(hWnd); } // if true, make false, and rerender
			}
			if (((XWindowPosition > 5) and (XWindowPosition < 16)) and ((YWindowPosition > 22) and (YWindowPosition < 33))) { // If edge detect option is selected
				if (Filters[1] == FALSE) { // if edge detection is false
					Filters[1] = TRUE; // make true
					Filters[0] = FALSE; Filters[2] = FALSE; Filters[3] = FALSE; Filters[4] = FALSE; // make others false
					DestroyFiltersDrop(hWnd);
					FilterDrop(hWnd); // rerender
				}
				else { Filters[1] = FALSE; DestroyFiltersDrop(hWnd); FilterDrop(hWnd); } // if true, make false, and rerender
			}
			if (((XWindowPosition > 5) and (XWindowPosition < 16)) and ((YWindowPosition > 41) and (YWindowPosition < 52))) { // If inverse edge detect option is selected
				if (Filters[2] == FALSE) { // if inverse edge detection is false
					Filters[2] = TRUE; // make true
					Filters[0] = FALSE; Filters[1] = FALSE; Filters[3] = FALSE; Filters[4] = FALSE; // make others false
					DestroyFiltersDrop(hWnd);
					FilterDrop(hWnd); // rerender
				}
				else { Filters[2] = FALSE; DestroyFiltersDrop(hWnd); FilterDrop(hWnd); } // if true, make false, and rerender
			}
			if (((XWindowPosition > 5) and (XWindowPosition < 16)) and ((YWindowPosition > 60) and (YWindowPosition < 71))) { // If grayscale option is selected
				if (Filters[3] == FALSE) { // if grayscale is false
					Filters[3] = TRUE; // make true
					Filters[0] = FALSE; Filters[1] = FALSE; Filters[2] = FALSE; Filters[4] = FALSE; // make others false
					DestroyFiltersDrop(hWnd);
					FilterDrop(hWnd); // rerender
				}
				else { Filters[3] = FALSE; DestroyFiltersDrop(hWnd); FilterDrop(hWnd); } // if true, make false, and rerender
			}
			if (((XWindowPosition > 5) and (XWindowPosition < 16)) and ((YWindowPosition > 79) and (YWindowPosition < 90))) { // If inverse grayscale option is selected
				if (Filters[4] == FALSE) { // if inverse grayscale is false
					Filters[4] = TRUE; // make true
					Filters[0] = FALSE; Filters[1] = FALSE; Filters[2] = FALSE; Filters[3] = FALSE; // make others false
					DestroyFiltersDrop(hWnd);
					FilterDrop(hWnd); // rerender
				}
				else { Filters[4] = FALSE; DestroyFiltersDrop(hWnd); FilterDrop(hWnd); } // if true, make false, and rerender
			}
		}
		if (FiltersDrop == FALSE) {
			if (((XWindowPosition > 139) and (XWindowPosition < 153)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyConfigDrop(hWnd); FilterDrop(hWnd); break; } // Trigger open filter dropdown
		}
		if (ConfigureDrop == TRUE) { // When configure menu is open
			if (((XWindowPosition > 73) and (XWindowPosition < 86)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyConfigDrop(hWnd); break; } // Destroy configure dropdown menu
			if (((XWindowPosition > 0) and (XWindowPosition < 89)) and ((YWindowPosition > -1) and (YWindowPosition < 19))) { DestroyAll(hWnd); FormulaMenu(hWnd); } // Destroy other menus and open formula menu
			if (((XWindowPosition > 0) and (XWindowPosition < 89)) and ((YWindowPosition > 19) and (YWindowPosition < 38))) { DestroyAll(hWnd); ColorMenu(hWnd); } // Destroy other menus and open color menu
			if (((XWindowPosition > 0) and (XWindowPosition < 89)) and ((YWindowPosition > 38) and (YWindowPosition < 55))) { DestroyAll(hWnd); LocationMenu(hWnd); } // Destroy other menus and open location menu
			if (((XWindowPosition > 0) and (XWindowPosition < 89)) and ((YWindowPosition > 57) and (YWindowPosition < 75))) { DestroyAll(hWnd); exit(0); } // Destroy other menus and exit
		}
		if (ConfigureDrop == FALSE) {
			if (((XWindowPosition > 71) and (XWindowPosition < 86)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyFiltersDrop(hWnd); ConfigDrop(hWnd); break; } // Trigger open configure dropdown
		}
		if (FormulaOpen == TRUE) { // While formula menu open
			if ((((XWindowPosition > 181) and (XWindowPosition < 190)) and ((YWindowPosition > 235) and (YWindowPosition < 244))) && FractDrop == FALSE) {
				if (ScreenMirror == FALSE) {
					ScreenMirror = TRUE;
					DestroyAll(hWnd);
					FormulaMenu(hWnd);
				}
				else { ScreenMirror = FALSE; DestroyAll(hWnd); FormulaMenu(hWnd); } // if true, make false, and rerender
			}
			if ((((XWindowPosition > 181) and (XWindowPosition < 190)) and ((YWindowPosition > 267) and (YWindowPosition < 276))) && FractDrop == FALSE) {
				if (JuliaMode == FALSE) {
					JuliaMode = TRUE;
					DestroyAll(hWnd);
					FormulaMenu(hWnd);
				}
				else { JuliaMode = FALSE; DestroyAll(hWnd); FormulaMenu(hWnd); } // if true, make false, and rerender
			}
			if ((((XWindowPosition > 261) and (XWindowPosition < 340)) and ((YWindowPosition > 321) and (YWindowPosition < 340))) && FractDrop == FALSE) { DestroyAll(hWnd); } // if Cancel button is hit
			if (((XWindowPosition > 332) and (XWindowPosition < 348)) and ((YWindowPosition > 153) and (YWindowPosition < 169))) { DestroyAll(hWnd); } // if X button is hit
			if ((((XWindowPosition > 161) and (XWindowPosition < 240)) and ((YWindowPosition > 321) and (YWindowPosition < 340))) && FractDrop == FALSE) { // if Apply button is hit
				RealFractalType = FractalType;
				std::wstring stemp3 = s2ws(std::to_string(RealFractalType)); // to LPCWSTR
				SetWindowTextW(Info9, stemp3.c_str());
				DestroyAll(hWnd);
			}
			if (FractDrop == FALSE) { // If dropdown menu is not open
				if (((XWindowPosition > 311) and (XWindowPosition < 330)) and ((YWindowPosition > 191) and (YWindowPosition < 210))) { FractDropdown(hWnd); break; }
			}
			if (FractDrop == TRUE) { // If dropdown menu is open
				if (((XWindowPosition > 311) and (XWindowPosition < 330)) and ((YWindowPosition > 191) and (YWindowPosition < 210))) { DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 211) and (YWindowPosition < 229))) { FractalType = 1; SetWindowTextW(Formula3, L"Mandelbrot set"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 229) and (YWindowPosition < 248))) { FractalType = 2; SetWindowTextW(Formula3, L"Burning ship"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 248) and (YWindowPosition < 267))) { FractalType = 3; SetWindowTextW(Formula3, L"Buffalo"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 267) and (YWindowPosition < 286))) { FractalType = 4; SetWindowTextW(Formula3, L"Celtic"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 286) and (YWindowPosition < 305))) { FractalType = 5; SetWindowTextW(Formula3, L"Mandelbar"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 305) and (YWindowPosition < 324))) { FractalType = 6; SetWindowTextW(Formula3, L"Mandelbar Celtic"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 324) and (YWindowPosition < 343))) { FractalType = 7; SetWindowTextW(Formula3, L"Perp. Mandelbrot"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 343) and (YWindowPosition < 362))) { FractalType = 8; SetWindowTextW(Formula3, L"Perp. Burning ship"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 362) and (YWindowPosition < 381))) { FractalType = 9; SetWindowTextW(Formula3, L"Perp. Buffalo"); DestroyFractDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 381) and (YWindowPosition < 400))) { FractalType = 10; SetWindowTextW(Formula3, L"Perp. Celtic"); DestroyFractDropdown(hWnd); }
			}
		}
		if (ColorOpen == TRUE) {
			if ((((XWindowPosition > 181) and (XWindowPosition < 190)) and ((YWindowPosition > 235) and (YWindowPosition < 244)))) {
				if (SmoothColor == FALSE) {
					SmoothColor = TRUE;
					DestroyAll(hWnd);
					ColorMenu(hWnd);
				}
				else { SmoothColor = FALSE; DestroyAll(hWnd); ColorMenu(hWnd); } // if true, make false, and rerender
			}
			if ((((XWindowPosition > 161) and (XWindowPosition < 240)) and ((YWindowPosition > 321) and (YWindowPosition < 340))) && ColorDrop == FALSE) { // if Apply button is hit
				std::wstring stemp4 = s2ws(std::to_string(ColorType)); // to LPCWSTR
				if (ColorType == 0) {
					SetWindowTextW(Info8, L"D");
				} else {
					SetWindowTextW(Info8, stemp4.c_str());
				}
				DestroyAll(hWnd);
			}
			if (ColorDrop == FALSE) { // If dropdown menu is not open
				if (((XWindowPosition > 311) and (XWindowPosition < 330)) and ((YWindowPosition > 191) and (YWindowPosition < 210))) { ColorDropdown(hWnd); break; }
			}
			if (ColorDrop == TRUE) { // If dropdown menu is open
				if (((XWindowPosition > 311) and (XWindowPosition < 330)) and ((YWindowPosition > 191) and (YWindowPosition < 210))) { DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 211) and (YWindowPosition < 229))) { ColorType = 0; SetWindowTextW(Color3, L"Default colors"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 229) and (YWindowPosition < 248))) { ColorType = 1; SetWindowTextW(Color3, L"Preset 1"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 248) and (YWindowPosition < 267))) { ColorType = 2; SetWindowTextW(Color3, L"Preset 2"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 267) and (YWindowPosition < 286))) { ColorType = 3; SetWindowTextW(Color3, L"Preset 3"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 286) and (YWindowPosition < 305))) { ColorType = 4; SetWindowTextW(Color3, L"Preset 4"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 305) and (YWindowPosition < 324))) { ColorType = 5; SetWindowTextW(Color3, L"Preset 5"); DestroyColorDropdown(hWnd); }
			}
			if ((((XWindowPosition > 261) and (XWindowPosition < 340)) and ((YWindowPosition > 321) and (YWindowPosition < 340))) && ColorDrop == FALSE) { DestroyAll(hWnd); } // if Cancel button is hit
			if (((XWindowPosition > 332) and (XWindowPosition < 348)) and ((YWindowPosition > 153) and (YWindowPosition < 169))) { DestroyAll(hWnd); } // if X button is hit
		}
		if (LocationOpen == TRUE) {  // While location menu is open
			if (((XWindowPosition > 161) and (XWindowPosition < 240) and ((YWindowPosition > 296) and (YWindowPosition < 315)))) { // if Apply is hit
				wchar_t RealLocation[100], ImagLocation[100], ZoomLocation[100]; // Define wide characters
				GetWindowTextW(Location3, RealLocation, 100); // Get window text
				GetWindowTextW(Location4, ImagLocation, 100);
				GetWindowTextW(Location5, ZoomLocation, 100);
				std::wstring ws(RealLocation); // Convert each to string
				std::string str1(ws.begin(), ws.end());
				std::wstring ws2(ImagLocation);
				std::string str2(ws2.begin(), ws2.end());
				std::wstring ws3(ZoomLocation);
				std::string str3(ws3.begin(), ws3.end());
				if (!str1.empty() && str1.find_first_not_of("0123456789-.") == std::string::npos) { // if float
					NewReal = stod(str1); // convert to double and save
					SetWindowTextW(Info2, RealLocation); // write text
				}
				else { DestroyIncorrectNumberNotif(); IncorrectNumBox(hWnd); } // if incorrect open infobox
				if (!str2.empty() && str2.find_first_not_of("0123456789-.") == std::string::npos) { // if float
					NewImag = stod(str2); // convert to double and save
					SetWindowTextW(Info3, ImagLocation); // write text
				}
				else { DestroyIncorrectNumberNotif(); IncorrectNumBox(hWnd); } // if incorrect open infobox
				if (!str3.empty() && str3.find_first_not_of("0123456789") == std::string::npos) { // if int
					NewZoom = stoull(str3); // convert to unassigned long long and save
					SetWindowTextW(Info5, ZoomLocation); // write text
				}
				else { DestroyIncorrectNumberNotif(); IncorrectNumBox(hWnd); } // if incorrect open infobox
			}
			if (((XWindowPosition > 261) and (XWindowPosition < 340) and ((YWindowPosition > 296) and (YWindowPosition < 315)))) { DestroyAll(hWnd); } // Close menu from cancel button
			if (((XWindowPosition > 332) and (XWindowPosition < 348) and ((YWindowPosition > 178) and (YWindowPosition < 194)))) { DestroyAll(hWnd); } // Close menu from X button
		}
		if (HelpOpen == TRUE) { // While help menu open
			if (((XWindowPosition > 357) and (XWindowPosition < 376) and ((YWindowPosition > 129) and (YWindowPosition < 146)))) { ShellExecute(NULL, NULL, L"https://github.com/BrendanScott105/CMandel", NULL, NULL, SW_SHOWNORMAL); LinkBox(hWnd); } // Open URL in browser
			if (((XWindowPosition > 317) and (XWindowPosition < 397) and ((YWindowPosition > 396) and (YWindowPosition < 416)))) { DestroyAll(hWnd); } // Destroy help menu from OK
			if (((XWindowPosition > 382) and (XWindowPosition < 399) and ((YWindowPosition > 82) and (YWindowPosition < 99)))) { DestroyAll(hWnd); } // Destroy help menu from X
		}
		if (LinkNotif == TRUE) { // Link notif close
			if (((XWindowPosition > 152) and (XWindowPosition < 166) and ((YWindowPosition > 453) and (YWindowPosition < 467)))) { DestroyLinkNotif(); }
		}
		if (IncorrectNumberNotif == TRUE) { // Incorrect number notif close
			if (((XWindowPosition > 120) and (XWindowPosition < 135) and ((YWindowPosition > 363) and (YWindowPosition < 378)))) { DestroyIncorrectNumberNotif(); }
		}
		if (((XWindowPosition > 483) and (XWindowPosition < 500)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { exit(0); } // Close application button
		if (((XWindowPosition > 466) and (XWindowPosition < 483)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { ShowWindow(hWnd, SW_MINIMIZE); } // Minimize window button
		if (((XWindowPosition > 449) and (XWindowPosition < 467)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) // Help button
		{
			DestroyAll(hWnd);
			HelpMenu(hWnd); // Call help menu
		}
	}
	default: // default case for all others
		return DefWindowProcW(hWnd, defmsg, wp, lp); // return
	}
}

void InfoBar(HWND hWnd) // add current view information bar
{
	Info0a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 0, 538, 9, 19, hWnd, NULL, NULL, NULL);
	Info1a = CreateWindowW(L"static", L"Iterations : ", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 520, 123, 19, hWnd, NULL, NULL, NULL); // Display initially
	Info1 = CreateWindowW(L"static", L"200", WS_VISIBLE | WS_CHILD, 73, 521, 48, 17, hWnd, NULL, NULL, NULL);
	Info2a = CreateWindowW(L"static", L"Real : ", WS_VISIBLE | WS_BORDER | WS_CHILD, 131, 520, 179, 19, hWnd, NULL, NULL, NULL);
	Info2 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_CHILD, 173, 521, 136, 17, hWnd, NULL, NULL, NULL);
	Info3a = CreateWindowW(L"static", L"Imag : ", WS_VISIBLE | WS_BORDER | WS_CHILD, 319, 520, 182, 19, hWnd, NULL, NULL, NULL);
	Info3 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_CHILD, 364, 521, 138, 17, hWnd, NULL, NULL, NULL);
	Info4a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 309, 520, 10, 19, hWnd, NULL, NULL, NULL);
	Info4 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 121, 520, 10, 19, hWnd, NULL, NULL, NULL);
	Info5a = CreateWindowW(L"static", L"Zoom : ", WS_VISIBLE | WS_CHILD, 10, 539, 210, 19, hWnd, NULL, NULL, NULL);
	Info5 = CreateWindowW(L"static", L"4", WS_VISIBLE | WS_CHILD, 60, 539, 160, 17, hWnd, NULL, NULL, NULL);
	Info6a = CreateWindowW(L"static", L"Rotation :", WS_VISIBLE | WS_BORDER | WS_CHILD, 220, 538, 97, 19, hWnd, NULL, NULL, NULL);
	Info6 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_CHILD, 287, 539, 30, 17, hWnd, NULL, NULL, NULL);
	Info7a = CreateWindowW(L"static", L"°", WS_VISIBLE | WS_CHILD, 311, 539, 6, 17, hWnd, NULL, NULL, NULL);
	Info7 = CreateWindowW(L"static", L"Color preset :", WS_VISIBLE | WS_BORDER | WS_CHILD, 316, 538, 103, 19, hWnd, NULL, NULL, NULL);
	Info8a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 538, 500, 1, hWnd, NULL, NULL, NULL);
	Info8 = CreateWindowW(L"static", L"D", WS_VISIBLE | WS_CHILD, 408, 539, 10, 19, hWnd, NULL, NULL, NULL);
	Info9a = CreateWindowW(L"static", L"Fractal :", WS_VISIBLE | WS_BORDER | WS_CHILD, 418, 538, 74, 19, hWnd, NULL, NULL, NULL);
	Info9 = CreateWindowW(L"static", L"1", WS_VISIBLE | WS_CHILD, 475, 539, 16, 17, hWnd, NULL, NULL, NULL);
	Info0 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 491, 538, 9, 19, hWnd, NULL, NULL, NULL);
}

void TitleBar(HWND hWnd) // Create title bar
{
	Top1 = CreateWindowW(L"static", L" CMandel 0.3.0", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, -1, -1, 502, 20, hWnd, NULL, NULL, NULL); // Display initially
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
	long L01, L02;
	Formula1 = CreateWindowW(L"static", L" Select Formula...\n\n\n\n\n             Mirror screen space\n\n             Julia set variant\n             [Position modifies C]", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 170, 200, 200, hWnd, NULL, NULL, NULL);
	Formula2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 190, 200, 1, hWnd, NULL, NULL, NULL);
	Formula3 = CreateWindowW(L"static", L"Mandelbrot set", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 210, 141, 20, hWnd, NULL, NULL, NULL);
	if (RealFractalType == 1) { SetWindowTextW(Formula3, L"Mandelbrot set"); }
	if (RealFractalType == 2) { SetWindowTextW(Formula3, L"Burning ship"); }
	if (RealFractalType == 3) { SetWindowTextW(Formula3, L"Buffalo"); }
	if (RealFractalType == 4) { SetWindowTextW(Formula3, L"Celtic"); }
	if (RealFractalType == 5) { SetWindowTextW(Formula3, L"Mandelbar"); }
	if (RealFractalType == 6) { SetWindowTextW(Formula3, L"Mandelbar Celtic"); }
	if (RealFractalType == 7) { SetWindowTextW(Formula3, L"Perp. Mandelbrot"); }
	if (RealFractalType == 8) { SetWindowTextW(Formula3, L"Perp. Burning Ship"); }
	if (RealFractalType == 9) { SetWindowTextW(Formula3, L"Perp. Buffalo"); }
	if (RealFractalType == 10) { SetWindowTextW(Formula3, L"Perp. Celtic"); }
	Formula4 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	if (ScreenMirror == TRUE) { L01 = SS_BLACKRECT; }
	else { L01 = SS_LEFT; }
	Formula5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER | L01, 180, 254, 10, 10, hWnd, NULL, NULL, NULL);
	if (JuliaMode == TRUE) { L02 = SS_BLACKRECT; }
	else { L02 = SS_LEFT; }
	Formula6 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER | L02, 180, 286, 10, 10, hWnd, NULL, NULL, NULL);
	Formula7 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 340, 80, 20, hWnd, NULL, NULL, NULL);
	Formula8 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 340, 80, 20, hWnd, NULL, NULL, NULL);
	Formula9 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 172, 17, 17, hWnd, NULL, NULL, NULL);
	FormulaOpen = TRUE;
}

void ColorMenu(HWND hWnd) // Create color menu
{
	long L01;
	Color1 = CreateWindowW(L"static", L" Choose color preset...\n\n\n\n\n             Smooth coloring\n             [Will disable some\n             fast rendering\n             optimizations]", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 170, 200, 200, hWnd, NULL, NULL, NULL);
	Color2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 190, 200, 1, hWnd, NULL, NULL, NULL);
	Color3 = CreateWindowW(L"static", L"Default colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 210, 141, 20, hWnd, NULL, NULL, NULL);
	if (ColorType == 0) { SetWindowTextW(Color3, L"Default Colors"); }
	if (ColorType == 1) { SetWindowTextW(Color3, L"Preset 1"); }
	if (ColorType == 2) { SetWindowTextW(Color3, L"Preset 2"); }
	if (ColorType == 3) { SetWindowTextW(Color3, L"Preset 3"); }
	if (ColorType == 4) { SetWindowTextW(Color3, L"Preset 4"); }
	if (ColorType == 5) { SetWindowTextW(Color3, L"Preset 5"); }
	Color4 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	if (SmoothColor == TRUE) { L01 = SS_BLACKRECT; }
	else { L01 = SS_LEFT; }
	Color5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER | L01, 180, 254, 10, 10, hWnd, NULL, NULL, NULL);
	Color6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 340, 80, 20, hWnd, NULL, NULL, NULL);
	Color7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 340, 80, 20, hWnd, NULL, NULL, NULL);
	Color8 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 172, 17, 17, hWnd, NULL, NULL, NULL);
	ColorOpen = TRUE;
}

void LocationMenu(HWND hWnd) // Create location menu and create textboxes
{
	Location1 = CreateWindowW(L"static", L" Set location and zoom...", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 195, 200, 150, hWnd, NULL, NULL, NULL);
	Location2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 215, 200, 1, hWnd, NULL, NULL, NULL);
	Location3 = CreateWindowW(L"edit", L"Real position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 225, 180, 20, hWnd, NULL, NULL, NULL);
	SendMessage(Location3, EM_SETLIMITTEXT, 17, NULL);
	Location4 = CreateWindowW(L"edit", L"Imaginary position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 255, 180, 20, hWnd, NULL, NULL, NULL);
	SendMessage(Location4, EM_SETLIMITTEXT, 17, NULL);
	Location5 = CreateWindowW(L"edit", L"Zoom [Standard notation]", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER, 160, 285, 180, 20, hWnd, NULL, NULL, NULL);
	SendMessage(Location5, EM_SETLIMITTEXT, 20, NULL);
	Location6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 315, 80, 20, hWnd, NULL, NULL, NULL);
	Location7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 315, 80, 20, hWnd, NULL, NULL, NULL);
	Location8 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 197, 17, 17, hWnd, NULL, NULL, NULL);
	LocationOpen = TRUE;
}

void HelpMenu(HWND hWnd) // Create help menu
{
	HelpMenu1 = CreateWindowW(L"static", L" About CMandel....   © 2021, Brendan Scott\n\n This is open source software :\n Github.com/BrendanScott105/CMandel\n\n x86 Build - 64 Bit | Detected threads :\n\n Controls :\n W / A / S / D : Up / Left / Down / Right\n Q / E : CCW / CW rotate\n Mouse left : Zoom in\n Mouse right : Zoom out\n - / + : Increase / Decrease iterations\n [Tab - 10 | Shift - 100 | Control - 1000]\n F5 : Rerender entire screen space\n\n Limitations :\n - Iterations does not exceed 999999\n - Zoom limited to 64 Bits\n - Precision limited to 64 Bits\n - Resolution locked at 500x500", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 100, 300, 340, hWnd, NULL, NULL, NULL);
	HelpMenu2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 19, 300, 1, HelpMenu1, NULL, NULL, NULL);
	HelpMenu3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 278, 0, 1, 20, HelpMenu1, NULL, NULL, NULL);
	HelpMenu4 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 280, 1, 17, 17, HelpMenu1, NULL, NULL, NULL);
	HelpMenu5 = CreateWindowW(L"static", L"Ok", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 215, 315, 80, 20, HelpMenu1, NULL, NULL, NULL);
	HelpMenu6 = CreateWindowW(L"static", L"🡭", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 256, 48, 17, 17, HelpMenu1, NULL, NULL, NULL);
	int Concurrent = std::thread::hardware_concurrency();
	std::wstring concurrence = s2ws(std::to_string(Concurrent)); // to LPCWSTR
	HelpMenu7 = CreateWindowW(L"static", concurrence.c_str(), WS_VISIBLE | WS_CHILD, 249, 80, 51, 17, HelpMenu1, NULL, NULL, NULL);
	HelpOpen = TRUE;
}

void LinkBox(HWND hWnd) // Create link notif box
{
	Link1 = CreateWindowW(L"static", L"Link opened in browser tab ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_RIGHT, 148, 470, 204, 20, hWnd, NULL, NULL, NULL);
	Link2 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 150, 472, 16, 16, hWnd, NULL, NULL, NULL);
	Link3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 167, 470, 1, 20, hWnd, NULL, NULL, NULL);
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
	Top7a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 3, 38, 81, 1, hWnd, NULL, NULL, NULL);
	Top8a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 3, 57, 81, 1, hWnd, NULL, NULL, NULL);
	Top9a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, -1, 74, 88, 3, hWnd, NULL, NULL, NULL);
	ConfigureDrop = TRUE;
}

void FilterDrop(HWND hWnd) // Create filter dropdown and handle element filling
{
	long L01, L02, L03, L04, L05;
	DestroyWindow(Top5);
	Top1b = CreateWindowW(L"static", L"▲", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 136, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top2b = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 18, 174, 96, hWnd, NULL, NULL, NULL);
	Top3b = CreateWindowW(L"static", L"     Decolorize", WS_VISIBLE | WS_CHILD, 0, 20, 172, 20, hWnd, NULL, NULL, NULL);
	Top4b = CreateWindowW(L"static", L"     Edge detection", WS_VISIBLE | WS_CHILD, 0, 39, 172, 20, hWnd, NULL, NULL, NULL);
	Top5b = CreateWindowW(L"static", L"     Inverse edge detection", WS_VISIBLE | WS_CHILD, 0, 58, 172, 20, hWnd, NULL, NULL, NULL);
	Top6b = CreateWindowW(L"static", L"     Grayscale", WS_VISIBLE | WS_CHILD, 0, 77, 172, 20, hWnd, NULL, NULL, NULL);
	Top7b = CreateWindowW(L"static", L"     Inverse Grayscale", WS_VISIBLE | WS_CHILD, 0, 96, 172, 17, hWnd, NULL, NULL, NULL);
	if (Filters[4] == TRUE) { L05 = SS_BLACKRECT; }
	else { L05 = SS_LEFT; }
	Top8b = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | L05, 4, 98, 12, 12, hWnd, NULL, NULL, NULL);
	if (Filters[3] == TRUE) { L04 = SS_BLACKRECT; }
	else { L04 = SS_LEFT; }
	Top9b = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | L04, 4, 79, 12, 12, hWnd, NULL, NULL, NULL);
	if (Filters[2] == TRUE) { L03 = SS_BLACKRECT; }
	else { L03 = SS_LEFT; }
	Top0b = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | L03, 4, 60, 12, 12, hWnd, NULL, NULL, NULL);
	if (Filters[1] == TRUE) { L02 = SS_BLACKRECT; }
	else { L02 = SS_LEFT; }
	TopAb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | L02, 4, 41, 12, 12, hWnd, NULL, NULL, NULL);
	if (Filters[0] == TRUE) { L01 = SS_BLACKRECT; }
	else { L01 = SS_LEFT; }
	TopBb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER | L01, 4, 22, 12, 12, hWnd, NULL, NULL, NULL);
	TopCb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 37, 164, 1, hWnd, NULL, NULL, NULL);
	TopDb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 56, 164, 1, hWnd, NULL, NULL, NULL);
	TopEb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 75, 164, 1, hWnd, NULL, NULL, NULL);
	TopFb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 94, 164, 1, hWnd, NULL, NULL, NULL);
	FiltersDrop = TRUE;
}

void IncorrectNumBox(HWND hWnd) // Create link notif box
{
	IN1 = CreateWindowW(L"static", L"One or more values are not numbers ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_RIGHT, 117, 380, 266, 20, hWnd, NULL, NULL, NULL);
	IN2 = CreateWindowW(L"static", L"✕", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 119, 382, 16, 16, hWnd, NULL, NULL, NULL);
	IN3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 136, 380, 1, 20, hWnd, NULL, NULL, NULL);
	IncorrectNumberNotif = TRUE;
}

void FractDropdown(HWND hWnd) // Create Fractal dropdown menu
{
	FDdrop1 = CreateWindowW(L"static", L"▲", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	FDdrop2 = CreateWindowW(L"static", L"Mandelbrot set", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 229, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop3 = CreateWindowW(L"static", L"Burning ship", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 248, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop4 = CreateWindowW(L"static", L"Buffalo", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 267, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop5 = CreateWindowW(L"static", L"Celtic", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 286, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop6 = CreateWindowW(L"static", L"Mandelbar", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 305, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop7 = CreateWindowW(L"static", L"Mandelbar Celtic", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 324, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop8 = CreateWindowW(L"static", L"Perp. Mandelbrot", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 343, 141, 20, hWnd, NULL, NULL, NULL);
	FDdrop9 = CreateWindowW(L"static", L"Perp. Burning ship", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 362, 141, 20, hWnd, NULL, NULL, NULL);
	FDdropA = CreateWindowW(L"static", L"Perp. Buffalo", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 381, 141, 20, hWnd, NULL, NULL, NULL);
	FDdropB = CreateWindowW(L"static", L"Perp. Celtic", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 400, 141, 20, hWnd, NULL, NULL, NULL);
	FDdropC = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 170, 228, 141, 3, hWnd, NULL, NULL, NULL);
	FractDrop = TRUE;
}

void ColorDropdown(HWND hWnd) // Create Fractal dropdown menu
{
	CDdrop1 = CreateWindowW(L"static", L"▲", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	CDdrop2 = CreateWindowW(L"static", L"Default colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 229, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop3 = CreateWindowW(L"static", L"Preset 1", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 248, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop4 = CreateWindowW(L"static", L"Preset 2", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 267, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop5 = CreateWindowW(L"static", L"Preset 3", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 286, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop6 = CreateWindowW(L"static", L"Preset 4", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 305, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop7 = CreateWindowW(L"static", L"Preset 5", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 324, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop8 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 170, 228, 141, 3, hWnd, NULL, NULL, NULL);
	ColorDrop = TRUE;
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

void DestroyFiltersDrop(HWND hWnd) // Destroy filters dropdown menu
{
	DestroyWindow(Top1b);
	DestroyWindow(Top2b);
	DestroyWindow(Top3b);
	DestroyWindow(Top4b);
	DestroyWindow(Top5b);
	DestroyWindow(Top6b);
	DestroyWindow(Top7b);
	DestroyWindow(Top8b);
	DestroyWindow(Top9b);
	DestroyWindow(Top0b);
	DestroyWindow(TopAb);
	DestroyWindow(TopBb);
	DestroyWindow(TopCb);
	DestroyWindow(TopDb);
	DestroyWindow(TopEb);
	DestroyWindow(TopFb);
	Top5 = CreateWindowW(L"static", L"▼", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 136, 1, 16, 16, hWnd, NULL, NULL, NULL);
	FiltersDrop = FALSE;
}

void DestroyIncorrectNumberNotif() // Destroy incorrect number notif
{
	DestroyWindow(IN1);
	DestroyWindow(IN2);
	DestroyWindow(IN3);
	IncorrectNumberNotif = FALSE;
}

void DestroyFractDropdown(HWND hWnd) // Destroy fract dropdown
{ 
	DestroyWindow(FDdrop1);
	DestroyWindow(FDdrop2);
	DestroyWindow(FDdrop3);
	DestroyWindow(FDdrop4);
	DestroyWindow(FDdrop5);
	DestroyWindow(FDdrop6);
	DestroyWindow(FDdrop7);
	DestroyWindow(FDdrop8);
	DestroyWindow(FDdrop9);
	DestroyWindow(FDdropA);
	DestroyWindow(FDdropB);
	DestroyWindow(FDdropC);
	FractDrop = FALSE;
}

void DestroyColorDropdown(HWND hWnd) { // Destroy fract dropdown
	DestroyWindow(CDdrop1);
	DestroyWindow(CDdrop2);
	DestroyWindow(CDdrop3);
	DestroyWindow(CDdrop4);
	DestroyWindow(CDdrop5);
	DestroyWindow(CDdrop6);
	DestroyWindow(CDdrop7);
	DestroyWindow(CDdrop8);
	ColorDrop = FALSE;
}

void DestroyAll(HWND hWnd) // Destroy all menus
{
	DestroyFractDropdown(hWnd);
	DestroyColorDropdown(hWnd);
	DestroyFormulaMenu();
	DestroyColorMenu();
	DestroyLocationMenu();
	DestroyHelpMenu();
	DestroyLinkNotif();
	DestroyConfigDrop(hWnd);
	DestroyFiltersDrop(hWnd);
	DestroyIncorrectNumberNotif();
}
