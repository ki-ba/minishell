/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:00:13 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 14:20:52 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "lexing.h"

void	join_in_place(char **s1, char *s2)
{
	char	*s3;

	s3 = ft_strjoin(*s1, s2);
	free(s2);
	free(*s1);
	*s1 = s3;
}

size_t	varnamelen(char str[])
{
	size_t	i;

	if (str[0] != '$')
		return (0);
	i = 1;
	if (str[i] == '?')
	{
		++i;
		return (i);
	}
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		++i;
	return (i);
}

size_t	get_part_len(char str[])
{
	size_t	i;
	size_t	tmp;

	i = 0;
	if (str[0] == '$')
		i = varnamelen(str);
	else
		i = ft_strlen_c(str, '$');
	tmp = ft_strlen_c(str, '|');
	if (!is_inquote(str, tmp) && i > tmp && tmp > 0)
		i = tmp;
	tmp = ft_strlen_c(str, '<');
	if (!is_inquote(str, tmp) && i > tmp && tmp > 0)
		i = tmp;
	tmp = ft_strlen_c(str, '>');
	if (!is_inquote(str, tmp) && i > tmp && tmp > 0)
		i = tmp;
	return (i);
}
