#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define MAX_TAB_STOPS 20
#define TAB_WIDTH 4

int countSpaces(char input[], int pos);
int countSpacesToTabStop(int pos);
int entab(char input[], int len);
int getLength(char input[]);
int getLine(char s[], int lim);

int main() {
    int lineLengthPrior, lineLengthAfter;
    char line[MAX_LINE_LENGTH];
    while ((lineLengthPrior = getLine(line, MAX_LINE_LENGTH)) > 0) {
        printf("(Before) Len: %d, Content: %s", lineLengthPrior, line);
        lineLengthAfter = entab(line, lineLengthPrior);
        printf("(After) Len: %d, Content: %s", lineLengthAfter, line);
    }
    return 0;
}

int entab(char input[], int len) {
    int i = 0;
    while (input[i] != '\0') {
        if (input[i] != ' ') {
            ++i;
            continue;
        }
        int curNumSpaces = countSpaces(input, i);
        int origNumSpaces = curNumSpaces;
        int newNumSpaces = 0;
        int newNumTabs = 0;

        // Find new number of tabs & spaces:
        // Account for initial tab
        int spacesTilTab = countSpacesToTabStop(i);
        if (curNumSpaces < spacesTilTab) {
            // Not enough spaces to make a tab
            i += curNumSpaces;
            continue;
        }
        curNumSpaces -= spacesTilTab;
        ++newNumTabs;

        // Account for intermediate tabs
        while (curNumSpaces >= TAB_WIDTH) {
            ++newNumTabs;
            curNumSpaces -= TAB_WIDTH;
        }

        // Account for leftover spaces
        newNumSpaces = curNumSpaces;

        // At this point, newNumTabs and newNumSpaces have the desired values.
        // We need to shift content of the array and replace with tabs/spaces.
        int trail = i + newNumTabs + newNumSpaces;
        int lead = i + origNumSpaces;

        while (input[lead] != '\0') {
            input[trail] = input[lead];
            ++trail;
            ++lead;
        }
        // copy null character
        input[trail] = input[lead];

        // Fill with tabs and spaces
        while (newNumTabs > 0) {
            input[i] = '\t';
            ++i;
            --newNumTabs;
        }
        while (newNumSpaces > 0) {
            input[i] = ' ';
            ++i;
            --newNumSpaces;
        }
    }

    return getLength(input);
}

int getLength(char input[]) {
    int newLen = 0;
    while (input[newLen] != '\0') {
        ++newLen;
    }
    return newLen;
}

int countSpacesToTabStop(int pos) {
    if (pos % TAB_WIDTH == 0) {
        return TAB_WIDTH;
    }
    int spaces = 0;
    while (pos % TAB_WIDTH != 0) {
        ++spaces;
        ++pos;
    }
    return spaces;
}

int countSpaces(char input[], int pos) {
    int spaces = 0;
    while (input[pos] == ' ' && pos <= MAX_LINE_LENGTH) {
        ++spaces;
        ++pos;
    }
    return spaces;
}

int getLine(char s[], int lim)
{
    int c, i;

    for (i = 0; i < lim-1 && (c = getchar()) != EOF && c!='\n'; ++i) {
        s[i] = c;
    }

    if (c == '\n') {
        s[i] = c;
        ++i;
    }
    s[i] = '\0';

    return i;
}

