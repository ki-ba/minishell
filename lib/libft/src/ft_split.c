/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kiba <kiba@student.42lyon.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 13:10:44 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/09 11:15:36 by kiba             ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	define_number_of_words(char const *s, char sep)
{
	size_t	size;
	int		i;
	int		is_first_char;

	is_first_char = 1;
	i = 0;
	size = 0;
	while (s[i])
	{
		if (s[i] == sep)
			is_first_char = 1;
		else if (is_first_char)
		{
			++size;
			is_first_char = 0;
		}
		++i;
	}
	return (size);
}

static size_t	define_word_size(char const *s, char sep)
{
	size_t	i;

	i = 0;
	while (s[i] != sep && s[i])
		++i;
	return (i);
}

static char	**free_arr(char **arr, size_t last_index)
{
	size_t	i;

	i = 0;
	while (i < last_index)
	{
		free(arr[i]);
		++i;
	}
	free(arr);
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	number_of_words;
	size_t	word_size;

	if (!s)
		return (0);
	i = 0;
	number_of_words = define_number_of_words(s, c);
	arr = malloc((number_of_words + 1) * sizeof(char *));
	if (!arr)
		return (NULL);
	while (number_of_words--)
	{
		while (*s == c)
			++s;
		word_size = define_word_size(s, c);
		arr[i++] = ft_substr(s, 0, word_size);
		if (!arr[i - 1])
			return (free_arr(arr, i - 1));
		s += word_size;
	}
	arr[i] = NULL;
	return (arr);
}
