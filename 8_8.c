#include <stdio.h>

int main(void)
{
    int i, j, k;
    int score[5][5] = {0};
    int student[5] = {0}, subject[5] = {0};
    int max[5] = {-1, -1, -1, -1, -1}, min[5] = {-1, -1, -1, -1, -1};
    for (i = 0; i < 5; i++)
    {
        printf("Enter student %d: ", i+1);
        for (j = 0; j < 5; j++)
        {
            scanf("%d", &score[i][j]);
            if (max[j] == -1 || score[i][j] > max[j])
            {
                max[j] = score[i][j];
            }
            if (min[j] == -1 || score[i][j] < min[j])
            {
                min[j] = score[i][j];
            }
            student[i] += score[i][j];
            subject[j] += score[i][j];
        }
    }
    
    for (i = 0; i < 5; i++)
    {
        printf("student %d total score: %d, average score: %.2f\n", i + 1, student[i], (float)student[i] / 5);
    }

    for (i = 0; i < 5; i++)
    {
        printf("subject %d average score %.2f, hightest score: %d, lowest score: %d\n", i + 1, (float)subject[i] / 5, max[i], min[i]);
    }
    return 0;
}