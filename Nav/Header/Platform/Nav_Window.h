#ifndef NAV_WINDOW_H
#define NAV_WINDOW_H

#include <Nav_Api.h>
#include <Math/Nav_Bit.h>
#include <Types/Nav_Value_Type.h>
#include <Types/Nav_Vector.h>

enum NavWindowStyleEnum
{
    NAV_WINDOW_STYLE_BORDER_COMPLETE = 0x01,
    NAV_WINDOW_STYLE_BORDER_CLEAN = 0x02,
    NAV_WINDOW_STYLE_BORDERLESS = 0x03,
};

typedef UInt8 NavWindowStyle;

struct NavWindowType;
typedef struct NavWindowType NavWindow;

NAV_API NavWindow* Nav_Window_Create(char* wndTitle, int width, int height, NavWindowStyle style);

NAV_API void Nav_Window_Destroy(NavWindow* wnd);

NAV_API Bool Nav_Window_UpdateEvents(NavWindow* wnd);

NAV_API void Nav_Window_SetCanClose(NavWindow* wnd, Bool canClose);

NAV_API IntVector2 Nav_Window_GetClientSize(NavWindow* wnd);

NAV_API void Nav_Window_SetClientSize(NavWindow* wnd, IntVector2 newWndSize);

NAV_API IntVector2 Nav_Window_GetPosition(NavWindow* wnd);

#endif