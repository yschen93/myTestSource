#include <stdio.h>
#define NUM 15

int main(int argc, int *argv[])
{
    char phone[NUM] = {0};
    int i;
    printf("Enter phone number: ");
    for (i = 0; i < NUM; i++)
    {
        phone[i] = getchar();
        if (phone[i] >= 'A' && phone[i] <= 'Z')
        switch(phone[i])
        {
            case 'A': case 'B': case 'C': phone[i] = '2'; break;
            case 'D': case 'E': case 'F': phone[i] = '3'; break;
            case 'G': case 'H': case 'I': phone[i] = '4'; break;
            case 'J': case 'K': case 'L': phone[i] = '5'; break;
            case 'M': case 'N': case 'O': phone[i] = '6'; break;
            case 'P': case 'Q': case 'R': case 'S': phone[i] = '7'; break;
            case 'T': case 'U': case 'V': phone[i] = '8'; break;
            case 'W': case 'X': case 'Y': case 'Z': phone[i] = '9'; break;
        }
    }

    printf("In numeric form: ");

    for (i = 0; i < NUM; i++)
    {
        putchar(phone[i]);
    }
    printf("\n");


    return 0;
}