#ifndef NAV_WINDOW_H
#define NAV_WINDOW_H

#include <nav_api.h>

struct WindowType;
typedef struct WindowType Window;

NAV_API Window* NavCreateWindow(char* wndTitle, int width, int height);
NAV_API void NavDestroyWindow(Window* wndPtr);

NAV_API char UpdateWindowEvents(Window* wnd);

#endif