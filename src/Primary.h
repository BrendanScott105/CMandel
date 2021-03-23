#pragma once
#include <windows.h> //include
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
void DestroyFFNotif();
void DestroyAll(HWND); //Declare existence
void FFMPEGBox(HWND);

void SetZoomDensity(INT); // Declare
void SetLocation(INT); // Declare
void SetRotation(INT); // Declare

void ShiftScreen(INT); // Declare

void PlotPoint(INT, INT);

void NaiveThread1(); // Declare thread
void NaiveThread2(); // Declare thread
void NaiveThread3(); // Declare thread
void NaiveThread4(); // Declare thread

void NaiveThread100();
void NaiveThread101();
void NaiveThread102();
void NaiveThread103();
void NaiveThread104();
void NaiveThread105();
void NaiveThread106();
void NaiveThread107();
void NaiveThread108();
void NaiveThread109();

int CaptureAnImage(HWND);
void getCurrentValue();

void DrawTwenty(INT, INT);

void RenderThreads();

DWORD tickThreadProc(HANDLE);

wstring s2ws(std::string);

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
HWND FF1, FF2, FF3;
HWND RealWinMain; // Declare main window
HWND SubWin;

BOOL FormulaOpen;
BOOL ColorOpen;
BOOL LocationOpen;
BOOL HelpOpen;
BOOL LinkNotif;
BOOL ConfigureDrop;
BOOL FiltersDrop;
BOOL IncorrectNumberNotif;
BOOL FFMPEGBoxNotif;
BOOL FractDrop = FALSE;
BOOL ColorDrop = FALSE;
BOOL SmoothColor = FALSE;

POINT Cursor;
ULONG_PTR GdiToken;
PAINTSTRUCT ps;

BOOL ScreenMirror = FALSE;
BOOL JuliaMode = FALSE;
INT FractalType = 1;
INT ColorType = 0;
INT zoomin = 14;
INT FrameCount;
INT Bailout = 4;
FLOAT ZoomOutSize = 1.1;

int RColor;
int GColor;
int BColor;
int Cycle;

static ULARGE_INTEGER lastCPU, lastSysCPU, lastUserCPU;
static int numProcessors;
static HANDLE self;
/*Window variables end*/

/*Fractal variable definitions start*/
int Iters = 200; // define iterations
long double PixelDif = 0.008;
BOOL Filters[5] = { FALSE,FALSE,FALSE,FALSE,FALSE }; // Decolorize, Edge detect, Color Cycle, Grayscale, Inverse Grayscale
long double NewReal = 0; long double NewImag = 0; long double NewZoom = 4; int Rotation = 0;
INT RealFractalType = 1;

int ScreenSpaceIters[500][500];
float Smooth[500][500];
/*Fractal variables end*/

INT SYSTEMTHREADS = std::thread::hardware_concurrency();

/*FAST DRAW LOGIC*/

struct pixel {
	union {
		struct {
			/* 'a' unused, used for 32-bit alignment,
			 * could also be used to store pixel alpha
			 */
			unsigned char b, g, r, a;
		};
		int val;
	};

	pixel() {
		val = 0;
	}
};

const int width = 500;
const int height = 500;

const int fps = 60;

HBITMAP hbmp;
HANDLE hTickThread;
HDC hdcMem;

pixel* pixels;

HDC hdc = GetDC(RealWinMain);

void NaiveThread1()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 4 == 0) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 4 == 0) {
					PlotPoint(x, y);
				}
			}
		}
	}
}

void NaiveThread2()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 4 == 1) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 4 == 1) {
					PlotPoint(x, y);
				}
			}
		}
	}
}

void NaiveThread3()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 4 == 2) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 4 == 2) {
					PlotPoint(x, y);
				}
			}
		}
	}
}

void NaiveThread4()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 4 == 3) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 4 == 3) {
					PlotPoint(x, y);
				}
			}
		}
	}
}

void NaiveThread100()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 0) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 0) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread101()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 1) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 1) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread102()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 2) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 2) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread103()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 3) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 3) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread104()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 4) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 4) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread105()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 5) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 5) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread106()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 6) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 6) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread107()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 7) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 7) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread108()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 8) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 8) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
void NaiveThread109()
{
	if (SmoothColor == FALSE && ScreenMirror == FALSE)
	{
		for (int x = 0; x < 20; x++) {
			for (int y = 0; y < 20; y++) {
				if (x % 10 == 9) {
					DrawTwenty(x, y);
				}
			}
		}
	}
	else
	{
		for (int x = 0; x < 500; x++) {
			for (int y = 0; y < 500; y++) {
				if (x % 10 == 9) {
					PlotPoint(x, y);
				}
			}
		}
	}
}
