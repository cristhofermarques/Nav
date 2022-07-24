#include <Nav_Debug.h>
#include <Platform/Nav_Window.h>
#include <Platform/Win32/Win32_Nav_Window_Struct.h>
#include <windows.h>

const char* nav_wnd_class = "nav_wnd_class";
const UINT NAV_WND_CLOSE = WM_USER + 1;

LRESULT CALLBACK Nav_Window_Procedure(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
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

NavWindow* Nav_Window_Create(char* wndTitle, int width, int height) 
{
    HINSTANCE hInstance = GetModuleHandle(NULL);

    WNDCLASSEX wndClassExA = {0};
    wndClassExA.cbSize = sizeof(WNDCLASSEX);
    wndClassExA.style = CS_OWNDC;
    wndClassExA.lpfnWndProc = Nav_Window_Procedure;
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
    
    NavWindow* wnd = malloc(sizeof(NavWindow));

    if(wnd == NULL)
    {
        DEBUG_ERROR("falied allocate window memory");
        return NULL;
    }
    HDC hDc = GetWindowDC(hWnd);
    
    wnd->hWnd = hWnd;
    wnd->hDc = hDc;

    return wnd;
}

void Nav_Window_Destroy(NavWindow* wnd)
{
    if(wnd != NULL)
    {
        DestroyWindow(wnd->hWnd);
        free(wnd);
    }
}

Bool Nav_Window_UpdateEvents(NavWindow* wnd)
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

void Nav_Window_SetCanClose(NavWindow* wnd, Bool canClose)
{
    //TODO : add a check to compare if current state can close is the same as 'canClose' param

    if(canClose)
    {
        NAV_BIT_ENABLE(wnd->state, NAV_WINDOW_STATE_CAN_CLOSE_BIT);
    }
    else
    {
        NAV_BIT_DISABLE(wnd->state, NAV_WINDOW_STATE_CAN_CLOSE_BIT);
    }
}

IntVector2 Nav_Window_GetClientSize(NavWindow* wnd)
{
    IntVector2 wndClientSize = (IntVector2){-1, -1};

    if(wnd == NullPtr){return wndClientSize;}

    RECT wndRect = {0};

    if(GetClientRect(wnd->hWnd, &wndRect))
    {
        wndClientSize.x = wndRect.right - wndRect.left;
        wndClientSize.y = wndRect.bottom - wndRect.top;
    }

    return wndClientSize;
}

void Nav_Window_SetClientSize(NavWindow* wnd, IntVector2 newWndSize)
{
        
}

IntVector2 Nav_Window_GetPosition(NavWindow* wnd)
{
    IntVector2 wndPos = (IntVector2){-1, -1};

    if(wnd == NullPtr){return wndPos;}

    RECT wndRect = {0};

    if(GetClientRect(wnd->hWnd, &wndRect))
    {
        wndPos.x = wndRect.left;
        wndPos.y = wndRect.top;
    }

    return wndPos;
}