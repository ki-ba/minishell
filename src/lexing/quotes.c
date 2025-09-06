/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:00 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 14:22:51 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"
#include <sys/types.h>

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static ssize_t	look_for_next_quote(char str[], ssize_t q)
{
	ssize_t	i;

	i = q + 1;
	while (str[i])
	{
		if (str[i] == str[q])
			return (i);
		++i;
	}
	return (-1);
}

/**
	* @brief removes quotes from the given string in-place.
	* @brief the string is re-null-terminated accordingly.
	* @brief exceeding space is not freed.
*/
static void	remove_quotes_str(char str[])
{
	ssize_t	i;
	ssize_t	j;
	ssize_t	next_quote;

	i = 0;
	j = 0;
	next_quote = -1;
	while (str[i])
	{
		if (i == next_quote)
			next_quote = -1;
		else if (next_quote == -1 && is_quote(str[i]))
		{
			next_quote = look_for_next_quote(str, i);
			if (next_quote == -1)
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		++i;
	}
	str[j] = '\0';
}

void	remove_quotes(void *item)
{
	char	*str;

	str = (char *)((t_token *)item)->token;
	remove_quotes_str(str);
}
