#include <platform/nav_window.h>
#include <nav_debug.h>
#include <stdlib.h>


int main(int argc, char** argv)
{
    Window* wnd = NavCreateWindow("nav", 600, 400);

    DEBUG_LOG(DECIMAL_LOG_FORMAT, WHITE_CONSOLE_COLOR, __STDC_VERSION__)

    while(UpdateWindowEvents(wnd))
    {
        Sleep(10);
    }

    NavDestroyWindow(wnd);

    return 0;
}
