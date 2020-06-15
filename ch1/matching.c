#include <stdio.h>

#define MAX_LINE_LENGTH 1000
#define CHAR_STACK_SIZE 1000

int getLine(char s[], int lim);
int isBalanced(char line[]);
int isClosePair(char leftCandidate, char rightCandidate);
int isOpenPair(char c);
int isPair(char c);

int main() {
    int lineLength;
    char c;
    char line[MAX_LINE_LENGTH];
    while ((c = getLine(line, MAX_LINE_LENGTH)) > 0) {
        if (isBalanced(line)) {
            printf("input has balanced syntax\n");
        } else {
            printf("input does not have balanced syntax\n");
        }
    }
}

int getLine(char s[], int lim) {
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

int isBalanced(char line[]) {
    char charStack[CHAR_STACK_SIZE];
    int head = 0;
    int pos = 0;
    while (line[pos] != '\0') {
        if (!isPair(line[pos])) {
            ++pos;
            continue;
        }

        if (isOpenPair(line[pos])) {
            charStack[head] = line[pos];
            ++head;
        } else if (--head < 0 || !isClosePair(charStack[head], line[pos])) {
            return 0;
        }
        ++pos;
    }
    return head == 0;
}

int isPair(char c) {
    if (    c == '{'  ||
            c == '('  ||
            c == '['  ||
            c == '}'  ||
            c == ')'  ||
            c == ']'  ||
            c == '"'  ||
            c == '\'') {
        return 1;
    }
    return 0;
}

int isOpenPair(char c) {
    if (    c == '{' ||
            c == '(' ||
            c == '[' ||
            c == '"' ||
            c == '\''     ) {
        return 1;
    }
    return 0;
}

int isClosePair(char leftCandidate, char rightCandidate) {
    switch (leftCandidate) {
        case '{':
            return rightCandidate == '}';
        case '(':
            return rightCandidate == ')';
        case '[':
            return rightCandidate == ']';
        case '"':
            return rightCandidate == '"';
        case '\'':
            return rightCandidate == '\'';
        default:
            return 0;
    }
}


