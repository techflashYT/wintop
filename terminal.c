#include <Windows.h>
#include <systemInfo.h>
void getTerminalWidthAndHeight() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    systemInfo.terminal.width = csbi.srWindow.Right - csbi.srWindow.Left + 1;
    systemInfo.terminal.height = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;

}
