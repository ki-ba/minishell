#include "minishell.h"

/**
 * @brief util function to add an entry to an array of strings.
 * @param arr the array to add `str` to.
 * @param str the string to add at the end of `arr`.
 * @return the updated array.
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
	while (i < initial_size)
	{
		arr2[i] = arr[i];
		++i;
	}
	arr2[initial_size] = ft_strdup(str);
	arr2[initial_size + 1] = NULL;
	free(arr);
	return (arr2);
}

int	check_parsing(char str[])
{
	if (!str || !ft_strncmp(str, "\0", 1) || check_quotes(str))
	{
		free (str);
		return (1);
	}
	return (0);
}

int	process_tokens(t_list *tokens)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	if (!tokens->next
		&& (token->type == TOKEN_PIPE || token->type == TOKEN_REDIRECT))
		return (ERR_PARSING);
	ft_lstiter(tokens, remove_quotes);
	return (0);
}
