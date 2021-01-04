#include "../drivers/screen.h"
#include "../kernel/low_level.h"

void _start() 
{
    clear_screen();
    char* str = "Coolt va? svar: ja, mask mask mask : \n";
    char* str2 = "Coolt va? svar: ja";
    //int row = 5;
    //int col = 6;
    //char attr = 0x0f;
    print(str);
    print(str);
    print(str);
    print(str);
    print(str2);
    print(str);
    print(str);
    print(str2);
    print(str);
    print(str);
    print(str);
}
