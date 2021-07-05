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
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
    }

    return 0;
}

int WINAPI WinMain(HINSTANCE hInst,
                   HINSTANCE hPrevInst,
                   LPSTR lpCmdLine,
                   int iCmdShow)
{
    WNDCLASSEX wcx;
    HWND hWnd;
    MSG  msg;
    RECT rect;

    wcx.lpszClassName = "WndClass";
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

    if (!RegisterClassEx(&wcx)) {
        MessageBox(NULL, "Failed to register window class.", NULL,
                   MB_ICONEXCLAMATION);
        return FALSE;
    }

    SystemParametersInfo(SPI_GETWORKAREA, 0, &rect, 0);

    hWnd = CreateWindowEx(WS_EX_CLIENTEDGE,
                          "WndClass",
                          "Window Title",
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
        MessageBox(NULL, "Failed to create window.", NULL, MB_ICONEXCLAMATION);
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
