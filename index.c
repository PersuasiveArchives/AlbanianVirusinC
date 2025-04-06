#define _WIN32_WINNT 0x0501

#include <windows.h>
#include <stdio.h> // For sprintf

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    const char CLASS_NAME[]  = "GenericErrorClass";
    char errorTitle[256];
    char errorMessage[512];

    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;

    if (!RegisterClass(&wc))
    {
        sprintf(errorTitle, "Error");
        sprintf(errorMessage, "Failed to register window class. Error code: %lu", GetLastError());
        MessageBox(NULL, errorMessage, errorTitle, MB_OK | MB_ICONERROR);
        return -1;
    }

    HWND hwnd = CreateWindowEx(
        0,
        CLASS_NAME,
        "An Error Has Occurred", // Generic title
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL)
    {
        sprintf(errorTitle, "Error");
        sprintf(errorMessage, "Failed to create window. Error code: %lu", GetLastError());
        MessageBox(NULL, errorMessage, errorTitle, MB_OK | MB_ICONERROR);
        return -1;
    }

    // Customize button text and message based on the specific error if needed
    CreateWindow("BUTTON", "OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
               150, 150, 100, 30, hwnd, (HMENU)1, hInstance, NULL);

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = {0};
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int) msg.wParam;
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        CreateWindow("STATIC", "A generic error has occurred. Please try again or contact support if the issue persists.",
                   WS_VISIBLE | WS_CHILD | SS_CENTER | SS_WORDBREAK,
                   50, 50, 300, 80, hwnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        break;

    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1: // ID for the "OK" button
            PostMessage(hwnd, WM_CLOSE, 0, 0);
            break;
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}
