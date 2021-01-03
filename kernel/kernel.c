#include "../drivers/screen.h"

void _start() 
{
    clear_screen();
    char* str = "Coolt va? svar: ja";
    int row = 5;
    int col = 6;
    char attr = 0x0f;
    print_string(row, col, str, attr);
}
