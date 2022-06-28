#include <nav_debug.h>
#include <platform/nav_window.h>
#include <platform/win32/win32_nav_window_struct.h>
#include <windows.h>

const char* nav_wnd_class = "nav_wnd_class";
const UINT NAV_WND_CLOSE = WM_USER + 1;

LRESULT CALLBACK NavWindowProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_CLOSE :
            DEBUG_INFO("close");
            PostMessage(hWnd, NAV_WND_CLOSE, 0, 0);
            return 0;
        break;

        case WM_QUIT :
            DEBUG_INFO("quit");
            PostMessage(hWnd, NAV_WND_CLOSE, 0, 0);
            return 0;
        break;
    }

    return DefWindowProc(hWnd, msg, wParam, lParam);

}

Window* NavCreateWindow(char* wndTitle, int width, int height) 
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wndClassExA = {0};
    wndClassExA.cbSize = sizeof(WNDCLASSEX);
    wndClassExA.style = CS_OWNDC;
    wndClassExA.lpfnWndProc = NavWindowProc;
    wndClassExA.cbClsExtra = 0;
    wndClassExA.cbWndExtra = 0;
    wndClassExA.hInstance = hInstance;
    wndClassExA.hIcon = 0;
    wndClassExA.hCursor = 0;
    wndClassExA.lpszMenuName = 0;
    wndClassExA.hbrBackground = 0;
    wndClassExA.lpszClassName = nav_wnd_class;

    if(! GetClassInfoEx(hInstance, nav_wnd_class, &wndClassExA))
    {
        DEBUG_LOG(STRING_LOG_FORMAT, WHITE_CONSOLE_COLOR, "registering nav window class");

        if(! RegisterClassEx(&wndClassExA))
        {

            DEBUG_LOG(STRING_LOG_FORMAT DECIMAL_LOG_FORMAT, WHITE_CONSOLE_COLOR, "falied to register nav window class", GetLastError());
            return NULL;
        }

        DEBUG_LOG(STRING_LOG_FORMAT, WHITE_CONSOLE_COLOR, "nav window class registered");
    }

    HWND hWnd = CreateWindowEx(0, nav_wnd_class, wndTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, width, height, NULL, NULL, hInstance, NULL);

    if(!hWnd)
    {
        DEBUG_ERROR("falied create window");
        return NULL;
    }
    
    Window* wnd = malloc(sizeof(Window));
    wnd->hWnd = hWnd;

    if(wnd == NULL)
    {
        DEBUG_ERROR("falied allocate window memory");
        return NULL;
    }

    return wnd;
}

void NavDestroyWindow(Window* wndptr)
{
    if(wndptr != NULL)
    {
        DestroyWindow(wndptr->hWnd);
        free(wndptr);
    }
}

char UpdateWindowEvents(Window* wnd)
{
    MSG msg;
    HWND hWnd = wnd->hWnd;
    while(PeekMessage(&msg, hWnd, 0, 0, PM_REMOVE))
    {
        if(msg.message == NAV_WND_CLOSE)
        {
            DEBUG_INFO("NAV_WND_CLOSE event");
            return 0;
        }

        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 1;
}