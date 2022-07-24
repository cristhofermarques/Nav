#ifndef NAV_DEBUG_H
#define NAV_DEBUG_H

#include <Nav_Api.h>
#include <Types/Nav_Value_Type.h>

#define BLACK_CONSOLE_COLOR 0
#define GRAY_CONSOLE_COLOR 1
#define WHITE_CONSOLE_COLOR 2
#define YELLOW_CONSOLE_COLOR 3
#define RED_CONSOLE_COLOR 4
#define BLUE_CONSOLE_COLOR 5
#define GREEN_CONSOLE_COLOR 6

#define FLOAT_LOG_FORMAT "%f "
#define DOUBLE_LOG_FORMAT "%lf "
#define STRING_LOG_FORMAT "%s "
#define DECIMAL_LOG_FORMAT "%d "

NAV_API Int32 Nav_Debug_Console_GetColorIndex(Int32 consoleColor);
NAV_API void Nav_Debug_Console_SetPrintColor(Int32 consoleColor);

#ifdef NAV_BUILD_MODE_DEBUG

#include<stdio.h>
#include <stdlib.h>

#define DEBUG_INFO(info_msg) \
    Nav_Debug_Console_SetPrintColor(Nav_Debug_Console_GetColorIndex(YELLOW_CONSOLE_COLOR)); \
    printf("INFO %s %s() %d : %s\n", __FILE__, __FUNCTION__, __LINE__, info_msg); \
    Nav_Debug_Console_SetPrintColor(Nav_Debug_Console_GetColorIndex(WHITE_CONSOLE_COLOR));

#define DEBUG_ERROR(error_msg) \
    Nav_Debug_Console_SetPrintColor(Nav_Debug_Console_GetColorIndex(RED_CONSOLE_COLOR)); \
    printf("ERROR %s %s() %d : %s\n", __FILE__, __FUNCTION__, __LINE__, error_msg); \
    Nav_Debug_Console_SetPrintColor(Nav_Debug_Console_GetColorIndex(WHITE_CONSOLE_COLOR));

#define DEBUG_LOG(log_format, logPrintColor, ...) \
    Nav_Debug_Console_SetPrintColor(Nav_Debug_Console_GetColorIndex(logPrintColor)); \
    printf("LOG %s %s() %d : " log_format "\n", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__); \
    Nav_Debug_Console_SetPrintColor(Nav_Debug_Console_GetColorIndex(WHITE_CONSOLE_COLOR));

#else // NAV_BUILD_RELEASE

#define DEBUG_INFO(info_msg)
#define DEBUG_ERROR(error_msg)
#define DEBUG_LOG(log_format, log_print_color, ...)

#define INIT_DEBUG_HISTORY_SAVE(character_capacity)
#define END_DEBUG_HISTORY_SAVE()

#endif // NAV_BUILD_DEBUG

#endif // NAV_DEBUG_H