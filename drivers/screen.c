#include "../drivers/screen.h"
#include "../kernel/low_level.h"

#define VIDEO_MEM_ADDR 0xb7fff
#define MAX_ROWS 25
#define MAX_COLS 80

#define DEFAULT_ATTR 0x0f

#define REG_SCREEN_CTRL 0x3d4
#define REG_SCREEN_DATA 0x3d5

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
    set_cursor(0);
    return;
}

int get_screen_offset(int row, int col)
{
    return (row*MAX_COLS+col)*2;
}

void print_char(int row, int col, char c, char attribute)
{
    int offset = get_screen_offset(row, col);
    if (row > MAX_ROWS || col > MAX_COLS)   // row/col too big
    {
        return;
    }
    else if (row < 0 || col < 0)
    {
        offset = get_cursor();
    }
    if (c == '\n')
    {
        int rows = offset / (MAX_COLS*2);
        offset = get_screen_offset(rows, MAX_COLS-1);
    }
    else {
        char* vidmem = (char*) VIDEO_MEM_ADDR;
        vidmem[offset] = attribute;
        vidmem[offset + 1] = c;
    }
    set_cursor(offset + 2);
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

unsigned int get_cursor()
{
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8;
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset |= port_byte_in(REG_SCREEN_DATA);
    return offset*2;
}

void set_cursor(int offset)
{
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) (offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char) offset);
}

void print(char* string)
{
    print_string(-1, -1, string, 0);
}
