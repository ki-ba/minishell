/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:29 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/03 13:21:02 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "error.h"
#include "libft.h"
#include "lexing.h"
#include "env.h"

static char	*expand_dollar(t_minishell *ms, char *str, size_t i, size_t len);
static char	*expand_metachar(char *str, size_t i, size_t len);

char	*expand_line_dollar(t_minishell *ms, char str[], char *expanded)
{
	size_t	i;
	size_t	part_len;
	char	*next_chunk;

	i = 0;
	while (str[i])
	{
		part_len = get_part_len_dollar(&str[i]);
		if (str[i] == '$' && must_expand(str, i))
			next_chunk = expand_dollar(ms, str, i, part_len);
		else
			next_chunk = ft_substr(str, i, part_len);
		i += part_len;
		join_in_place(&expanded, next_chunk);
	}
	return (expanded);
}

char	*expand_line_metachar(char str[], char *expanded)
{
	size_t	i;
	size_t	part_len;
	char	*next_chunk;

	i = 0;
	while (str[i])
	{
		part_len = get_part_len_metachar(&str[i]);
		if (is_metachar(str[i + part_len]) && must_expand(str, i + part_len))
			next_chunk = expand_metachar(str, i, part_len);
		else
			next_chunk = ft_substr(str, i, part_len);
		i += part_len;
		if (is_metachar(str[i]))
			++i;
		if (str[i] == '<' || str[i] == '>')
			++i;
		join_in_place(&expanded, next_chunk);
	}
	return (expanded);
}

char	*expand_line(t_minishell *ms, char str[], int option)
{
	char	*expanded;

	expanded = ft_calloc(1, sizeof(char));
	if (!expanded)
	{
		ms->error = ERR_ALLOC;
		return (NULL);
	}
	if (option == DOLLAR)
		return (expand_line_dollar(ms, str, expanded));
	if (option == METACHAR)
		return (expand_line_metachar(str, expanded));
	return (expanded);
}

static char	*expand_dollar(t_minishell *ms, char *str, size_t i, size_t len)
{
	char		*varname;
	char		*next_chunk;
	t_env_lst	*tmp;

	varname = ft_substr(str, i + 1, len - (len > 1));
	if (!varname)
		return (NULL);
	if (str[i + 1] == '?')
		next_chunk = ft_itoa(ms->error);
	else if (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?')
	{
		tmp = search_env_var(ms->env, varname);
		if (tmp)
			next_chunk = ft_concat(3, "\"", tmp->value, "\"");
		else
			next_chunk = ft_strdup("\"\"");
	}
	else if (!str[i + 1] || str[i + 1] == '$' || is_inquote(str, i + 1))
		next_chunk = ft_strdup("$");
	else
		next_chunk = ft_strdup("");
	free(varname);
	return (next_chunk);
}

static char	*expand_metachar(char *str, size_t i, size_t len)
{
	char	*varname;
	char	*next_chunk;
	char	meta[3];
	size_t	pos;

	pos = i + len;
	varname = ft_substr(str, i, len);
	if (!varname)
		return (NULL);
	ft_bzero(meta, 3);
	meta[0] = str[pos];
	if (str[pos] != '|' && str[pos] == str[pos + 1])
		meta[1] = meta[0];
	if (is_inquote(str, pos))
		next_chunk = ft_concat(2, varname, meta);
	else
		next_chunk = ft_concat(4, varname, " ", meta, " ");
	free(varname);
	return (next_chunk);
}
