#define LEAN_AND_MEAN

#include <nav_debug.h>
#include <windows.h>

int get_console_color_index(int console_color)
{
    switch(console_color)
    {
        case 0:// Black
            return 0;
        break;

        case 1: // Gray
            return 8;
        break;

        case 2: // White
            return 7;
        break;

        case 3: // Yellow
            return 6;
        break;

        case 4: // Red
            return 4;
        break;

        case 5: // Blue
            return 1;
        break;

        case 6: // Green
            return 2;
        break;
    }
}

void set_console_print_color(int new_print_color)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!h_console){return;}

    SetConsoleTextAttribute(h_console, new_print_color);
}