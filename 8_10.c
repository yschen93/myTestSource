#include <stdio.h>

int abs(int num);

int main(int argc, char *argv[])
{
    int i;
    int hour, mins, total;
    int min = -1, minValue;
    int hour1, min1, hour2, min2;
    int isOut1 = -1, isOut2 = -1;
    int start[8] = {480, 583, 679, 767, 840, 945, 1140, 1305};
    int end[8] = {616, 712, 811, 900, 968, 1075, 1280, 1438};
    printf("Enter a 24-hour time: ");
    scanf("%d:%d", &hour, &mins);
    total = hour * 60 + mins;
    for (i = 0; i < 8; i++)
    {
        if (min == -1 || abs(total - start[i]) < minValue)
        {
            min = i;
            minValue = abs(total - start[i]);
        }
    }

    if (start[min] / 60 > 12)
    {
        hour1 = start[min] / 60  - 12;
        isOut1 = 1;
    }
    else
    {
        hour1 = start[min] / 60;
    }
    
    min1 = start[min] - start[min] / 60 * 60;
    printf("Closest departure time is %d:%.2d %s, ", hour1, min1, (start[min] / 60 >= 12) ? "p.m." : "a.m.");


    if (end[min] / 60 >= 12)
    {
        hour2 = end[min] / 60  - 12;
    }
    else
    {
        hour2 = end[min] / 60;
    }

    min2 = end[min] - end[min] / 60 * 60;
    printf("arriving at %d:%.2d %s\n", hour2, min2, (end[min] / 60 >= 12) ? "p.m." : "a.m.");

    return 0;
}

int abs(int num)
{
    return num >= 0 ? num : -num;
}

