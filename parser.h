#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <stdbool.h>
#include "token.h"

bool isJSON(void);
bool isObject(void);
bool isArray(void);
bool isValue(void);
void ReadWhitespaces(void);
token_t scan_token(void);
char * token_string(token_t t);

FILE *tokens;
long current_position;
int errors;
int line;

#endif // PARSER_H_INCLUDED
