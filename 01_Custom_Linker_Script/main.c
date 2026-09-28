#include <stdint.h>

/* Simple main function to test startup code and linker script */
int main(void)
{
    /* Volatile loop counter to prevent compiler optimization */
    volatile uint32_t counter = 0;

    while (1)
    {
        counter++;
    }

    return 0;
}