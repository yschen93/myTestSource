#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int func(int *i, int *j, int num, char array[][10]);

int main(int argc, char *argv[])
{

	printf("nihao");
	printf("hello");

    char array[10][10];
    int i, j;
    int isGo = 1;
    int randNum;

    srand((unsigned) time(NULL));
    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            array[i][j] = '.';
        }
    }
    i = 0, j = 0;
    array[i][j] = 'A';
    while (1)
    {
        isGo = 1;
        randNum = rand() % 4;
        if (randNum == 0)
        {
            if (i - 1 >= 0 && array[i-1][j] == '.')
            {
                array[i-1][j] = array[i][j] + 1;
                i = i - 1;
            }
            else if (func(&i, &j, randNum, array) == -1)
            {
                isGo = 0;
            }
        }
        else if (randNum == 1)
        {
            if (i + 1 <= 9 && array[i+1][j] == '.')
            {
                array[i+1][j] = array[i][j] + 1;
                i = i + 1;
            }
            else if (func(&i, &j, randNum, array) == -1)
            {
                isGo = 0;
            }
        }
        else if (randNum == 2)
        {
            if (j - 1 >= 0 && array[i][j-1] == '.')
            {
                array[i][j-1] = array[i][j] + 1;
                j = j - 1;
            }
            else if (func(&i, &j, randNum, array) == -1)
            {
                isGo = 0;
            }
        }
        else if (randNum == 3)
        {
            if (j + 1 <= 9 && array[i][j+1] == '.')
            {
                array[i][j+1] = array[i][j] + 1;
                j = j + 1;
            }
            else if (func(&i, &j, randNum, array) == -1)
            {
                isGo = 0;
            }
        }

        if (isGo == 0 || array[i][j] == 'Z')
        {
            break;
        }
    }

    for (i = 0; i < 10; i++)
    {
        for (j = 0; j < 10; j++)
        {
            printf("%c", array[i][j]);
            if (j == 9)
            {
                printf("\n");
            }
            else
            {
                printf(" ");
            }
        }
    }
    printf("\n");
    
    return 0;
}

int func(int *pi, int *pj, int num, char array[][10])
{
    int i, j;
    i = *pi;
    j = *pj;
    if (num != 0 && i - 1 >= 0 && array[i-1][j] == '.')
    {
        array[i-1][j] = array[i][j] + 1;
        *pi = *pi - 1;
        return 0;
    }

    if (num != 1 && i + 1 <= 9 && array[i+1][j] == '.')
    {
        array[i+1][j] = array[i][j] + 1;
        *pi = *pi + 1;
        return 0;
    }

    if (num != 2 && j - 1 >= 0 && array[i][j-1] == '.')
    {
        array[i][j-1] = array[i][j] + 1;
        *pj = *pj- 1;
        return 0;
    }

    if (num != 3 && j + 1 <= 9 && array[i][j+1] == '.')
    {
        array[i][j+1] = array[i][j] + 1;
        *pj = *pj + 1;
        return 0;
    }

    return -1;
}