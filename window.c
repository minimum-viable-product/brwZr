#include <windows.h>


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg) {
        case WM_CLOSE:
            DestroyWindow(hWnd);
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcW(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}


INT WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPrevInst,
                   LPSTR lpCmdLine,
                   int iCmdShow)
{
    WNDCLASSEXW wndclass;
    HWND hWnd;
    MSG  msg;
    RECT rect;

    /* Get args as wide characters for old mingw/gcc compatibility */
    LPWSTR lpwsCmdLine = GetCommandLineW();

    wndclass.lpszClassName = L"WndClass";
    wndclass.lpfnWndProc   = WndProc;
    wndclass.hInstance     = hInst;
    wndclass.hCursor       = NULL;
    wndclass.hIcon         = NULL;
    wndclass.hIconSm       = NULL;
    wndclass.hbrBackground = GetStockObject(DKGRAY_BRUSH);
    wndclass.lpszMenuName  = NULL;
    wndclass.style         = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
    wndclass.cbClsExtra    = 0;
    wndclass.cbWndExtra    = 0;
    wndclass.cbSize        = sizeof (wndclass);

    if (!RegisterClassExW(&wndclass)) {
        MessageBoxW(NULL,
                    L"Failed to register window class.",
                    NULL,
                    MB_ICONEXCLAMATION);
        return FALSE;
    }

    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

    hWnd = CreateWindowExW(WS_EX_CLIENTEDGE,     /* extended window style */
                           L"WndClass",          /* class atom            */
                           L"brwZr",             /* window title          */
                           WS_OVERLAPPEDWINDOW,  /* style of the window   */
                           rect.left+15,         /* X (upper-left corner) */
                           rect.top+15,          /* Y (upper-left corner) */
                           rect.right-30,        /* width                 */
                           rect.bottom-60,       /* height                */
                           NULL,                 /* handle to parent      */
                           NULL,                 /* handle to menu        */
                           hInst,                /* handle to instance    */
                           NULL);                /* additional data       */

    if (hWnd == NULL) {
        MessageBoxW(NULL,
                    L"Failed to create window.",
                    NULL,
                    MB_ICONEXCLAMATION);
        return FALSE;
    }

    ShowWindow(hWnd, iCmdShow);
    UpdateWindow(hWnd);

    while(GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}
