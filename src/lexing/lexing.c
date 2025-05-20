#include "libft.h"
#include "minishell.h"
#include <string.h>

t_token_type	determine_token_type(char token_str[], t_token_type *last_type, t_bool *cmd_bool)
{
	if (determine_redirect(token_str))
		return (TOKEN_REDIRECT);
	else if (*last_type == TOKEN_REDIRECT)
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
	new_token->type = determine_token_type(token_str, &last_type, cmd_bool);
	new_token->token = token_str;
	return (new_token);
}

void	tokenize(t_list **tokens, char *line)
{
	t_token			*token;
	size_t			cur_len;
	size_t			i;
	t_bool			cmd_bool;

	cmd_bool = FALSE;
	i = 0;
	if (!line || check_quotes(line))
		return ;
	while (line[i])
	{
		cur_len = count_token_len(&line[i]);
		token = create_token(tokens, ft_substr(line, i, cur_len), &cmd_bool);
		ft_lstadd_back(tokens, ft_lstnew(token));
		i += cur_len;
		while (ft_iswhitespace(line[i]))
			++i;
	}
	ft_lstiter(*tokens, remove_quotes);
}

int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}
/**
	* @brief removes quotes from the given string in-place.
	* @brief the string is re-null-terminated accordingly.
	* @brief exceeding space is not freed.
*/
void	remove_quotes(void *item)
{
	char	quote;
	size_t	i;
	size_t	dest_i;
	char	*new_str;
	char	*str;

	str = (char *)((t_token *)item)->token;
	i = 0;
	dest_i = 0;
	quote = '\0';
	new_str = ft_calloc(ft_strlen(str) + 1, sizeof(char));
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (str[i] == quote)
				quote = '\0';
			else if (quote == 0)
				quote = str[i];
			else
				new_str[dest_i++] = str[i];
		}
		else
			new_str[dest_i++] = str[i];
		++i;
	}
	free(str);
	((t_token *)item)->token = new_str;
}
