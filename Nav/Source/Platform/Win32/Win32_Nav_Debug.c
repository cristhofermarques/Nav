#define LEAN_AND_MEAN

#include <Nav_Debug.h>
#include <windows.h>


Int32 Nav_Debug_Console_GetColorIndex(Int32 consoleColor)
{
    switch(consoleColor)
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

void Nav_Debug_Console_SetPrintColor(Int32 consoleColor)
{
    HANDLE h_console = GetStdHandle(STD_OUTPUT_HANDLE);
    if(!h_console){return;}

    SetConsoleTextAttribute(h_console, consoleColor);
}