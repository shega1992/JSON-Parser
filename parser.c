#include <stdio.h>
#include "parser.h"

bool isJSON(void)
{
    if((t = scan_token()) & (isObject() || isArray()))
    {
        ReadWhitespaces();
        if(t == TOKEN_EOF && errors == 0)
            return true;
        else
            return false;
    }
    else
    {
       printf("parse error in isJSON: unexpected token %s in %d line\n", token_string(t), line);
       errors++;
       return false;
    }
}

bool isObject(void)
{
    if(t == TOKEN_LBRACE)
    {
        ReadWhitespaces();
        if(t == TOKEN_RBRACE)
            return true;
        while(t == TOKEN_STRING)
        {
            ReadWhitespaces();
            if(t == TOKEN_COLON)
            {
                if(isValue() && t == TOKEN_COMMA)
                    ;
                else if(t == TOKEN_RBRACE)
                    return true;
                else
                {
                    printf("parse error in isObject: unexpected token %s in %d line\n", token_string(t), line);
                    errors++;
                    return false;
                }
            }
            else
            {
                printf("parse error in isObject: unexpected token %s in %d line\n", token_string(t), line);
                errors++;
                return false;
            }
            ReadWhitespaces();
        }
        printf("parse error in isObject: unexpected token %s in %d line\n", token_string(t), line);
        errors++;
        return false;
    }
    else
        return false;
}

bool isArray(void)
{
    if(t == TOKEN_LBRACKET)
    {
        current_position = ftell(tokens);
        int temp = line;
        ReadWhitespaces();
        if(t == TOKEN_RBRACKET)
            return true;
        fseek(tokens, current_position, SEEK_SET);
        line = temp;
        while(isValue() && t == TOKEN_COMMA)
            ;
        if(t == TOKEN_RBRACKET)
                return true;
        else
        {
            printf("parse error in isArray: unexpected token %s in %d line\n", token_string(t), line);
            errors++;
            return false;
        }
    }
    else
        return false;
}

bool isValue(void)
{
    ReadWhitespaces();
    switch(t)
    {
        case TOKEN_STRING: case TOKEN_NUMBER:
        case TOKEN_TRUE: case TOKEN_FALSE:
        case TOKEN_NULL:
            ReadWhitespaces();
            return true;
        case TOKEN_LBRACKET:
            if(isArray())
            {
               ReadWhitespaces();
               return true;
            }
            else
                return false;
        case TOKEN_LBRACE:
            if(isObject())
            {
                ReadWhitespaces();
                return true;
            }
            else
                return false;
        default:
            printf("parse error in isValue: unexpected token %s in %d line\n", token_string(t), line);
            errors++;
            return false;

    }
}

void ReadWhitespaces(void)
{
    while((t = scan_token()) && (t == TOKEN_SPACE || t == TOKEN_LINEFEED || t == TOKEN_CARRIAGE_RETURN || t == TOKEN_HORIZONTAL_TAB))
        if(t == TOKEN_LINEFEED) line++;
}

token_t scan_token(void)
{
    int temp;
    fscanf(tokens,"%d", &temp);
    return temp;
}

char * token_string(token_t t)
{
    switch(t)
    {
        case TOKEN_EOF: return "EOF";
        case TOKEN_SPACE: return "SPACE";
        case TOKEN_LINEFEED: return "LINEFEED";
        case TOKEN_CARRIAGE_RETURN: return "CARRIAGE_RETURN";
        case TOKEN_HORIZONTAL_TAB: return "HORIZONTAL_TAB";
        case TOKEN_NUMBER: return "NUMBER";
        case TOKEN_STRING: return "STRING";
        case TOKEN_LBRACKET: return "LBRACKET";
        case TOKEN_RBRACKET: return "RBRACKET";
        case TOKEN_LBRACE: return "LBRACE";
        case TOKEN_RBRACE: return "RBRACE";
        case TOKEN_COLON: return "COLON";
        case TOKEN_COMMA: return "COMMA";
        case TOKEN_TRUE: return "TRUE";
        case TOKEN_FALSE: return "FALSE";
        case TOKEN_NULL: return "NULL";
        case TOKEN_ERROR: return "ERROR";
    }
}
