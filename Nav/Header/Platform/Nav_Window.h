#ifndef NAV_WINDOW_H
#define NAV_WINDOW_H

#include <nav_api.h>
#include <math/nav_bit.h>
#include <math/nav_value_type.h>
#include <math/nav_vector.h>

struct Nav_WindowType;
typedef struct Nav_WindowType Nav_Window;

NAV_API Nav_Window* Nav_Window_Create(char* wndTitle, int width, int height);

NAV_API void Nav_Window_Destroy(Nav_Window* wndPtr);

NAV_API char Nav_Window_UpdateEvents(Nav_Window* wnd);

NAV_API void Nav_Window_SetCanClose(Nav_Window* window, Bool canClose);

NAV_API IntVector2 Nav_Window_GetClientSize(Nav_Window* window);

NAV_API void Nav_Window_SetClientSize(Nav_Window* window, IntVector2 newWndSize);

NAV_API IntVector2 Nav_Window_GetPosition(Nav_Window* window);

#endif