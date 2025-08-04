/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexing_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:01:07 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 14:22:05 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

/**
 * @brief helper function to for check_quotes.
 */
static int	check_open(int open, char c)
{
	if (c == '\'')
	{
		if (open == 0)
			open = 1;
		else if (open == 1)
			open = 0;
	}
	if (c == '"')
	{
		if (open == 0)
			open = 2;
		else if (open == 2)
			open = 0;
	}
	return (open);
}

/**
 * @brief checks wether the provided `line` has unclosed quotes.
 * @param open is 0 when not open, 1 when single quote, 2 when double.
 * @returns 0 if all quotes are correctly closed, non-zero otherwise.
 */
int	check_quotes(char *line)
{
	size_t	i;
	int		open;

	open = 0;
	i = 0;
	if (!line)
		return (1);
	while (line[i])
	{
		if (line[i] == '\'' || line [i] == '"')
			open = check_open(open, line[i]);
		++i;
	}
	return (open);
}

/**
	* @brief counts the length of the first token of the provided line.
	* @brief a "token" is a sequence of characters delimited by an
	* @brief unescaped space or the end of the string.
*/
size_t	count_token_len(char *line)
{
	size_t		i;
	int			simple_q;
	int			double_q;

	i = 0;
	simple_q = 0;
	double_q = 0;
	while (line[i] && (line[i] != ' ' || simple_q || double_q))
	{
		if (line[i] == '"')
			double_q = !double_q;
		else if (line[i] == '\'')
			simple_q = !simple_q;
		++i;
	}
	return (i);
}
