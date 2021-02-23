#include <SFML/Graphics.hpp>
#include <windows.h> // Include
#include <cmath>
#include <string>
#include <thread>
#include <iomanip>
#include <sstream>
#include <complex>

using namespace std;

/*Window variables start*/
LRESULT CALLBACK Proc(HWND, UINT, WPARAM, LPARAM); // Declare existence
void WinMenus(HWND); // Declare existence
void InfoBar(HWND); // Declare existence
void TitleBar(HWND); // Declare existence
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

void SetZoomDensity(INT); // Declare
void SetLocation(INT); // Declare
void SetRotation(INT); // Declare

void PullFromIter(); // Declare

void ColorizePlot(INT, INT, INT); // Declare

void ShiftScreen(INT); // Declare

void PlotPoint(INT, INT);

std::complex<long double> TableToComplex(INT, INT); // X, Y

HMENU hMenu; // define header menu

HWND Formula1, Formula2, Formula3, Formula4, Formula5, Formula6, Formula7, Formula8, Formula9; // Declare formula menu elements globally
HWND Location1, Location2, Location3, Location4, Location5, Location6, Location7, Location8; // Declare Location menu elements globally
HWND Color1, Color2, Color3, Color4, Color5, Color6, Color7, Color8; // Declare color menu elements globally
HWND HelpMenu1, HelpMenu2, HelpMenu3, HelpMenu4, HelpMenu5, HelpMenu6, HelpMenu7; // Declare help menu elements globally
HWND Top1, Top2, Top3, Top4, Top5, Top6, Top7, Top8, Top9, Top0, TopA; // Declare top level menu elements globally
HWND Top1a, Top2a, Top3a, Top4a, Top5a, Top6a, Top7a, Top8a, Top9a, Top0a;
HWND Top1b, Top2b, Top3b, Top4b, Top5b, Top6b, Top7b, Top8b, Top9b, Top0b, TopAb, TopBb, TopCb, TopDb, TopEb, TopFb, TopGb;
HWND Info0a, Info0, Info1a, Info1, Info2a, Info2, Info3a, Info3, Info4a, Info4, Info5a, Info5, Info6a, Info6, Info7a, Info7, Info8a, Info8, Info9a, Info9; // Declare info elements globally
HWND Link1, Link2, Link3; // Declare link notif elements globally
HWND IN1, IN2, IN3; // Declare Incorrect Number notif elements globally
HWND FDdrop1, FDdrop2, FDdrop3, FDdrop4, FDdrop5, FDdrop6, FDdrop7, FDdrop8, FDdrop9, FDdropA, FDdropB, FDdropC; // Declare fractal dropdown elements globally
HWND CDdrop1, CDdrop2, CDdrop3, CDdrop4, CDdrop5, CDdrop6, CDdrop7, CDdrop8; // Declare color dropdown elements globally
HWND RealWinMain; // Declare main window
HWND SubWin;

sf::RenderWindow SFMLMain(SubWin);
sf::Image ImageMain;
sf::Texture TextureMain;

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

sf::Text GlobalText;

POINT Cursor;
ULONG_PTR GdiToken;
HDC hdc;
PAINTSTRUCT ps;

BOOL ScreenMirror = FALSE;
BOOL JuliaMode = FALSE;
INT FractalType = 2;
INT ColorType = 0;
/*Window variables end*/

/*Fractal variable definitions start*/
int Iters = 200; // define iterations
long double PixelDif = 0.008;
BOOL Filters[5] = { FALSE,FALSE,FALSE,FALSE,FALSE }; // Decolorize, Edge detect, Inverse edge, Grayscale, Inverse Grayscale
long double NewReal = 0; long double NewImag = 0; long double NewZoom = 4; int Rotation = 0;
INT RealFractalType = 1;

int ScreenSpaceIters[500][500];
/*Fractal variables end*/

/*##########
WINDOW LOGIC
##########*/

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

	RealWinMain = CreateWindowW(L"MainWin", L"CMandel", (WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME) & ~WS_MAXIMIZEBOX & ~WS_CAPTION | WS_VISIBLE | WS_BORDER | WS_POPUP, 500, 200, 502, 577, NULL, NULL, NULL, NULL); // Create window with basic params
	SubWin = CreateWindowW(L"static", NULL, WS_VISIBLE | WS_CHILD, 0, 20, 500, 500, RealWinMain, NULL, NULL, NULL);
	sf::RenderWindow SFMLMain(SubWin);

	for (int x = 0; x < 500; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			PlotPoint(x, y);
		}
	}
	

	MSG Message;
	Message.message = ~WM_QUIT;
	while (Message.message != WM_QUIT)
	{
		if (PeekMessage(&Message, NULL, 0, 0, PM_REMOVE))
		{
			// If a message was waiting in the message queue, process it
			TranslateMessage(&Message);
			DispatchMessage(&Message);
		}
		else {
			if (!(FormulaOpen || ColorOpen || LocationOpen || HelpOpen || LinkNotif || ConfigureDrop || FiltersDrop || IncorrectNumberNotif || FractDrop || ColorDrop || SmoothColor) == TRUE)
			{
				ImageMain.create(500, 500);

				PullFromIter();

				TextureMain.loadFromImage(ImageMain);
				sf::Sprite SpriteMain(TextureMain);
				SFMLMain.draw(SpriteMain);
				SFMLMain.display();
			}
		}
		
	}

}

