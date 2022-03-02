#include "mylib.h"

int LEtoInt(unsigned char* arr, int byte_size = 4)    //little endian to integer
{
    unsigned int integer = 0;
    for (int i = 0, j = 1; i < byte_size; i++, j *= 256)
    {
        integer += arr[i] * j;
    }
    return integer;
}
