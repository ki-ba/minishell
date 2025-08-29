/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:40 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/19 16:38:45 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "error.h"
#include "lexing.h"

/**
 * @brief util function to add an entry to an array of strings.
 * @param arr the array to add `str` to.
 * @param str the string to add at the end of `arr`.
 * @return the updated array, or NULL if an error occcured.
 */
char	**add_to_array(char **arr, char *str)
{
	char	**arr2;
	size_t	i;
	size_t	initial_size;

	arr2 = NULL;
	i = 0;
	initial_size = get_arr_length(arr);
	arr2 = ft_calloc(initial_size + 2, sizeof(char *));
	if (!arr2)
		return (NULL);
	while (i < initial_size)
	{
		arr2[i] = arr[i];
		++i;
	}
	free(arr);
	arr2[initial_size] = ft_strdup(str);
	arr2[initial_size + 1] = NULL;
	if (!arr2[initial_size])
	{
		ft_free_arr(arr2);
		return (NULL);
	}
	return (arr2);
}

/**
 * @brief checks if passed string is non-null, non-empty, and quotes are
 * @brief correctly closed.
 * @return 1 if list is null / empty or there are unclosed quotes
 * @return 0 otherwise.
 */
int	check_parsing(char str[])
{
	if (!str || !ft_strncmp(str, "\0", 1) || check_quotes(str))
		return (1);
	return (0);
}

static int	is_a_redirect(t_token_type type)
{
	return (type >= T_REDIR_IN && type <= T_HD);
}

/**
	* @brief attributes a type to every token on the list, then removes quotes
	* @brief inside tokens.
	* @param tokens the token list.
	* @return an errror code (described in error.h)
*/
int	process_tokens(t_list *tokens)
{
	t_token	*token;
	t_token	*token2;

	while (tokens->next)
	{
		token = (t_token *) tokens->content;
		token2 = (t_token *) tokens->next->content;
		if (is_a_redirect(token->type) && is_a_redirect(token2->type))
			return (ERR_PARSING);
		if (is_a_redirect(token->type) && token2->type == T_PIPE)
			return (ERR_PARSING);
		if (token->type == T_PIPE && token2->type == T_PIPE)
			return (ERR_PARSING);
		tokens = tokens->next;
	}
	token = (t_token *) tokens->content;
	if (!tokens->next && (token->type == T_PIPE || is_a_redirect(token->type)))
		return (ERR_PARSING);
	ft_lstiter(tokens, remove_quotes);
	return (0);
}
