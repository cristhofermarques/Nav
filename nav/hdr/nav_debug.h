#ifndef NAV_DEBUG_H
#define NAV_DEBUG_H

#include <nav_api.h>

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

NAV_API int get_console_color_index(int console_color);
NAV_API void set_console_print_color(int new_print_color);

#ifdef DEBUG

#include<stdio.h>
#include <stdlib.h>

#define DEBUG_INFO(info_msg) \
set_console_print_color(get_console_color_index(YELLOW_CONSOLE_COLOR)); \
printf("INFO %s %s() %d : %s\n", __FILE__, __FUNCTION__, __LINE__, info_msg); \
set_console_print_color(get_console_color_index(WHITE_CONSOLE_COLOR));

#define DEBUG_ERROR(error_msg) \
set_console_print_color(get_console_color_index(RED_CONSOLE_COLOR)); \
printf("ERROR %s %s() %d : %s\n", __FILE__, __FUNCTION__, __LINE__, error_msg); \
set_console_print_color(get_console_color_index(WHITE_CONSOLE_COLOR));

#define DEBUG_LOG(log_format, log_print_color, ...) \
set_console_print_color(get_console_color_index(log_print_color)); \
printf("LOG %s %s() %d : " log_format "\n", __FILE__, __FUNCTION__, __LINE__, __VA_ARGS__); \
set_console_print_color(get_console_color_index(WHITE_CONSOLE_COLOR));

#define INIT_DEBUG_HISTORY_SAVE(character_capacity) \
unsigned int debug_history_buffer_peek = 0; \
char* debug_history_buffer_ptr = (char*)malloc(sizeof(char) * character_capacity); \
char debug_history_save_initialized = debug_history_buffer_ptr != NULL; \

#define END_DEBUG_HISTORY_SAVE() \
if(debug_history_save_initialized) \
{ \
    free(debug_history_buffer_ptr); \
} \

#else

#define DEBUG_INFO(info_msg)
#define DEBUG_ERROR(error_msg)
#define DEBUG_LOG(log_format, log_print_color, ...)

#define INIT_DEBUG_HISTORY_SAVE(character_capacity)
#define END_DEBUG_HISTORY_SAVE()

#endif

#endif