LRESULT CALLBACK Proc(HWND hWnd, UINT defmsg, WPARAM wp, LPARAM lp) // window procedure code
{
	switch (defmsg)
	{
	case WM_CREATE: // when window is created
		TitleBar(hWnd); // Call title bar function
		InfoBar(hWnd);
		break;
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		// Call main render function here
		EndPaint(hWnd, &ps);
		return 0;
	}
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
			LPCWSTR temp8;
			std::wstring Wtemp2 = to_wstring(Iters);
			temp8 = (LPCWSTR)Wtemp2.c_str();
			SetWindowTextW(Info1, temp8);
			for (int x = 0; x < 500; x++)
			{
				for (int y = 0; y < 500; y++)
				{
					PlotPoint(x, y);
				}
			}
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
			LPCWSTR temp9;
			std::wstring Wtemp2 = to_wstring(Iters);
			temp9 = (LPCWSTR)Wtemp2.c_str();
			SetWindowTextW(Info1, temp9);
			for (int x = 0; x < 500; x++)
			{
				for (int y = 0; y < 500; y++)
				{
					PlotPoint(x, y);
				}
			}
		}
		if (wp == VK_UP) { SetZoomDensity(1); PlotPoint(250, 250);} // Zoom in
		if (wp == VK_DOWN) { SetZoomDensity(0); PlotPoint(250, 250);} // Zoom out
		if (wp == 0x57) { SetLocation(0); ShiftScreen(3);} // Set new position
		if (wp == 0x41) { SetLocation(1); ShiftScreen(2);}
		if (wp == 0x53) { SetLocation(2); ShiftScreen(1);}
		if (wp == 0x44) { SetLocation(3); ShiftScreen(0); }
		if (wp == 0x45) { SetRotation(0); } // Rotate clockwise
		if (wp == 0x51) { SetRotation(1); } // Rotate counterclockwise
		if (wp == VK_F5) { } // For rerendering

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
				MoveWindow(hWnd, Cursor.x - XWindowPosition, Cursor.y - YWindowPosition - 20, 502, 577, TRUE);
				UpdateWindow(hWnd);
			}
		}
		if (FiltersDrop == TRUE) { // When filters menu is open
			if (((XWindowPosition > 150) and (XWindowPosition < 166)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyFiltersDrop(hWnd); break; } // Destroy filters dropdown
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

			if (((XWindowPosition > 150) and (XWindowPosition < 166)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyAll(hWnd);  DestroyConfigDrop(hWnd); FilterDrop(hWnd); break; } // Trigger open filter dropdown
		}
		if (ConfigureDrop == TRUE) { // When configure menu is open
			if (((XWindowPosition > 81) and (XWindowPosition < 96)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyConfigDrop(hWnd); break; } // Destroy configure dropdown menu
			if (((XWindowPosition > 0) and (XWindowPosition < 99)) and ((YWindowPosition > -1) and (YWindowPosition < 19))) { DestroyAll(hWnd); FormulaMenu(hWnd); } // Destroy other menus and open formula menu
			if (((XWindowPosition > 0) and (XWindowPosition < 99)) and ((YWindowPosition > 19) and (YWindowPosition < 38))) { DestroyAll(hWnd); ColorMenu(hWnd); } // Destroy other menus and open color menu
			if (((XWindowPosition > 0) and (XWindowPosition < 99)) and ((YWindowPosition > 38) and (YWindowPosition < 55))) { DestroyAll(hWnd); LocationMenu(hWnd); } // Destroy other menus and open location menu
			if (((XWindowPosition > 0) and (XWindowPosition < 99)) and ((YWindowPosition > 57) and (YWindowPosition < 75))) { DestroyAll(hWnd); exit(0); } // Destroy other menus and exit
		}
		if (ConfigureDrop == FALSE) {
			if (((XWindowPosition > 81) and (XWindowPosition < 96)) and ((YWindowPosition > -19) and (YWindowPosition < -4))) { DestroyAll(hWnd); DestroyFiltersDrop(hWnd); ConfigDrop(hWnd); break; } // Trigger open configure dropdown
		}
		if (FormulaOpen == TRUE) { // While formula menu open
			if ((((XWindowPosition > 181) and (XWindowPosition < 190)) and ((YWindowPosition > 237) and (YWindowPosition < 246))) && FractDrop == FALSE) {
				if (ScreenMirror == FALSE) {
					ScreenMirror = TRUE;
					DestroyAll(hWnd);
					FormulaMenu(hWnd);
				}
				else { ScreenMirror = FALSE; DestroyAll(hWnd); FormulaMenu(hWnd); } // if true, make false, and rerender
			}
			if ((((XWindowPosition > 181) and (XWindowPosition < 190)) and ((YWindowPosition > 276) and (YWindowPosition < 285))) && FractDrop == FALSE) {
				if (JuliaMode == FALSE) {
					JuliaMode = TRUE;
					DestroyAll(hWnd);
					FormulaMenu(hWnd);
				}
				else { JuliaMode = FALSE; DestroyAll(hWnd); FormulaMenu(hWnd); } // if true, make false, and rerender
			}
			if ((((XWindowPosition > 261) and (XWindowPosition < 340)) and ((YWindowPosition > 321) and (YWindowPosition < 350))) && FractDrop == FALSE) { DestroyAll(hWnd); } // if Cancel button is hit
			if (((XWindowPosition > 332) and (XWindowPosition < 348)) and ((YWindowPosition > 153) and (YWindowPosition < 169))) { DestroyAll(hWnd); } // if X button is hit
			if ((((XWindowPosition > 161) and (XWindowPosition < 240)) and ((YWindowPosition > 321) and (YWindowPosition < 350))) && FractDrop == FALSE) { // if Apply button is hit
				RealFractalType = FractalType;
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
			if ((((XWindowPosition > 181) and (XWindowPosition < 190)) and ((YWindowPosition > 237) and (YWindowPosition < 246))) && ColorDrop == FALSE) {
				if (SmoothColor == FALSE) {
					SmoothColor = TRUE;
					DestroyAll(hWnd);
					ColorMenu(hWnd);
				}
				else { SmoothColor = FALSE; DestroyAll(hWnd); ColorMenu(hWnd); } // if true, make false, and rerender
			}
			if ((((XWindowPosition > 161) and (XWindowPosition < 240)) and ((YWindowPosition > 316) and (YWindowPosition < 340))) && ColorDrop == FALSE) { // if Apply button is hit
				DestroyAll(hWnd);
			}
			if (ColorDrop == FALSE) { // If dropdown menu is not open
				if (((XWindowPosition > 311) and (XWindowPosition < 330)) and ((YWindowPosition > 191) and (YWindowPosition < 210))) { ColorDropdown(hWnd); break; }
			}
			if (ColorDrop == TRUE) { // If dropdown menu is open
				if (((XWindowPosition > 311) and (XWindowPosition < 330)) and ((YWindowPosition > 191) and (YWindowPosition < 210))) { DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 211) and (YWindowPosition < 229))) { ColorType = 0; SetWindowTextW(Color3, L"Default"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 229) and (YWindowPosition < 248))) { ColorType = 1; SetWindowTextW(Color3, L"Legacy"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 248) and (YWindowPosition < 267))) { ColorType = 2; SetWindowTextW(Color3, L"Warm colors"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 267) and (YWindowPosition < 286))) { ColorType = 3; SetWindowTextW(Color3, L"Cool colors"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 286) and (YWindowPosition < 305))) { ColorType = 4; SetWindowTextW(Color3, L"Deuteranopia"); DestroyColorDropdown(hWnd); }
				if (((XWindowPosition > 171) and (XWindowPosition < 311)) and ((YWindowPosition > 305) and (YWindowPosition < 324))) { ColorType = 5; SetWindowTextW(Color3, L"Tritanopia"); DestroyColorDropdown(hWnd); }
			}
			if ((((XWindowPosition > 261) and (XWindowPosition < 340)) and ((YWindowPosition > 316) and (YWindowPosition < 340))) && ColorDrop == FALSE) { DestroyAll(hWnd); } // if Cancel button is hit
			if (((XWindowPosition > 332) and (XWindowPosition < 348)) and ((YWindowPosition > 153) and (YWindowPosition < 169))) { DestroyAll(hWnd); } // if X button is hit
		}
		if (LocationOpen == TRUE) {  // While location menu is open
			BOOL Valid1 = FALSE;
			BOOL Valid2 = FALSE;
			BOOL Valid3 = FALSE;
			if (((XWindowPosition > 161) and (XWindowPosition < 240) and ((YWindowPosition > 296) and (YWindowPosition < 320)))) { // if Apply is hit
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
					Valid1 = TRUE;
				}
				else { DestroyIncorrectNumberNotif(); IncorrectNumBox(hWnd); } // if incorrect open infobox
				if (!str2.empty() && str2.find_first_not_of("0123456789-.") == std::string::npos) { // if float
					NewImag = stod(str2); // convert to double and save
					SetWindowTextW(Info3, ImagLocation); // write text
					Valid2 = TRUE;
				}
				else { DestroyIncorrectNumberNotif(); IncorrectNumBox(hWnd); } // if incorrect open infobox
				if (!str3.empty() && str3.find_first_not_of("0123456789-.") == std::string::npos) { // if int
					NewZoom = stod(str3); // convert to unassigned long long and save
					SetWindowTextW(Info5, ZoomLocation); // write text
					Valid3 = TRUE;
				}
				else { DestroyIncorrectNumberNotif(); IncorrectNumBox(hWnd); } // if incorrect open infobox
				if ((Valid1 && Valid2 &&Valid3) == TRUE) { 
					DestroyAll(hWnd);
					for (int x = 0; x < 500; x++)
					{
						for (int y = 0; y < 500; y++)
						{
							PlotPoint(x, y);
						}
					}
				}
			}
			if (((XWindowPosition > 261) and (XWindowPosition < 340) and ((YWindowPosition > 296) and (YWindowPosition < 320)))) { DestroyAll(hWnd); } // Close menu from cancel button
			if (((XWindowPosition > 332) and (XWindowPosition < 348) and ((YWindowPosition > 178) and (YWindowPosition < 194)))) { DestroyAll(hWnd); } // Close menu from X button
		}
		if (HelpOpen == TRUE) { // While help menu open
			if (((XWindowPosition > 347) and (XWindowPosition < 366) and ((YWindowPosition > 104) and (YWindowPosition < 121)))) { ShellExecute(NULL, NULL, L"https://github.com/BrendanScott105/CMandel", NULL, NULL, SW_SHOWNORMAL); LinkBox(hWnd); } // Open URL in browser
			if (((XWindowPosition > 317) and (XWindowPosition < 397) and ((YWindowPosition > 396) and (YWindowPosition < 416)))) { DestroyAll(hWnd); } // Destroy help menu from OK
			if (((XWindowPosition > 382) and (XWindowPosition < 399) and ((YWindowPosition > 82) and (YWindowPosition < 99)))) { DestroyAll(hWnd); } // Destroy help menu from X
		}
		if (LinkNotif == TRUE) { // Link notif close
			if (((XWindowPosition > 148) and (XWindowPosition < 166) and ((YWindowPosition > 458) and (YWindowPosition < 472)))) { DestroyLinkNotif(); }
		}
		if (IncorrectNumberNotif == TRUE) { // Incorrect number notif close
			if (((XWindowPosition > 123) and (XWindowPosition < 138) and ((YWindowPosition > 363) and (YWindowPosition < 378)))) { DestroyIncorrectNumberNotif(); }
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

/*##############
END WINDOW LOGIC
################
START WINDOW DEF
##############*/

void InfoBar(HWND hWnd) // add current view information bar
{
	Info1a = CreateWindowW(L"static", L"Iterations : ", WS_VISIBLE | WS_BORDER | WS_CHILD, 350, 539, 150, 19, hWnd, NULL, NULL, NULL); // Display initially
	Info1 = CreateWindowW(L"static", L"200", WS_VISIBLE | WS_CHILD, 440, 540, 57, 17, hWnd, NULL, NULL, NULL);
	Info2a = CreateWindowW(L"static", L"Re : ", WS_VISIBLE | WS_BORDER | WS_CHILD, 0, 521, 500, 19, hWnd, NULL, NULL, NULL);
	Info2 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_CHILD, 35, 522, 464, 17, hWnd, NULL, NULL, NULL);
	Info3a = CreateWindowW(L"static", L"Im : ", WS_VISIBLE | WS_BORDER | WS_CHILD, 0, 539, 351, 19, hWnd, NULL, NULL, NULL);
	Info3 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_CHILD, 32, 540, 318, 17, hWnd, NULL, NULL, NULL);
	Info4a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 0, 558, 1, 19, hWnd, NULL, NULL, NULL);
	Info5a = CreateWindowW(L"static", L"Zoom : ", WS_VISIBLE | WS_CHILD, 2, 558, 229, 19, hWnd, NULL, NULL, NULL);
	Info5 = CreateWindowW(L"static", L"4", WS_VISIBLE | WS_CHILD, 58, 558, 333, 16, hWnd, NULL, NULL, NULL);
	Info6a = CreateWindowW(L"static", L"Rotation :", WS_VISIBLE | WS_BORDER | WS_CHILD, 391, 557, 109, 19, hWnd, NULL, NULL, NULL);
	Info6 = CreateWindowW(L"static", L"0", WS_VISIBLE | WS_CHILD, 471, 558, 28, 17, hWnd, NULL, NULL, NULL);
	Info0a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 0, 520, 500, 1, hWnd, NULL, NULL, NULL);
}

