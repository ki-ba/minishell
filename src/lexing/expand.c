/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:29 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/30 14:16:26 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*expand_dollar(t_env_lst *env, char *str, size_t i, size_t len);
static char	*expand_metachar(char *str, size_t i, size_t len);
static char	*set_chunk_val(t_env_lst *env, char *str, size_t i, size_t len);

char	*expand_line(t_env_lst *env, char str[])
{
	size_t	i;
	size_t	part_len;
	char	*expanded;
	char	*next_chunk;

	i = 0;
	expanded = ft_calloc(1, sizeof(char));
	if (!expanded)
		return (NULL);
	while (str[i])
	{
		part_len = get_part_len(&str[i]);
		next_chunk = set_chunk_val(env, str, i, part_len);
		i += part_len;
		if (!is_inquote(str, i) && is_metachar(str[i]))
			++i;
		if (!is_inquote(str, i) && (str[i] == '<' || str[i] == '>'))
			++i;
		join_in_place(&expanded, next_chunk);
		if (!expanded)
			return (NULL);
	}
	return (expanded);
}

static char	*set_chunk_val(t_env_lst *env, char *str, size_t i, size_t len)
{
	char		*next_chunk;

	if (i == 0 && is_metachar(str[i]))
	{
		++i;
		--len;
		if (str[i] == '<' || str[i] == '>')
		{
			++i;
			--len;
		}
	}
	if (str[i] == '$' && must_expand(str, i))
		next_chunk = expand_dollar(env, str, i, len);
	else if (must_expand(str, i) && i > 0 && is_metachar(str[i - 1]))
		next_chunk = expand_metachar(str, i, len);
	else
		next_chunk = ft_substr(str, i, len);
	return (next_chunk);
}

static char	*expand_dollar(t_env_lst *env, char *str, size_t i, size_t len)
{
	char		*varname;
	char		*next_chunk;
	t_env_lst	*tmp;

	varname = ft_substr(str, i + 1, len - (len > 1));
	if (!varname)
		return (NULL);
	if (ft_isalnum(str[i + 1]) || str[i + 1] == '_' || str[i + 1] == '?')
	{
		tmp = search_env_var(env, varname);
		if (tmp)
			next_chunk = ft_concat(3, "\"", tmp->value, "\"");
		else
			next_chunk = ft_strdup("");
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

	if (!is_inquote(str, i))
		--i;
	varname = ft_substr(str, i + 1, len);
	if (!varname)
		return (NULL);
	ft_bzero(meta, 3);
	meta[0] = str[i];
	if (str[i] != '|' && (i > 0 && str[i] == str[i - 1]))
		meta[1] = meta[0];
	if (is_inquote(str, i))
		next_chunk = ft_concat(2, meta, varname);
	else
		next_chunk = ft_concat(4, " ", meta, " ", varname);
	free(varname);
	return (next_chunk);
}
