/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:29 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/02 19:50:16 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "error.h"
#include "libft.h"
#include "lexing.h"
#include "env.h"

static char	*expand_dollar(t_minishell *ms, char *str, size_t i, size_t len);
static char	*expand_metachar(char *str, size_t i, size_t len);
static char	*set_chunk_val(t_minishell *ms, char *str, size_t i, size_t len, int option);

char	*expand_line(t_minishell *ms, char str[], int option)
{
	size_t	i;
	size_t	part_len;
	char	*expanded;
	char	*next_chunk;

	i = 0;
	expanded = ft_calloc(1, sizeof(char));
	if (!expanded)
	{
		ms->error = ERR_ALLOC;
		return (NULL);
	}
	while (str[i])
	{
		part_len = get_part_len(&str[i], option);
		next_chunk = set_chunk_val(ms, str, i, part_len, option);
		i += part_len;
		if (option == METACHAR && is_metachar(str[i]))
			++i;
		if (option == METACHAR && (str[i] == '<' || str[i] == '>'))
			++i;
		join_in_place(&expanded, next_chunk);
		if (option == METACHAR)
			printf("WW i: %zu(%c) ; pl: %zu(%c)\n", i, str[i], part_len, str[part_len + 1]);
	}
	return (expanded);
}

static char	*set_chunk_val(t_minishell *ms, char *str, size_t i, size_t len, int option)
{
	char		*next_chunk;

	// if (option == METACHAR && must_expand(str, i) && i == 0 && is_metachar(str[i]))
	// {
	// 	next_chunk = ft_strdup(" ");
	// 	return (next_chunk);
	// }
	// if (option == METACHAR && i == 0 && is_metachar(str[i]))
	// {
	// 	++i;
	// 	--len;
	// 	if (str[i] == '<' || str[i] == '>')
	// 	{
	// 		++i;
	// 		--len;
	// 	}
	// }
	// TODO:
	//! echo '$PWD' not working
	//! echo "bim|bam" | rev not working (double meta char)
	if (str[i] == '$' || is_metachar(str[i + len]))
	{
		if (option == DOLLAR && str[i] == '$' && must_expand(str, i))
			next_chunk = expand_dollar(ms, str, i, len);
		if (option == METACHAR && is_metachar(str[i + len]) && must_expand(str, i + len))
			next_chunk = expand_metachar(str, i, len);
		if (option == METACHAR)
		{
			printf("str[len]= %c ; i= %zu ; len= %zu\n", str[i+len], i, len);
			if (is_metachar(str[i + len]))
				printf("META\n");
			if (must_expand(str, i + len))
				printf("EXPANDABLE\n");
		}
	}
	else
		next_chunk = ft_substr(str, i, len);
	return (next_chunk);
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
	size_t	pos;

	pos = i + len;
	printf("i: %zu(%c) ; len: %zu(%c)\n", i, str[i], len, str[len]);
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
