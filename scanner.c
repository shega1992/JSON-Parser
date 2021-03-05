#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "token.h"

token_t yylex(FILE *fp)
{
    int ch = fgetc(fp);
    if(ch == EOF)
        return TOKEN_EOF;
    else if(ch == '-' || isdigit(ch))
    {
        while(isdigit(ch = fgetc(fp)))
            ;
        if(ch == '.')
           while(isdigit(ch = fgetc(fp)))
                ;
        if(ch == 'E' || ch == 'e')
        {
            ch = fgetc(fp);
            if(ch == '+' || ch == '-' || isdigit(ch))
                while(isdigit(ch = fgetc(fp)))
                    ;
        }
        ungetc(ch, fp);
        return TOKEN_NUMBER;
    }
    else if(isalpha(ch))
    {
        char str[6];
        int i;
        str[0] = ch;
        for(i = 1; isalpha(ch = fgetc(fp)); i++)
            str[i] = ch;
        str[i] = '\0';
        ungetc(ch, fp);
        if(!strcmp(str, "true")) return TOKEN_TRUE;
        if(!strcmp(str, "false")) return TOKEN_FALSE;
        if(!strcmp(str, "null")) return TOKEN_NULL;
    }
    else if(ch == '"')
    {
        while((ch = fgetc(fp)) != '"')
            if(ch == '\\') fgetc(fp); // if \ then discard next character
        return TOKEN_STRING;
    }
    else if(isspace(ch))
    {
        switch(ch)
        {
            case ' ': return TOKEN_SPACE;
            case '\n': return TOKEN_LINEFEED;
            case '\r': return TOKEN_CARRIAGE_RETURN;
            case '\t': return TOKEN_HORIZONTAL_TAB;
        }
    }
    else if(ispunct(ch))
    {
        switch(ch)
        {
            case '[': return TOKEN_LBRACKET;
            case ']': return TOKEN_RBRACKET;
            case '{': return TOKEN_LBRACE;
            case '}': return TOKEN_RBRACE;
            case ':': return TOKEN_COLON;
            case ',': return TOKEN_COMMA;
        }
    }
    return TOKEN_ERROR;
}
