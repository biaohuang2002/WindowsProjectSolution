// HelloWindowsDesktop.cpp
// compile with: /D_UNICODE /DUNICODE /DWIN32 /D_WINDOWS /c

#include "DesktopApp.h"
#include "TestLibrary.h"

// Global variables

// The main window class name.
static TCHAR szWindowClass[] = _T("DesktopApp");

// The string that appears in the application's title bar.
static TCHAR szTitle[] = _T("Windows Desktop Guided Tour Application");

// Stored instance handle for use in Win32 API calls such as FindResource
HINSTANCE hInst;

// Forward declarations of functions included in this code module:
LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK About(HWND, UINT, WPARAM, LPARAM);
wstring StringToWstring(const string&);

int WINAPI WinMain(
  _In_ HINSTANCE hInstance,
  _In_opt_ HINSTANCE hPrevInstance,
  _In_ LPSTR     lpCmdLine,
  _In_ int       nCmdShow
)
{
  WNDCLASSEX wcex;

  wcex.cbSize = sizeof(WNDCLASSEX);
  wcex.style = CS_HREDRAW | CS_VREDRAW;
  wcex.lpfnWndProc = WndProc;
  wcex.cbClsExtra = 0;
  wcex.cbWndExtra = 0;
  wcex.hInstance = hInstance;
  wcex.hIcon = LoadIcon(wcex.hInstance, IDI_APPLICATION);
  wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
  wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wcex.lpszMenuName = MAKEINTRESOURCEW(IDR_MENU1);
  wcex.lpszClassName = szWindowClass;
  wcex.hIconSm = LoadIcon(wcex.hInstance, IDI_APPLICATION);

  if (!RegisterClassEx(&wcex))
  {
    MessageBox(NULL,
      _T("Call to RegisterClassEx failed!"),
      _T("Windows Desktop Guided Tour"),
      NULL);

    return 1;
  }

  // Store instance handle in our global variable
  hInst = hInstance;

  // The parameters to CreateWindowEx explained:
  // WS_EX_OVERLAPPEDWINDOW : An optional extended window style.
  // szWindowClass: the name of the application
  // szTitle: the text that appears in the title bar
  // WS_OVERLAPPEDWINDOW: the type of window to create
  // CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)
  // 500, 100: initial size (width, length)
  // NULL: the parent of this window
  // NULL: this application does not have a menu bar
  // hInstance: the first parameter from WinMain
  // NULL: not used in this application
  HWND hWnd = CreateWindowEx(
    WS_EX_OVERLAPPEDWINDOW,
    szWindowClass,
    szTitle,
    WS_OVERLAPPEDWINDOW,
    CW_USEDEFAULT, 0, CW_USEDEFAULT, 0,
    NULL,
    NULL,
    hInstance,
    NULL
  );

  if (!hWnd)
  {
    MessageBox(NULL,
      _T("Call to CreateWindow failed!"),
      _T("Windows Desktop Guided Tour"),
      NULL);

    return 1;
  }

  // The parameters to ShowWindow explained:
  // hWnd: the value returned from CreateWindow
  // nCmdShow: the fourth parameter from WinMain
  ShowWindow(hWnd,
    nCmdShow);
  UpdateWindow(hWnd);

  // Main message loop:
  MSG msg;
  while (GetMessage(&msg, NULL, 0, 0))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }

  return (int)msg.wParam;
}

//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
  PAINTSTRUCT ps;
  HDC hdc;
  TCHAR greeting[] = _T("Hello, Windows desktop!");

  switch (message)
  {
  case WM_COMMAND:
    {
      int wmId = LOWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
      case ID_HELP_ABOUT:
        DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hWnd, About);
        break;
      case ID_FILE_EXIT:
        DestroyWindow(hWnd);
        break;
      case ID_TEST_DLL1:
        MessageBox(NULL,
          StringToWstring(TestFirst("First")).c_str(),
          _T("Test"),
          NULL);
        break;
      case ID_TEST_DLL2:
        MessageBox(NULL,
          StringToWstring(TestSecond("Second")).c_str(),
          _T("Test"),
          NULL);
        break;
      case ID_TEST_DLL3:
        MessageBox(NULL,
          StringToWstring(TestThird("Third")).c_str(),
          _T("Test"),
          NULL);
        break;
      default:
        return DefWindowProc(hWnd, message, wParam, lParam);
      }
    }
    break;
  case WM_PAINT:
    hdc = BeginPaint(hWnd, &ps);

    // Here your application is laid out.
    // For this introduction, we just print out "Hello, Windows desktop!"
    // in the top left corner.
    TextOut(hdc,
      5, 5,
      greeting, _tcslen(greeting));
    // End application-specific layout section.

    EndPaint(hWnd, &ps);
    break;
  case WM_DESTROY:
    PostQuitMessage(0);
    break;
  default:
    return DefWindowProc(hWnd, message, wParam, lParam);
    break;
  }

  return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
  HWND hwndText;
  UNREFERENCED_PARAMETER(lParam);

  switch (message)
  {
  case WM_INITDIALOG:
    hwndText = GetDlgItem(hDlg, IDC_STATIC);
    InvalidateRect(hwndText, NULL, true);
    SetWindowText(hwndText, L"Hi sir, this is my first text box!");
    return (INT_PTR)TRUE;

  case WM_COMMAND:
    if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
    {
      EndDialog(hDlg, LOWORD(wParam));
      return (INT_PTR)TRUE;
    }
    break;
  }
  return (INT_PTR)FALSE;
}

wstring StringToWstring(const string& text) {
  return wstring(text.begin(), text.end());
}
