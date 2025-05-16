#include "libft.h"
#include "minishell.h"

t_token_type	determine_token_type(char token_str[], t_token_type last_type, t_bool *cmd_bool)
{
	if (determine_redirect(token_str))
		return (TOKEN_REDIRECT);
	else if (last_type == TOKEN_REDIRECT)
		return (TOKEN_FILE);
	else if (determine_option(token_str))
		return (TOKEN_OPT);
	else if (determine_pipe(token_str))
	{
		*cmd_bool = FALSE;
		return (TOKEN_PIPE);
	}
	else if (!(*cmd_bool) && ft_str_is_alnum(token_str))
	{
		*cmd_bool = TRUE;
		return (TOKEN_CMD);
	}
	else
		return (TOKEN_STR);
}

t_token	*create_token(t_list **tokens, char *token_str, t_bool *cmd_bool)
{
	t_token_type	last_type;
	t_list			*last_lst;
	t_token			*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	last_lst = ft_lstlast(*tokens);
	last_type = TOKEN_PIPE;
	if (last_lst)
		last_type = ((t_token *)(last_lst->content))->type;
	new_token->type = determine_token_type(token_str, last_type, cmd_bool);
	new_token->token = token_str;
	return (new_token);
}

void	tokenize(t_list **tokens, char *line)
{
	t_token			*token;
	size_t			cur_token_len;
	size_t			i;
	t_bool			cmd_bool;

	cmd_bool = FALSE;
	i = 0;
	if (!line || check_quotes(line))
		return ;
	while (line[i])
	{
		cur_token_len = count_token_len(&line[i]);
		token = create_token(tokens, ft_substr(line, i, cur_token_len), &cmd_bool);
		ft_lstadd_back(tokens, ft_lstnew(token));
		i += cur_token_len;
		while (line[i] == ' ') // FIXME replace by iswhitespace()
			++i;
	}
}
