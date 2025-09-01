/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:47 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 18:28:41 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"
#include "error.h"

t_token_type	token_type(char val[], t_token_type *last_type, t_bool *cmd_b)
{
	int	redir_type;

	redir_type = determine_redirect(val);
	if (redir_type)
		return (redir_type);
	else if (*last_type > T_PIPE && *last_type < T_FILE)
		return (T_FILE);
	else if (determine_option(val))
		return (T_OPT);
	else if (determine_pipe(val))
	{
		*cmd_b = FALSE;
		return (T_PIPE);
	}
	else if (!(*cmd_b) && ft_str_is_alnum(val))
	{
		*cmd_b = TRUE;
		return (T_CMD);
	}
	else
		return (T_STR);
}

t_token	*token(t_list **tokens, char *token_str, t_bool *cmd_bool)
{
	t_token_type	last_type;
	t_list			*last_lst;
	t_token			*new_token;

	if (!token_str)
		return (NULL);
	new_token = malloc(sizeof(t_token));
	if (!new_token)
	{
		free(token_str);
		return (NULL);
	}
	last_lst = ft_lstlast(*tokens);
	last_type = T_PIPE;
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
			free(line);
			ft_lstclear(tokens, deltoken);
			deltoken(cur_token);
			return (ERR_ALLOC);
		}
		ft_lstadd_back(tokens, new);
		i += cur_len;
		while (ft_iswhitespace(line[i]))
			++i;
	}
	return (!line * ERR_PARSING);
}
