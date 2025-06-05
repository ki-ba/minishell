#include "minishell.h"

void	deltoken(void *token)
{
	t_token	*ttoken;

	ttoken = (t_token *)token;
	if (token)
		free(ttoken->token);
	free(token);
}
