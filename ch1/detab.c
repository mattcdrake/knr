#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define MAX_TAB_STOPS 20

int detab(char input[], int len);
int getLine(char s[], int lim);

int main()
{
    int lineLengthPrior, lineLengthAfter;
    char line[MAX_LINE_LENGTH];
    while ((lineLengthPrior = getLine(line, MAX_LINE_LENGTH)) > 0)
    {
        printf("(Before) Len: %d, Content: %s", lineLengthPrior, line);
        lineLengthAfter = detab(line, lineLengthPrior);
        printf("(After) Len: %d, Content: %s", lineLengthAfter, line);
    }
    return 0;
}

int detab(char input[], int len)
{
    int pos = 0;
    int newLen = len;
    while (pos < newLen && pos < MAX_TAB_STOPS * 4)
    {
        if (input[pos] != '\t')
        {
            ++pos;
            continue;
        }

        // Calculate number of spaces
        int numSpaces = pos;
        if (numSpaces % 4 == 0)
        {
            numSpaces = 4;
        }
        else
        {
            while (numSpaces % 4 != 0)
            {
                ++numSpaces;
            }
            numSpaces -= pos;
        }

        // Shift everything between tab+1 and '\0' to make room for spaces.
        int lead = newLen + numSpaces - 1;
        int cur = newLen;
        newLen = lead;

        while (cur > pos) 
        {
            input[lead] = input[cur];
            --cur;
            --lead;
        }

        // Add spaces
        int spacePos = pos;
        while (numSpaces > 0)
        {
            input[spacePos] = ' ';
            ++spacePos;
            --numSpaces;
        }
        ++pos;
    }
    return newLen;
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
