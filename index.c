#define _WIN32_WINNT 0x0501

#include <windows.h>

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pCmdLine, int nCmdShow)
{
    const char CLASS_NAME[]  = "Sample Window Class";
    
    WNDCLASS wc = {0};
    wc.lpfnWndProc   = WindowProc;
    wc.hInstance     = hInstance;
    wc.lpszClassName = CLASS_NAME;
    
    if (!RegisterClass(&wc))
    {
        return -1;
    }

    HWND hwnd = CreateWindowEx(
        0,                     
        CLASS_NAME,            
        "Virus Alert !",             
        WS_OVERLAPPEDWINDOW,   
        CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
        NULL,                  
        NULL,                  
        hInstance,            
        NULL                   
    );

    if (hwnd == NULL)
    {
        return -1;
    }

    CreateWindow("BUTTON", "Yes", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 50, 150, 100, 30, hwnd, (HMENU)1, hInstance, NULL);
    CreateWindow("BUTTON", "No", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 160, 150, 100, 30, hwnd, (HMENU)2, hInstance, NULL);
    CreateWindow("BUTTON", "Cancel", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                 270, 150, 100, 30, hwnd, (HMENU)3, hInstance, NULL);

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
        CreateWindow("STATIC", "Hi, I am an Albanian virus but because of poor technology in my country unfortunately I am not able to harm your computer. Please be so kind to delete one of your important files yourself and then forward me to other users. Many thanks for your cooperation! Best regards, Albanian virus", 
                     WS_VISIBLE | WS_CHILD | SS_CENTER,
                     50, 50, 300, 50, hwnd, (HMENU)0, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        break;
    
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case 1: 
        case 2: 
        case 3: 
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
