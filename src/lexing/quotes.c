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

static int	is_quote(char c)
{
	return (c == '\'' || c == '"');
}

static void	remove_quotes_str(char str[])
{
	char	quote;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	quote = '\0';
	while (str[i])
	{
		if (is_quote(str[i]))
		{
			if (str[i] == quote)
				quote = '\0';
			else if (quote == 0)
				quote = str[i];
			else
				str[j++] = str[i];
		}
		else
			str[j++] = str[i];
		++i;
	}
	str[j] = '\0';
}

/**
	* @brief removes quotes from the given string in-place.
	* @brief the string is re-null-terminated accordingly.
	* @brief exceeding space is not freed.
*/
void	remove_quotes(void *item)
{
	char	*str;

	str = (char *)((t_token *)item)->token;
	remove_quotes_str(str);
}
