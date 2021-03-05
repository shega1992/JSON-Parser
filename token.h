#ifndef TOKEN_H_INCLUDED
#define TOKEN_H_INCLUDED

typedef enum{
    TOKEN_EOF,
    TOKEN_SPACE,
    TOKEN_LINEFEED,
    TOKEN_CARRIAGE_RETURN,
    TOKEN_HORIZONTAL_TAB,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_LBRACKET,
    TOKEN_RBRACKET,
    TOKEN_LBRACE,
    TOKEN_RBRACE,
    TOKEN_COLON,
    TOKEN_COMMA,
    TOKEN_TRUE,
    TOKEN_FALSE,
    TOKEN_NULL,
    TOKEN_ERROR
}token_t;

token_t yylex(FILE *);
token_t t;

#endif // TOKEN_H_INCLUDED
