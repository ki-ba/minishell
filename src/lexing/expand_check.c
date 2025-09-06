/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:55 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/01 19:33:28 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"

int	is_metachar(char c)
{
	return (c == '<' || c == '>' || c == '|');
}

t_bool	is_inquote(char *str, size_t pos)
{
	size_t	i;
	int		sq;
	int		dq;

	i = 0;
	sq = 0;
	dq = 0;
	while (i < pos)
	{
		if (str[i] == '\'')
			++sq;
		if (str[i] == '"')
			++dq;
		++i;
	}
	return ((sq % 2) + (dq % 2) % 2);
}

static t_bool	look_for_hd(char str[], size_t pos)
{
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	while (i < pos)
	{
		if (str[i] == '<')
			++n;
		else if (str[i] != '\"' && !ft_iswhitespace(str[i]))
			n = 0;
		++i;
	}
	return (n == 2);
}

t_bool	must_expand(char str[], size_t pos)
{
	char	quote;
	size_t	i;

	i = 0;
	quote = '\0';
	while (i < pos)
	{
		if ((str[i] == '"' || str[i] == '\'') && !quote)
			quote = str[i];
		else if (str[i] == quote)
			quote = '\0';
		++i;
	}
	return (!look_for_hd(str, pos) && quote != '\'');
}

int	check_meta_validity(char *str)
{
	size_t	i;

	i = 0;
	while (str && str[i])
	{
		if (is_metachar(str[i]) && !is_inquote(str, i))
		{
			if (str[i] == '|' && ((str[i + 1] == '>' || str[i + 1] == '<')))
				return (ERR_PARSING);
			if (str[i] == '>' && ((str[i + 1] == '|' || str[i + 1] == '<')))
				return (ERR_PARSING);
			if (str[i] == '<' && ((str[i + 1] == '|' || str[i + 1] == '>')))
				return (ERR_PARSING);
			if (str[i] == '<' || str[i] == '>')
			{
				if (str[i + 1] == str[i] && str[i + 2] == str[i])
					return (ERR_PARSING);
			}
		}
		++i;
	}
	if (str && i > 0 && is_metachar(str[i - 1]) && !is_inquote(str, i - 1))
		return (ERR_PARSING);
	return (SUCCESS);
}
