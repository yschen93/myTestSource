#include<stdio.h>

#define STACK_SIZE 5


int contents[STACK_SIZE];
int top;
int isOver = 0;
int isLower = 0;

void make_empty(void);
int is_empty(void);
int is_full(void);
void push(char ch);
char pop(void);

int main(int argc, char *argv[])
{
    char ch;
    printf("Enter parenteses and/or braces: ");
    while((ch = getchar()) != '\n')
    {
        while(ch == ' ');
        if ((ch == '(' || ch == '{'))
        {
            if (top == STACK_SIZE)
            {
                printf("up to stack top.\n");
                return 0;
            }
            else
            {
                push(ch);
            } 
        }
        else if ((ch == ')' || ch == '}'))
        {
            if (top == 0)
            {
                printf("down to stack bottom.\n");
                return 0;
            }
            else
            {
                char temp = pop();
                if ((temp == '(' && ch == ')') || (temp == '{' && ch == '}'))
                {
                    continue;
                }
                else
                {
                   printf("mismatching.\n");
                }
            }
        }
        
    }
    if (top == 0)
    {
        printf("matching.\n");
    }
    else
    {
        printf("mismatching.\n");
    }

    return 0;
}

void make_empty(void)
{
    top = 0;
}

int is_empty(void)
{
    return top == 0;
}

int is_full(void)
{
    return top == STACK_SIZE;
}

void push(char ch)
{
    if (is_full())
    {
        return;
    }
    contents[top++] = ch;
}

char pop(void)
{
    if (is_empty())
    {
        return ' ';
    }
    return contents[--top];
}