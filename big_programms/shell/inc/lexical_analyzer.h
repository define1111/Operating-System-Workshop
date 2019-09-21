#ifndef LEXICAL_ANALYZER_SENTRY
#define LEXICAL_ANALYZER_SENTRY

enum lex
{
    lex_none = 0, lex_identifier,
    lex_single_quotes, /* ' ... ' */ lex_double_quotes, /* " ... " */
    lex_less, /* < */ lex_more, /* > */, lex_mooore, /* >> */, lex_vertical_line, /* | */
    lex_slash, /* / */ lex_sharp, /* # */ lex_ampersand, /* & */ lex_semicolon, /* ; */
    lex_env, /* ${VAR} */
};

typedef enum lex lex_t;

struct token
{
    lex_t lex;
    char *value;
}

typedef struct token token_t;

enum state_lex
{
    
}

#endif