void TitleBar(HWND hWnd) // Create title bar
{
	Top1 = CreateWindowW(L"static", L" CMandel 0.5", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, -1, -1, 502, 20, hWnd, NULL, NULL, NULL); // Display initially
	Top2 = CreateWindowW(L"static", L"Configure", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, -2, 99, 21, hWnd, NULL, NULL, NULL);
	Top3 = CreateWindowW(L"static", L"▾", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 80, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top4 = CreateWindowW(L"static", L"Filters", WS_VISIBLE | WS_BORDER | WS_CHILD, 97, -2, 70, 21, hWnd, NULL, NULL, NULL);
	Top5 = CreateWindowW(L"static", L"▾", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 149, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top6 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 483, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top7 = CreateWindowW(L"static", L"⎽⎽", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 466, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top8 = CreateWindowW(L"static", L"ˀ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 449, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top9 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 470, 12, 8, 2, hWnd, NULL, NULL, NULL);
	Top0 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 447, -1, 1, 20, hWnd, NULL, NULL, NULL);
	TopA = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 0, 19, 500, 1, hWnd, NULL, NULL, NULL);
}

void FormulaMenu(HWND hWnd) // Create formula menu
{
	long L01, L02;
	Formula1 = CreateWindowW(L"static", L" Select Formula...\n\n\n\n             Mirror screen\n\n             Julia set variant\n             [Position sets C]", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 170, 200, 210, hWnd, NULL, NULL, NULL);
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
	Formula4 = CreateWindowW(L"static", L"˅", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	if (ScreenMirror == TRUE) { L01 = SS_BLACKRECT; }
	else { L01 = SS_LEFT; }
	Formula5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER | L01, 180, 256, 10, 10, hWnd, NULL, NULL, NULL);
	if (JuliaMode == TRUE) { L02 = SS_BLACKRECT; }
	else { L02 = SS_LEFT; }
	Formula6 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER | L02, 180, 295, 10, 10, hWnd, NULL, NULL, NULL);
	Formula7 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 345, 80, 25, hWnd, NULL, NULL, NULL);
	Formula8 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 345, 80, 25, hWnd, NULL, NULL, NULL);
	Formula9 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 172, 17, 17, hWnd, NULL, NULL, NULL);
	FormulaOpen = TRUE;
}

