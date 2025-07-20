#include "error.h"
#include "libft.h"
#include "minishell.h"

t_token_type	token_type(char val[], t_token_type *last_type, t_bool *cmd_b)
{
	if (determine_redirect(val))
		return (TOKEN_REDIRECT);
	else if (*last_type == TOKEN_REDIRECT)
		return (TOKEN_FILE);
	else if (determine_option(val))
		return (TOKEN_OPT);
	else if (determine_pipe(val))
	{
		*cmd_b = FALSE;
		return (TOKEN_PIPE);
	}
	else if (!(*cmd_b) && ft_str_is_alnum(val))
	{
		*cmd_b = TRUE;
		return (TOKEN_CMD);
	}
	else
		return (TOKEN_STR);
}

t_token	*token(t_list **tokens, char *token_str, t_bool *cmd_bool)
{
	t_token_type	last_type;
	t_list			*last_lst;
	t_token			*new_token;

	new_token = malloc(sizeof(t_token));
	if (!token_str || !new_token)
	{
		free(token_str);
		return (NULL);
	}
	last_lst = ft_lstlast(*tokens);
	last_type = TOKEN_PIPE;
	if (last_lst)
		last_type = ((t_token *)(last_lst->content))->type;
	new_token->type = token_type(token_str, &last_type, cmd_bool);
	new_token->token = token_str;
	return (new_token);
}

int	tokenize(t_list **tokens, char *line)
{
	t_token			*cur_token;
	size_t			cur_len;
	size_t			i;
	t_bool			cmd_b;
	t_list			*new;

	cmd_b = FALSE;
	i = 0;
	while (line && line[i])
	{
		cur_len = count_token_len(&line[i]);
		cur_token = token(tokens, ft_substr(line, i, cur_len), &cmd_b);
		new = ft_lstnew(cur_token);
		if (!cur_token || !new)
		{
			ft_lstclear(tokens, deltoken);
			return (ERR_ALLOC);
		}
		ft_lstadd_back(tokens, new);
		i += cur_len;
		while (ft_iswhitespace(line[i]))
			++i;
	}
	return (!line);
}
