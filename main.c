#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXINPUTSIZE 128
#define TOKEN_FALSE 0
#define TOKEN_TRUE 1
#define TOKEN_OR 2
#define TOKEN_AND 3
#define TOKEN_NOT 4
#define TOKEN_LPAREN 5
#define TOKEN_RPAREN 6
#define TOKEN_EOL 7
#define TOKEN_INVALID 8

int expression[MAXINPUTSIZE];

int parseExpression(int** expr);
int parseFactor(int** expr);
int parseTerm(int** expr);

void lexer(char input[], int expression[]) {
    char *ptr = input;
    int counter_to_expression = 0;
    
    while (*ptr != '\0') {
        switch (*ptr) {
            case ' ':
                ptr++;
                break;
            case '|':
                expression[counter_to_expression] = TOKEN_OR;
                counter_to_expression++;
                ptr += 2;
                break;
            case '&':
                expression[counter_to_expression] = TOKEN_AND;
                counter_to_expression++;
                ptr += 2;
                break;
            case '!':
                expression[counter_to_expression] = TOKEN_NOT;
                counter_to_expression++;
                ptr++;
                break;
            case '(':
                expression[counter_to_expression] = TOKEN_LPAREN;
                counter_to_expression++;
                ptr++;
                break;
            case ')':
                expression[counter_to_expression] = TOKEN_RPAREN;
                counter_to_expression++;
                ptr++;
                break;
            case 'T':
                expression[counter_to_expression] = TOKEN_TRUE;
                counter_to_expression++;
                ptr += 4;
                break;
            case 'F':
                expression[counter_to_expression] = TOKEN_FALSE;
                counter_to_expression++;
                ptr += 5;
                break;
            default:
                printf("Invalid token at %s\n", ptr);
                exit(EXIT_FAILURE);
        }
    }
    expression[counter_to_expression] = TOKEN_EOL;
    return;
}

int parseFactor(int** expr) {
    if (**expr == TOKEN_NOT) {
        (*expr)++;
        return !parseFactor(expr);
    }

    else if (**expr == TOKEN_LPAREN) {
        (*expr)++;
        int result = parseExpression(expr);
        
        if (**expr == TOKEN_RPAREN)
            (*expr)++;
        else 
            printf("mismatching parenthesis\n");
        return result;
    }

    else if (**expr == TOKEN_TRUE) {
        (*expr)++;
        return 1;
    }

    else if (**expr == TOKEN_FALSE) {
        (*expr)++;
        return 0;
    }

    else {
        printf("Unexpected token at: %s\n", **expr);
        exit(1);
    }
}

int parseTerm(int** expr) {
    int result = parseFactor(expr);

    while (**expr != TOKEN_EOL) {
        if (**expr == TOKEN_AND) {
            (*expr)++;
            result = result && parseFactor(expr);
        }
        else break;
    }
    return result;
}

int parseExpression(int** expr) {
    int result = parseTerm(expr);

    while (**expr != TOKEN_EOL) {
        if (**expr == TOKEN_OR) {
            (*expr)++;
            result = result || parseTerm(expr);
        }
        else break;
    }
    return result; 
}

int main(void) {

    while (1) {
        int result;
        char input[MAXINPUTSIZE];

        printf(">>> ");
        if (fgets(input, MAXINPUTSIZE, stdin) == NULL) {
            fprintf(stderr, "Couldn't get your input");
            return 1;
        }

        size_t position_to_newline = strcspn(input, "\n");
        input[position_to_newline] = '\0';

        lexer(input, expression);

        int* expr = expression;
        result = parseExpression(&expr);

        if (result) printf("True\n");
        else printf("False\n");
    }
}