void ColorMenu(HWND hWnd) // Create color menu
{
	long L01;
	Color1 = CreateWindowW(L"static", L" Choose color preset...\n\n\n\n             Smooth coloring\n             [Will disable some\n             optimizations]", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 170, 200, 200, hWnd, NULL, NULL, NULL);
	Color2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 190, 200, 1, hWnd, NULL, NULL, NULL);
	Color3 = CreateWindowW(L"static", L"Default colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 210, 141, 20, hWnd, NULL, NULL, NULL);
	if (ColorType == 0) { SetWindowTextW(Color3, L"Default"); };
	if (ColorType == 1) { SetWindowTextW(Color3, L"Legacy"); };
	if (ColorType == 2) { SetWindowTextW(Color3, L"Warm colors"); };
	if (ColorType == 3) { SetWindowTextW(Color3, L"Cool colors"); };
	if (ColorType == 4) { SetWindowTextW(Color3, L"Deuteranopia"); };
	if (ColorType == 5) { SetWindowTextW(Color3, L"Tritanopia"); };
	Color4 = CreateWindowW(L"static", L"˅", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	if (SmoothColor == TRUE) { L01 = SS_BLACKRECT; }
	else { L01 = SS_LEFT; }
	Color5 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER | L01, 180, 256, 10, 10, hWnd, NULL, NULL, NULL);
	Color6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 335, 80, 25, hWnd, NULL, NULL, NULL);
	Color7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 335, 80, 25, hWnd, NULL, NULL, NULL);
	Color8 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 172, 17, 17, hWnd, NULL, NULL, NULL);
	ColorOpen = TRUE;
}

void LocationMenu(HWND hWnd) // Create location menu and create textboxes
{
	Location1 = CreateWindowW(L"static", L" Set location / zoom...", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 195, 200, 155, hWnd, NULL, NULL, NULL);
	Location2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 150, 215, 200, 1, hWnd, NULL, NULL, NULL);
	Location3 = CreateWindowW(L"edit", L"Real position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 225, 180, 20, hWnd, NULL, NULL, NULL);
	SendMessage(Location3, EM_SETLIMITTEXT, 22, NULL);
	Location4 = CreateWindowW(L"edit", L"Imaginary position", WS_VISIBLE | WS_BORDER | WS_CHILD, 160, 255, 180, 20, hWnd, NULL, NULL, NULL);
	SendMessage(Location4, EM_SETLIMITTEXT, 22, NULL);
	Location5 = CreateWindowW(L"edit", L"Zoom [Standard]", WS_VISIBLE | WS_BORDER | WS_CHILD | ES_NUMBER, 160, 285, 180, 20, hWnd, NULL, NULL, NULL);
	SendMessage(Location5, EM_SETLIMITTEXT, 22, NULL);
	Location6 = CreateWindowW(L"static", L"Apply", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 160, 315, 80, 25, hWnd, NULL, NULL, NULL);
	Location7 = CreateWindowW(L"static", L"Cancel", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 260, 315, 80, 25, hWnd, NULL, NULL, NULL);
	Location8 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 331, 197, 17, 17, hWnd, NULL, NULL, NULL);
	LocationOpen = TRUE;
}

void HelpMenu(HWND hWnd) // Create help menu
{
	HelpMenu1 = CreateWindowW(L"static", L" About...        © 2021, Brendan Scott\n This is open source software :\n @ Github/BrendanScott105/CMandel\n 64 Bit | Detected threads :\n Controls : ------------------------------------------\n W / A / S / D : Up / Left / Down / Right\n Q / E : CCW / CW rotate\n 🠕 : Zoom in\n 🠗 : Zoom out\n - / + : Increase / Decrease iterations\n [Tab - 10 | Shift - 100 | Control - 1000]\n F5 : Rerender entire screen space\n Limitations : --------------------------------------\n - Iterations does not exceed 999999\n - Precision limited to long double\n - Resolution locked at 500", WS_VISIBLE | WS_BORDER | WS_CHILD, 100, 100, 300, 340, hWnd, NULL, NULL, NULL);
	HelpMenu2 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 19, 300, 1, HelpMenu1, NULL, NULL, NULL);
	HelpMenu3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 278, 0, 1, 20, HelpMenu1, NULL, NULL, NULL);
	HelpMenu4 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 280, 1, 17, 17, HelpMenu1, NULL, NULL, NULL);
	HelpMenu5 = CreateWindowW(L"static", L"Ok", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 215, 315, 80, 20, HelpMenu1, NULL, NULL, NULL);
	HelpMenu6 = CreateWindowW(L"static", L"⌃", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 246, 23, 17, 17, HelpMenu1, NULL, NULL, NULL);
	int Concurrent = std::thread::hardware_concurrency();
	LPCWSTR temp3;
	std::wstring Wtemp3 = to_wstring(std::thread::hardware_concurrency());
	temp3 = (LPCWSTR)Wtemp3.c_str();
	HelpMenu7 = CreateWindowW(L"static", temp3, WS_VISIBLE | WS_CHILD, 212, 60, 51, 17, HelpMenu1, NULL, NULL, NULL);
	HelpOpen = TRUE;
}

