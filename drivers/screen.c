#include "screen.h"

#define VIDEO_MEM_ADDR 0xb7fff
#define MAX_ROWS 25
#define MAX_COLS 80

#define DEFAULT_ATTR 0x0f

void fill_screen(char c, char attr)
{
    short* video_memory = (short*) VIDEO_MEM_ADDR;
    for (int i=0; i<MAX_COLS*MAX_ROWS; i++)
    {
        *video_memory = (c << 8 | attr);
        video_memory++;
    }
}

void clear_screen()
{
    fill_screen(' ', DEFAULT_ATTR);
    return;
}

void print_char(int row, int col, char c, char attribute)
{
    if (row > MAX_ROWS || col > MAX_COLS)   // row/col too big
    {
        return;
    }
    else if (row < -1 || col < 0)    // row/col too small -> TODO: use cursor pos?
    {
        // TODO: Use cursor pos
        return;
    }
    char* vidmem = (char*) VIDEO_MEM_ADDR;
    int offset = (row*MAX_COLS+col)*2;
    vidmem[offset] = attribute;
    vidmem[offset + 1] = c;
    return;
}

void print_string(int row, int col, char* string_ptr, char attribute)
{
    if (attribute == 0x00)
    {
        attribute = DEFAULT_ATTR;
    }
    while (*string_ptr != 0x00)
    {
        print_char(row, col++, *string_ptr++, attribute);
    }
    return;
}
