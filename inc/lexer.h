#ifndef LEXER_H
# define LEXER_H

enum e_token_type
{
	TOKEN_CMD,
	TOKEN_STR,
	TOKEN_REDIRECT,
	TOKEN_FILE
}

typedef	struct s_token
{
	int		type;
	char	*value;
}	t_token;

char	*get_variable(char *var);


#endif
