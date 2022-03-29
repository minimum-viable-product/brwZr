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

INT WINAPI wWinMain(HINSTANCE hInst,
                    HINSTANCE hPrevInst,
                    LPSTR lpCmdLine,
                    int iCmdShow)
{
    WNDCLASSEXW wcx;
    HWND hWnd;
    MSG  msg;
    RECT rect;

    wcx.lpszClassName = L"WndClass";
    wcx.lpfnWndProc   = WndProc;
    wcx.hInstance     = hInst;
    wcx.hCursor       = NULL;
    wcx.hIcon         = NULL;
    wcx.hIconSm       = NULL;
    wcx.hbrBackground = GetStockObject(DKGRAY_BRUSH);
    wcx.lpszMenuName  = NULL;
    wcx.style         = CS_HREDRAW | CS_VREDRAW | CS_PARENTDC;
    wcx.cbClsExtra    = 0;
    wcx.cbWndExtra    = 0;
    wcx.cbSize        = sizeof (wcx);

    if (!RegisterClassExW(&wcx)) {
        MessageBoxW(NULL,
                    L"Failed to register window class.",
                    NULL,
                    MB_ICONEXCLAMATION);
        return FALSE;
    }

    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

    hWnd = CreateWindowExW(WS_EX_CLIENTEDGE,
                           L"WndClass",
                           L"Window Title",
                           WS_OVERLAPPEDWINDOW,
                           rect.left+15,
                           rect.top+15,
                           rect.right-30,
                           rect.bottom-60,
                           NULL,
                           NULL,
                           hInst,
                           NULL);

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
