#include "../kernel/utils.h"

void mem_copy(char* copy_to, char* copy_from, int size)
{
    for (; size > 0; size--)
    {
        *copy_to++ = *copy_from++; 
    }
}