void LinkBox(HWND hWnd) // Create link notif box
{
	Link1 = CreateWindowW(L"static", L"Link opened in browser ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_RIGHT, 148, 470, 210, 20, hWnd, NULL, NULL, NULL);
	Link2 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 150, 472, 16, 16, hWnd, NULL, NULL, NULL);
	Link3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 167, 470, 1, 20, hWnd, NULL, NULL, NULL);
	LinkNotif = TRUE;
}

void ConfigDrop(HWND hWnd) // Create configure dropdown
{
	DestroyWindow(Top3);
	Top1a = CreateWindowW(L"static", L"▴", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 80, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top2a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 18, 99, 77, hWnd, NULL, NULL, NULL);
	Top3a = CreateWindowW(L"static", L" Formula", WS_VISIBLE | WS_CHILD, -1, 19, 98, 20, hWnd, NULL, NULL, NULL);
	Top4a = CreateWindowW(L"static", L" Colors", WS_VISIBLE | WS_CHILD, -1, 38, 98, 20, hWnd, NULL, NULL, NULL);
	Top5a = CreateWindowW(L"static", L" Location", WS_VISIBLE | WS_CHILD, -1, 57, 98, 20, hWnd, NULL, NULL, NULL);
	Top6a = CreateWindowW(L"static", L" Exit", WS_VISIBLE | WS_CHILD, -1, 77, 98, 17, hWnd, NULL, NULL, NULL);
	Top7a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 3, 38, 91, 1, hWnd, NULL, NULL, NULL);
	Top8a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 3, 57, 91, 1, hWnd, NULL, NULL, NULL);
	Top9a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, -1, 74, 98, 3, hWnd, NULL, NULL, NULL);
	Top0a = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, 0, 18, 101, 2, hWnd, NULL, NULL, NULL);
	ConfigureDrop = TRUE;
}

void FilterDrop(HWND hWnd) // Create filter dropdown and handle element filling
{
	long L01, L02, L03, L04, L05;
	DestroyWindow(Top5);
	Top1b = CreateWindowW(L"static", L"▴", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 149, 1, 16, 16, hWnd, NULL, NULL, NULL);
	Top2b = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD, -1, 18, 174, 96, hWnd, NULL, NULL, NULL);
	Top3b = CreateWindowW(L"static", L"     Decolorize", WS_VISIBLE | WS_CHILD, 0, 18, 185, 20, hWnd, NULL, NULL, NULL);
	Top4b = CreateWindowW(L"static", L"     Edge detection", WS_VISIBLE | WS_CHILD, 0, 37, 185, 20, hWnd, NULL, NULL, NULL);
	Top5b = CreateWindowW(L"static", L"     Inverse edge", WS_VISIBLE | WS_CHILD, 0, 56, 185, 20, hWnd, NULL, NULL, NULL);
	Top6b = CreateWindowW(L"static", L"     Grayscale", WS_VISIBLE | WS_CHILD, 0, 75, 185, 20, hWnd, NULL, NULL, NULL);
	Top7b = CreateWindowW(L"static", L"     Inverse Grayscale", WS_VISIBLE | WS_CHILD, 0, 94, 185, 20, hWnd, NULL, NULL, NULL);
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
	TopCb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 37, 177, 1, hWnd, NULL, NULL, NULL);
	TopDb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 56, 177, 1, hWnd, NULL, NULL, NULL);
	TopEb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 75, 177, 1, hWnd, NULL, NULL, NULL);
	TopFb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 4, 94, 177, 1, hWnd, NULL, NULL, NULL);
	TopGb = CreateWindowW(L"static", L"", WS_VISIBLE | WS_CHILD | WS_BORDER, 0, 18, 190, 2, hWnd, NULL, NULL, NULL);
	FiltersDrop = TRUE;
}

void IncorrectNumBox(HWND hWnd) // Create link notif box
{
	IN1 = CreateWindowW(L"static", L"Some values are not numbers", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_RIGHT, 120, 380, 260, 20, hWnd, NULL, NULL, NULL);
	IN2 = CreateWindowW(L"static", L"ˣ", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 122, 382, 16, 16, hWnd, NULL, NULL, NULL);
	IN3 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 139, 380, 1, 20, hWnd, NULL, NULL, NULL);
	IncorrectNumberNotif = TRUE;
}

