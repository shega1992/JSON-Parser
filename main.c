#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "parser.h"

 //int line = 1;

int main(int argc, char * argv[])
{
    FILE *source;
    //extern FILE *tokens;
    //extern int errors;

    if(argc != 3)
    {
        printf("Usage: %s -key filename\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    if((source = fopen(argv[2], "r")) == NULL)
    {
        printf("Can't open %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    if(!strcmp(argv[1],"-scan"))
    {
        int counter = 0;
        printf("Sequence of tokens in %s(format: <token, token's line>):\n", argv[2]);
        while((t = yylex(source)))
        {
            switch(t)
            {
            case TOKEN_SPACE:
                printf("%d.<SPACE,%d>\n", ++counter, line);
                break;
            case TOKEN_LINEFEED:
                printf("%d.<LINEFEED,%d>\n", ++counter, line++);
                break;
            case TOKEN_CARRIAGE_RETURN:
                printf("%d.<CARRIAGE RETURN,%d>\n", ++counter, line);
                break;
            case TOKEN_HORIZONTAL_TAB:
                printf("%d.<HORIZONTAL TAB,%d>\n", ++counter, line);
                break;
            case TOKEN_NUMBER:
                printf("%d.<NUMBER,%d>\n", ++counter, line);
                break;
            case TOKEN_STRING:
                printf("%d.<STRING,%d>\n", ++counter, line);
                break;
            case TOKEN_LBRACKET:
                printf("%d.<LBRACKET,%d>\n", ++counter, line);
                break;
            case TOKEN_RBRACKET:
                printf("%d.<RBRACKET,%d>\n", ++counter,line);
                break;
            case TOKEN_LBRACE:
                printf("%d.<LBRACE,%d>\n", ++counter,line);
                break;
            case TOKEN_RBRACE:
                printf("%d.<RBRACE,%d>\n", ++counter,line);
                break;
            case TOKEN_COLON:
                printf("%d.<COLON,%d>\n", ++counter,line);
                break;
            case TOKEN_COMMA:
                printf("%d.<COMMA,%d>\n", ++counter,line);
                break;
            case TOKEN_TRUE:
                printf("%d.<TRUE,%d>\n", ++counter,line);
                break;
            case TOKEN_FALSE:
                printf("%d.<FALSE,%d>\n", ++counter,line);
                break;
            case TOKEN_NULL:
                printf("%d.<NULL,%d>\n", ++counter,line);
                break;
            case TOKEN_ERROR:
                printf("%d.<ERROR,%d>\n", ++counter,line);
                printf("Scan error in line %d\a\n", line);
                printf("Total: %d tokens\n", counter);
                fclose(source);
                exit(EXIT_FAILURE);
            }
        }
        printf("%d.<EOF,%d>\n", ++counter, line);
        printf("Total: %d tokens\n", counter);
        fclose(source);
    }
    else if(!strcmp(argv[1],"-parse"))
    {
         if((tokens = fopen("tokens.txt", "w+"))== NULL)
         {
            printf("Can't create output file\n");
            exit(EXIT_FAILURE);
         }

        while((t = yylex(source)))
        {
            switch(t)
            {
            case TOKEN_SPACE:
                fprintf(tokens,"%d ", TOKEN_SPACE);
                break;
            case TOKEN_LINEFEED:
                fprintf(tokens,"%d\n", TOKEN_LINEFEED);
                line++;
                break;
            case TOKEN_CARRIAGE_RETURN:
                fprintf(tokens,"%d ", TOKEN_CARRIAGE_RETURN);
                break;
            case TOKEN_HORIZONTAL_TAB:
                fprintf(tokens,"%d ", TOKEN_HORIZONTAL_TAB);
                break;
            case TOKEN_NUMBER:
                fprintf(tokens,"%d ", TOKEN_NUMBER);
                break;
            case TOKEN_STRING:
                fprintf(tokens,"%d ", TOKEN_STRING);
                break;
            case TOKEN_LBRACKET:
                fprintf(tokens,"%d ", TOKEN_LBRACKET);
                break;
            case TOKEN_RBRACKET:
                fprintf(tokens,"%d ", TOKEN_RBRACKET);
                break;
            case TOKEN_LBRACE:
                fprintf(tokens,"%d ", TOKEN_LBRACE);
                break;
            case TOKEN_RBRACE:
                fprintf(tokens,"%d ", TOKEN_RBRACE);
                break;
            case TOKEN_COLON:
                fprintf(tokens,"%d ", TOKEN_COLON);
                break;
            case TOKEN_COMMA:
                fprintf(tokens,"%d ", TOKEN_COMMA);
                break;
            case TOKEN_TRUE:
                fprintf(tokens,"%d ", TOKEN_TRUE);
                break;
            case TOKEN_FALSE:
                fprintf(tokens,"%d ", TOKEN_FALSE);
                break;
            case TOKEN_NULL:
                fprintf(tokens,"%d ", TOKEN_NULL);
                break;
            case TOKEN_ERROR:
                fprintf(stderr,"Scan error in line %d\a\n", line);
                fclose(source);
                fclose(tokens);
                if(remove("tokens.txt") != 0)
                    printf("Can't delete tokens.txt\n");
                exit(EXIT_FAILURE);
            }
        }
        fprintf(tokens,"%d ", TOKEN_EOF);

        rewind(tokens);
        line = 1;

        isJSON()? printf("Success\n") : printf("Failure. Number of errors:%d\n", errors);

        fclose(source);
        fclose(tokens);
        if(remove("tokens.txt") != 0)
            printf("Can't delete tokens.txt\n");
    }
    else
        fprintf(stderr,"Error. Unknown key\a\n");

    return 0;
}
