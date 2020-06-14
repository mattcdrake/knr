#include <stdio.h>
#define MAXLINE 1000

int getLine(char line[], int maxline);
int trimLine(char line[], int length);
void copy(char to[], char from[]);
void reverse(char line[], int len);

int old_main()
{
    int len;
    int max;
    char line[MAXLINE];
    char longest[MAXLINE];

    max = 0;
    while ((len = trimLine(line, getLine(line, MAXLINE))) > 0)
    {
        printf("len: %d, content: %s", len, line);
        if (len > 80)
        {
            printf("more than 80! len: %d, content: %s", len, line);
        }
        if (len > max)
        {
            max = len;
            copy(longest, line);
        }
        reverse(line, len);
        printf("reversed: %s", line);
    }
    if (max > 0)
    {
        printf("%s", longest);
    }
    return 0;
}

int getLine(char s[], int lim) 
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c!='\n'; ++i)
    {
        s[i] = c;
    }

    if (c == '\n') 
    {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

// Not checking for newlines
int trimLine(char s[], int len)
{
    int lead = len - 2;
    while (lead > 0 && (s[lead] == ' ' || s[lead] == '\t'))
    {
        s[lead] = '\n';
        s[len] = '\0';
        --lead;
        --len;
    }
    // If the only thing left is a newline, return len 0
    if (len == 1)
    {
        --len;
    }
    return len;
}

void copy(char to[], char from[])
{
    int i = 0;
    while ((to[i] = from[i]) != '\0')
    {
        ++i;
    }
}

void reverse(char line[], int len)
{
    int front = 0;
    int back = len - 2;
    char temp;
    while (front < back)
    {
        temp = line[front];
        line[front] = line[back];
        line[back] = temp;
        ++front;
        --back;
    }
}

