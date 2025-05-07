#include "minishell.h"

void	display_token(t_token *token)
{
	char			token_type[10];
	t_token_type	type_int;

	type_int = token->type;
	if (token->type == TOKEN_CMD)
		strcpy(token_type, "COMMAND");
	else if (type_int == TOKEN_STR)
		strcpy(token_type, "STRING");
	else if (type_int == TOKEN_REDIRECT)
		strcpy(token_type, "REDIRECT");
	else if (type_int == TOKEN_FILE)
		strcpy(token_type, "FILE");
	else
		strcpy(token_type, "UNKNOWN");
	ft_printf("token %p : %s\n^%s$", token, token_type, token->token);
}

void	print_token_list(t_list *tokens)
{
	t_list	*current;

	current = tokens;
	while (current)
	{
		display_token(current->content);
		current = current->next;
	}
}
