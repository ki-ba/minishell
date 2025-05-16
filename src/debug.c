#include "libft.h"
#include "minishell.h"

void	display_token(t_token *token)
{
	char			token_type[10];
	t_token_type	type_int;

	type_int = token->type;
	if (token->type == TOKEN_CMD)
		ft_strlcpy(token_type, "COMMAND", 10);
	else if (token->type == TOKEN_OPT)
		ft_strlcpy(token_type, "OPTION", 10);
	else if (type_int == TOKEN_STR)
		ft_strlcpy(token_type, "STRING", 10);
	else if (type_int == TOKEN_PIPE)
		ft_strlcpy(token_type, "PIPE", 10);
	else if (type_int == TOKEN_REDIRECT)
		ft_strlcpy(token_type, "REDIRECT", 10);
	else if (type_int == TOKEN_FILE)
		ft_strlcpy(token_type, "FILE", 10);
	else
		ft_strlcpy(token_type, "UNKNOWN", 10);
	ft_printf("-----\ntoken %p : %s\n^%s$\n------\n", token, token_type, token->token);
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

char	*summarize_lexing(t_list *tokens)
{
	t_list	*current;
	t_token	*token;
	char	*str;

	str = ft_calloc(1, sizeof(char));
	current = tokens;
	while (current)
	{
		token = (t_token *)current->content;
		str = ft_strjoin(str, ft_itoa(token->type));
		current = current->next;
	}
	str = ft_strjoin(str, ";");
	return (str);
}