void FractDropdown(HWND hWnd) // Create Fractal dropdown menu
{
	FDdrop1 = CreateWindowW(L"static", L"˄", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
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
	CDdrop1 = CreateWindowW(L"static", L"˄", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 310, 210, 20, 20, hWnd, NULL, NULL, NULL);
	CDdrop2 = CreateWindowW(L"static", L"Default", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 229, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop3 = CreateWindowW(L"static", L"Legacy", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 248, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop4 = CreateWindowW(L"static", L"Warm colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 267, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop5 = CreateWindowW(L"static", L"Cool colors", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 286, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop6 = CreateWindowW(L"static", L"Deuteranopia", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 305, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop7 = CreateWindowW(L"static", L"Tritanopia", WS_VISIBLE | WS_BORDER | WS_CHILD, 170, 324, 141, 20, hWnd, NULL, NULL, NULL);
	CDdrop8 = CreateWindowW(L"static", L"", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_BLACKRECT, 170, 228, 141, 3, hWnd, NULL, NULL, NULL);
	ColorDrop = TRUE;
}

/*############
END WINDOW DEF
##############
START DESTROY
############*/

void DestroyFormulaMenu() // Destroy formula menu
{
	DestroyWindow(Formula1); DestroyWindow(Formula2); DestroyWindow(Formula3); DestroyWindow(Formula4);
	DestroyWindow(Formula5); DestroyWindow(Formula6); DestroyWindow(Formula7); DestroyWindow(Formula8);
	DestroyWindow(Formula9); FormulaOpen = FALSE;
}

void DestroyColorMenu() // Destroy color menu
{
	DestroyWindow(Color1); DestroyWindow(Color2); DestroyWindow(Color3); DestroyWindow(Color4);
	DestroyWindow(Color5); DestroyWindow(Color6); DestroyWindow(Color7); DestroyWindow(Color8);
	ColorOpen = FALSE;
}

void DestroyLocationMenu() // Destroy location menu
{
	DestroyWindow(Location1); DestroyWindow(Location2); DestroyWindow(Location3); DestroyWindow(Location4);
	DestroyWindow(Location5); DestroyWindow(Location6); DestroyWindow(Location7); DestroyWindow(Location8);
	LocationOpen = FALSE;
}

void DestroyHelpMenu() // Destroy help menu
{
	DestroyWindow(HelpMenu1); DestroyWindow(HelpMenu2); DestroyWindow(HelpMenu3); DestroyWindow(HelpMenu4);
	HelpOpen = FALSE;
}

void DestroyLinkNotif() // Destroy link notif
{
	DestroyWindow(Link1); DestroyWindow(Link2); DestroyWindow(Link3);
	LinkNotif = FALSE;
}

void DestroyConfigDrop(HWND hWnd) // Destroy configuration dropdown menu
{
	DestroyWindow(Top1a); DestroyWindow(Top2a); DestroyWindow(Top3a); DestroyWindow(Top4a);
	DestroyWindow(Top5a); DestroyWindow(Top6a); DestroyWindow(Top7a); DestroyWindow(Top8a);
	DestroyWindow(Top9a); DestroyWindow(Top0a);
	Top3 = CreateWindowW(L"static", L"▾", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 80, 1, 16, 16, hWnd, NULL, NULL, NULL);
	ConfigureDrop = FALSE;
}

void DestroyFiltersDrop(HWND hWnd) // Destroy filters dropdown menu
{
	DestroyWindow(Top1b); DestroyWindow(Top2b); DestroyWindow(Top3b); DestroyWindow(Top4b);
	DestroyWindow(Top5b); DestroyWindow(Top6b); DestroyWindow(Top7b); DestroyWindow(Top8b);
	DestroyWindow(Top9b); DestroyWindow(Top0b); DestroyWindow(TopAb); DestroyWindow(TopBb);
	DestroyWindow(TopCb); DestroyWindow(TopDb); DestroyWindow(TopEb); DestroyWindow(TopFb);
	DestroyWindow(TopGb);
	Top5 = CreateWindowW(L"static", L"▾", WS_VISIBLE | WS_BORDER | WS_CHILD | SS_CENTER, 149, 1, 16, 16, hWnd, NULL, NULL, NULL);
	FiltersDrop = FALSE;
}

void DestroyIncorrectNumberNotif() // Destroy incorrect number notif
{
	DestroyWindow(IN1); DestroyWindow(IN2); DestroyWindow(IN3);
	IncorrectNumberNotif = FALSE;
}

void DestroyFractDropdown(HWND hWnd) // Destroy fract dropdown
{
	DestroyWindow(FDdrop1); DestroyWindow(FDdrop2); DestroyWindow(FDdrop3); DestroyWindow(FDdrop4);
	DestroyWindow(FDdrop5); DestroyWindow(FDdrop6); DestroyWindow(FDdrop7); DestroyWindow(FDdrop8);
	DestroyWindow(FDdrop9); DestroyWindow(FDdropA); DestroyWindow(FDdropB); DestroyWindow(FDdropC);
	FractDrop = FALSE;
}

void DestroyColorDropdown(HWND hWnd) { // Destroy fract dropdown
	DestroyWindow(CDdrop1); DestroyWindow(CDdrop2); DestroyWindow(CDdrop3); DestroyWindow(CDdrop4);
	DestroyWindow(CDdrop5); DestroyWindow(CDdrop6); DestroyWindow(CDdrop7); DestroyWindow(CDdrop8);
	ColorDrop = FALSE;
}

void DestroyAll(HWND hWnd) // Destroy all menus
{
	DestroyFractDropdown(hWnd); DestroyColorDropdown(hWnd); DestroyFormulaMenu();
	DestroyColorMenu(); DestroyLocationMenu(); DestroyHelpMenu(); DestroyLinkNotif();
	DestroyConfigDrop(hWnd); DestroyFiltersDrop(hWnd); DestroyIncorrectNumberNotif();
}

/*#########################
END WINDOW DESTROY
###########################
START LOCATION MODIFICATION
#########################*/

void SetZoomDensity(INT InOut) // Set pixel density for determining distance between points
{
	if (InOut == 1) { NewZoom = NewZoom * 1.1; } // Zoom in and out
	if (InOut == 0) { NewZoom = NewZoom / 1.1; }
	PixelDif = (4 * (4 / NewZoom)) / 500; // Zoom logic, allows for non 2^n zoom levels
	LPCWSTR temp4;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(5) << NewZoom; // Set precision of window number
	const std::string string5 = stream.str(); // Convert
	const std::wstring Wtemp5(string5.begin(), string5.end());
	temp4 = (LPCWSTR)Wtemp5.c_str();
	SetWindowTextW(Info5, temp4); // Set window text
	for (int x = 0; x < 500; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			PlotPoint(x, y);
		}
	}
}

void SetLocation(INT ULDR) // Set new position on keypress
{
	if (ULDR == 2) { NewImag += PixelDif*10; } // Proper addition and subtraction
	if (ULDR == 1) { NewReal -= PixelDif*10; }
	if (ULDR == 0) { NewImag -= PixelDif*10; }
	if (ULDR == 3) { NewReal += PixelDif*10; }
	LPCWSTR temp5;
	std::stringstream stream;
	stream << std::fixed << std::setprecision(49) << NewReal; // Set precision of window number
	const std::string string5 = stream.str(); // Convert
	const std::wstring Wtemp5(string5.begin(), string5.end());
	temp5 = (LPCWSTR)Wtemp5.c_str();
	SetWindowTextW(Info2, temp5); // Set window text
	LPCWSTR temp6;
	std::stringstream stream2;
	stream2 << std::fixed << std::setprecision(33) << NewImag * -1; // Set precision of window number
	const std::string string6 = stream2.str(); // Convert
	const std::wstring Wtemp6(string6.begin(), string6.end());
	temp6 = (LPCWSTR)Wtemp6.c_str();
	SetWindowTextW(Info3, temp6); // Set window text
}

void SetRotation(INT CwCCw) // Set new rotation position
{
	if (CwCCw == 0) { Rotation += 1; }
	else { Rotation -= 1; }
	if (Rotation > 359) { Rotation = 0; }
	if (Rotation < 0) { Rotation = 359; }
	LPCWSTR temp9;
	std::wstring Wtemp9 = to_wstring(Rotation);
	temp9 = (LPCWSTR)Wtemp9.c_str();
	SetWindowTextW(Info6, temp9);
}

/*#######################
END LOCATION MODIFICATION
#########################
START ITER TABLE TO CMPLX
#######################*/

std::complex<long double> TableToComplex(INT TableX, INT TableY) // Input screen coordinates and return a complex at the given location
{
	long double TTCoutReal = NewReal;
	long double TTCoutImag = NewImag;
	if (TableX < 249)
	{
		TTCoutReal -= (PixelDif * (249 - (long double)TableX));
	}
	else {
		TTCoutReal -= (PixelDif * (249 - (long double)TableX));
	}
	if (TableY < 249)
	{
		TTCoutImag -= (PixelDif * (249 - (long double)TableY));
	}
	else {
		TTCoutImag -= (PixelDif * (249 - (long double)TableY));
	}
	std::complex<long double> ComplexOutput(TTCoutReal, TTCoutImag);
	return(ComplexOutput);
}

/*#####################
END ITER TABLE TO CMPLX
#######################
START PULL FROM ITERTBL
#####################*/

void PullFromIter()
{
	for (int x = 0; x < 500; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			ColorizePlot(ScreenSpaceIters[x][y], x, y); // Pull iteration from iteration table and send it into colorize function
		}
	}
}

/*###################
END PULL FROM ITERTBL
#####################
START SHIFT ITERTABLE
###################*/

void ShiftScreen(INT Direction) {
	if (Direction == 0) // Move pixels to the left creating space on the right
	{
		for (int x = 0; x < 489; x++)
		{
			for (int y = 0; y < 500; y++)
			{
				ScreenSpaceIters[x][y] = ScreenSpaceIters[x + 10][y];
			}
		}
		for (int x = 489; x < 500; x++)
		{
			for (int y = 0; y < 500; y++)
			{
				PlotPoint(x, y);
			}
		}
	}
	if (Direction == 1) // Move pixels to the top creating space on the bottom
	{
		for (int y = 0; y < 489; y++)
		{
			for (int x = 0; x < 500; x++)
			{
				ScreenSpaceIters[x][y] = ScreenSpaceIters[x][y + 10];
			}
		}
		for (int x = 0; x < 500; x++)
		{
			for (int y = 489; y < 500; y++)
			{
				PlotPoint(x, y);
			}
		}
	}
	if (Direction == 2) // Move pixels to the right creating space on the left
	{
	for (int x = 0; x < 489; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			ScreenSpaceIters[(489 - x) + 10][y] = ScreenSpaceIters[(489 - x)][y];
		}
	}
	for (int x = 0; x < 11; x++)
	{
		for (int y = 0; y < 500; y++)
		{
			PlotPoint(x, y);
		}
	}
	}
	if (Direction == 3) // Move pixels to the bottom creating space on the top
	{
		for (int y = 0; y < 489; y++)
		{
			for (int x = 0; x < 500; x++)
			{
				ScreenSpaceIters[x][(489 - y) + 10] = ScreenSpaceIters[x][(489 - y)];
			}
		}
		for (int x = 0; x < 500; x++)
		{
			for (int y = 0; y < 11; y++)
			{
				PlotPoint(x, y);
			}
		}
	}
}

/*###################
END SHIFT ITERTABLE
#####################
START MAIN COLOR FUNC
###################*/

void ColorizePlot(INT Iterations, INT X, INT Y)
{
	if (SmoothColor == FALSE && (Filters[0] || Filters[1] || Filters[2] || Filters[3] || Filters[4]) == FALSE)
	{
		sf::Color BandedColor;
		if (ColorType == 0)
		{
			sf::Color Type1[32] = { sf::Color(255, 25, 0), sf::Color(255, 70, 0), sf::Color(255, 116, 0), sf::Color(255, 162, 0), sf::Color(255, 209, 0), sf::Color(249, 249, 0),
									sf::Color(209, 255, 0), sf::Color(162, 255, 0), sf::Color(116, 255, 0), sf::Color(70, 255, 0), sf::Color(25, 255, 0), sf::Color(0, 255, 29),
									sf::Color(0, 255, 74), sf::Color(0, 255, 120), sf::Color(0, 255, 167), sf::Color(0, 247, 251), sf::Color(0, 205, 255), sf::Color(0, 158, 255),
									sf::Color(0, 112, 255), sf::Color(0, 65, 255), sf::Color(0, 21, 255), sf::Color(33, 0, 255), sf::Color(78, 0, 255), sf::Color(124, 0, 255),
									sf::Color(171, 0, 255), sf::Color(217, 0, 255), sf::Color(253, 0, 245), sf::Color(255, 0, 200), sf::Color(255, 0, 154), sf::Color(255, 0, 107),
									sf::Color(255, 0, 61) }; // Color preset 1 to somewhat cycle through all RGB values
			BandedColor = Type1[Iterations % 31];
		}
		if (ColorType == 1)
		{
			sf::Color Type2[8] = { sf::Color(0, 0, 0), sf::Color(255, 0, 0), sf::Color(255, 165, 0), sf::Color(255, 255, 0),
								   sf::Color(0, 128, 0), sf::Color(0, 0, 255), sf::Color(238, 130, 238), sf::Color(128, 128, 128) };
			// Color Preset 2 to cycle through all values from /PyFractalRenderer
			BandedColor = Type2[Iterations % 7];
		}
		if (ColorType == 2)
		{
			sf::Color Type3[16] = { sf::Color(255, 25, 0), sf::Color(255, 70, 0), sf::Color(255, 116, 0), sf::Color(255, 162, 0), sf::Color(255, 209, 0), sf::Color(249, 249, 0),
									sf::Color(209, 255, 0), sf::Color(162, 255, 0), sf::Color(116, 255, 0), sf::Color(162, 255, 0), sf::Color(209, 255, 0), sf::Color(249, 249, 0),
									sf::Color(255, 209, 0), sf::Color(255, 162, 0), sf::Color(255, 116, 0), sf::Color(255, 70, 0) }; // Filter through all "warm" colors of preset 1
			BandedColor = Type3[Iterations % 15];
		}
		if (ColorType == 3)
		{
			sf::Color Type4[18] = { sf::Color(0, 255, 167), sf::Color(0, 247, 251), sf::Color(0, 205, 255), sf::Color(0, 158, 255), sf::Color(0, 112, 255), sf::Color(0, 65, 255),
									sf::Color(0, 21, 255), sf::Color(33, 0, 255), sf::Color(78, 0, 255), sf::Color(124, 0, 255), sf::Color(78, 0, 255), sf::Color(33, 0, 255),
									sf::Color(0, 21, 255), sf::Color(0, 65, 255), sf::Color(0, 112, 255), sf::Color(0, 158, 255), sf::Color(0, 205, 255), sf::Color(0, 247, 251) };
			// Filter through all "cool" colors of preset 1
			BandedColor = Type4[Iterations % 17];
		}
		if (ColorType == 4)
		{
			sf::Color Type5[32] = { sf::Color(164, 123, 0), sf::Color(175, 132, 0), sf::Color(199, 149, 0), sf::Color(232, 174, 0), sf::Color(255, 206, 124), sf::Color(255, 239, 219),
									sf::Color(255, 234, 207), sf::Color(255, 224, 183), sf::Color(255, 217, 163), sf::Color(255, 213, 150), sf::Color(255, 211, 144), sf::Color(255, 211, 144),
									sf::Color(255, 211, 149), sf::Color(255, 212, 161), sf::Color(255, 214, 182), sf::Color(247, 217, 222), sf::Color(224, 216, 254), sf::Color(165, 185, 255),
									sf::Color(81, 153, 253), sf::Color(0, 112, 210), sf::Color(0, 96, 160), sf::Color(0, 81, 135), sf::Color(0, 81, 134), sf::Color(0, 87, 146),
									sf::Color(0, 99, 167), sf::Color(0, 115, 197), sf::Color(26, 133, 232), sf::Color(94, 144, 230), sf::Color(126, 137, 188), sf::Color(144, 131, 143),
									sf::Color(155, 126, 96) }; // Color preset 5 to simulate Deuteranopia
			BandedColor = Type5[Iterations % 31];
		}
		if (ColorType == 5)
		{
			sf::Color Type6[32] = { sf::Color(254, 29, 17), sf::Color(255, 66, 69), sf::Color(255, 110, 117), sf::Color(255, 155, 164), sf::Color(255, 199, 210), sf::Color(255, 236, 247),
									sf::Color(230, 237, 255), sf::Color(191, 237, 255), sf::Color(156, 237, 255), sf::Color(129, 236, 255), sf::Color(115, 236, 255), sf::Color(114, 236, 255),
									sf::Color(116, 237, 255), sf::Color(122, 238, 255), sf::Color(131, 239, 255), sf::Color(143, 241, 255), sf::Color(124, 239, 254), sf::Color(0, 208, 225),
									sf::Color(0, 169, 181), sf::Color(0, 132, 140), sf::Color(0, 103, 108), sf::Color(0, 87, 91), sf::Color(0, 87, 91), sf::Color(0, 94, 100),
									sf::Color(81, 99, 107), sf::Color(144, 100, 107), sf::Color(198, 100, 107), sf::Color(238, 96, 102), sf::Color(246, 79, 83), sf::Color(250, 61, 63),
									sf::Color(253, 43, 41) }; // Color preset 5 to simulate Tritanopia
			BandedColor = Type6[Iterations % 31];
		}
		if (ScreenSpaceIters[X][Y] == Iters) { BandedColor = sf::Color(0, 0, 0); }
		ImageMain.setPixel(X, Y, BandedColor);
	}
}

/*###################
END MAIN COLOR FUNCTN
#####################
START DRAW POINT FUNC
###################*/

void PlotPoint(INT x, INT y)
{
	std::complex<long double> CPoint = TableToComplex(x, y);
	std::complex<long double> IteratePoint(0, 0);
	int count = 0;
	long double zi = 0, zr = 0, zisqr = 0, zrsqr = 0;

	if (RealFractalType == 1) // Mandelbrot set
	{
		long double q = ((CPoint.real() - 0.25) * (CPoint.real() - 0.25)) + (CPoint.imag() * CPoint.imag());
		if ((q * (q + (CPoint.real() - 0.25)) <= (0.25 * (CPoint.imag() * CPoint.imag()))) || (((CPoint.real() + 1) * (CPoint.real() + 1)) + (CPoint.imag() * CPoint.imag())) <= 0.0625)
		{
			count = Iters;
		}
		else {
			while (((zi * zi) + (zr * zr) < 4) && count < Iters)
			{
				zi = zr * zi * 2 + CPoint.imag();
				zr = zrsqr - zisqr + CPoint.real();
				zisqr = zi * zi;
				zrsqr = zr * zr;
				count++;
			}
		}
	}
	if (RealFractalType == 2) // Burning ship
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = abs(zr * zi) * 2 + CPoint.imag();
			zr = zrsqr - zisqr + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 3) // Buffalo
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = abs(zr * zi) * 2 + CPoint.imag();
			zr = abs(zrsqr - zisqr) + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 4) // Celtic
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = zr * zi * 2 + CPoint.imag();
			zr = abs(zrsqr - zisqr) + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 5) // Mandelbar
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = zr * zi * -2 + CPoint.imag();
			zr = zrsqr - zisqr + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 6) // Mandelbar celtic
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = zr * zi * -2 + CPoint.imag();
			zr = abs(zrsqr - zisqr) + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 7) // Perp mandelbrot
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = abs(zr) * zi * -2 + CPoint.imag();
			zr = zrsqr - zisqr + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 8) // Perpendicular burning
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = zr * abs(zi) * -2 + CPoint.imag();
			zr = zrsqr - zisqr + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 9) // Perpendicular buffalo
	{
		while(((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = zr * abs(zi) * 2 + CPoint.imag();
			zr = abs(zrsqr - zisqr) + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	if (RealFractalType == 10) // Perpendicular celtic
	{
		while (((zi * zi) + (zr * zr) < 4) && count < Iters)
		{
			zi = abs(zr) * zi * -2 + CPoint.imag();
			zr = abs(zrsqr - zisqr) + CPoint.real();
			zisqr = zi * zi;
			zrsqr = zr * zr;
			count++;
		}
	}
	ScreenSpaceIters[x][y] = count;
}
