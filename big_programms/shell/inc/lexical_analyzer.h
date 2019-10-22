#ifndef LEXICAL_ANALYZER_SENTRY
#define LEXICAL_ANALYZER_SENTRY

enum lex
{
    lex_none = 0, lex_identifier,
    lex_single_quotes, /* ' ... ' */ lex_double_quotes, /* " ... " */
    lex_less, /* < */ lex_more, /* > */, lex_mooore, /* >> */, lex_vertical_line, /* | */
    lex_slash, /* / */ lex_sharp, /* # */ lex_ampersand, /* & */ lex_semicolon, /* ; */
    lex_env, /* ${VAR} */
    lex_regex /* ?* */
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
    none = 0,
    loop, word, 
    in_single_quotes, in_double_quotes,
    special_symbol
};

typedef enum state_lex state_lex_t;

#endif
