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

/** handles current TOKEN_FILE.
 *	if the current token is a heredoc delimiter, call appropriate function.
 *	otherwise setup the token's `filename` attribute to the name of the file
 *	to read from / write into.
 *	if `open` fails, write on stderr, then return an error.
 * */
int	handle_file(t_exec_node *node, t_token *token, t_redir redir, t_list **lst)
{
	int	fd;

	fd = 0;
	if (redir == 0 && node->io[redir] > MAX_FD)
		node->io[0] = read_input(token->token);
	else if (node->status == 0)
	{
		node->filename[redir] = ft_strdup(token->token);
		if (!node->filename[redir])
		{
			ft_lstclear(lst, del_exec_node);
			return (ERR_ALLOC);
		}
		if (node->io[0] != STDIN_FILENO && access(node->filename[1], F_OK))
			node->file_exist = TRUE;
		fd = open(node->filename[redir], node->oflags[redir], 0644);
		if (fd < 0)
		{
			perror("open");
		}
		node->io[redir] = fd;
	}
	return (fd < 0);
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
