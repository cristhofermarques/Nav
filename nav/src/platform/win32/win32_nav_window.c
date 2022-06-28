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
            DEBUG_INFO("WM_CLOSE event");
            PostMessageA(hWnd, NAV_WND_CLOSE, 0, 0);
            return 0;
        break;

        default:
            return DefWindowProc(hWnd, msg, wParam, lParam);
    }

}

Window* NavCreateWindow(char* wndTitle, int width, int height) 
{
    HINSTANCE hinstance = GetModuleHandle(NULL);

    WNDCLASSEXA wndClassExA = {0};
    wndClassExA.lpfnWndProc = NavWindowProc;
    wndClassExA.style = CS_OWNDC;
    wndClassExA.cbClsExtra = 0;
    wndClassExA.cbWndExtra = 0;
    wndClassExA.cbSize = sizeof(WNDCLASSEXA);
    wndClassExA.hInstance = hinstance;
    wndClassExA.lpszClassName = nav_wnd_class;
    wndClassExA.hIcon = LoadIcon(wndClassExA.hInstance, IDI_APPLICATION);
    wndClassExA.hCursor = LoadCursor(wndClassExA.hInstance, IDC_ARROW);

    if(! GetClassInfoExA(hinstance, nav_wnd_class, &wndClassExA))
    {
        DEBUG_LOG(STRING_LOG_FORMAT, WHITE_CONSOLE_COLOR, "registering nav window class");

        if(! RegisterClassExA(&wndClassExA))
        {

            DEBUG_LOG(STRING_LOG_FORMAT DECIMAL_LOG_FORMAT, WHITE_CONSOLE_COLOR, "falied to register nav window class", GetLastError());
            return NULL;
        }

        DEBUG_LOG(STRING_LOG_FORMAT, WHITE_CONSOLE_COLOR, "nav window class registered");
    }

    HWND hwnd = CreateWindowExA(0, nav_wnd_class, wndTitle, WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0, 0, width, height, NULL, NULL, hinstance, 0);

    if(!hwnd)
    {
        DEBUG_ERROR("falied create window");
        return NULL;
    }
    
    Window* wnd = malloc(sizeof(Window));

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
        free(wndptr);
    }
}

char UpdateWindowEvents(Window* wnd)
{
    MSG msg;
    HWND hWnd = wnd->hwnd;
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