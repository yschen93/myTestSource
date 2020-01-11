#include <stdio.h>
#include <ctype.h>

int main(int argc, char *argv[])
{
    int sum = 0;
    printf("Enter a word: ");
    char ch;
    int array[26] = {1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    while((ch = getchar()) != '\n')
    {
        sum += array[toupper(ch) - 'A'];
    }

    printf("Scrabble vavle: %d\n", sum);

    return 0;
}
