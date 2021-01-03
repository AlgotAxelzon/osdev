#define VIDEO_MEM_ADDR 0xb8000;

void fill_screen(short cell_attribute)
{
    short* video_memory = (short*) VIDEO_MEM_ADDR;
    for (int i=0; i<80*25; i++)
    {
        *video_memory = cell_attribute;
        video_memory++;
    }
    
}

void _start() 
{
    fill_screen(0b1101011000000000);
}
