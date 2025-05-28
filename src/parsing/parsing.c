#include "data_structures.h"
#include "error.h"
#include "libft.h"
#include "minishell.h"

/**
* Parse the token list and create a process list with correct infiles,
* outfiles, argv and environments.
*
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

static int	handle_redirect(t_exec_node *node, t_token *token, t_redir *redir)
{
	if (!strncmp(token->token, ">", 2) || !strncmp(token->token, ">>", 3))
	{
		*redir = OUTFILE;
		if (!strncmp(token->token, ">", 2))
			return (O_CREAT | O_TRUNC | O_WRONLY);
		return (O_CREAT | O_APPEND | O_RDONLY);
	}
	else if (!strncmp(token->token, "<", 2) || !strncmp(token->token, "<<", 3))
	{
		*redir = INFILE;
		if (!strncmp(token->token, "<<", 2))
			node->io[0] = MAX_FD + 1;
		return (O_RDONLY);
	}
	return (0);
}

static void	handle_file(t_exec_node *node, t_token *token, t_redir redir)
{
	int	fd;

	if (redir == 0 && node->io[redir] > MAX_FD)
		node->io[0] = here_doc(token->token);
	else
	{
		node->filename[redir] = ft_strdup(token->token);
		if (!node->filename[redir])
			return ;
		fd = open(node->filename[redir], node->oflags[redir], 0644);
		if (fd < 0)
			return (perror("open"));
		node->io[redir] = fd;
	}
}

static void	handle_cmd(t_exec_node *node, t_token *token)
{
	char	**old_arr;

	old_arr = node->cmd;
	node->cmd = add_to_array(node->cmd, token->token);
	if (!node->cmd)
		ft_free_arr(old_arr);
}

t_list	*parse_tokens(t_list *tokens)
{
	t_list		*exec_lst;
	t_token		*token;
	t_exec_node	*node;
	t_redir		redir_type;

	node = NULL;
	exec_lst = NULL;
	while (tokens)
	{
		token = (t_token *)(tokens)->content;
		if (!node || token->type == TOKEN_PIPE)
		{
			ft_lstadd_back(&exec_lst, ft_lstnew(create_exec_node()));
			node = (t_exec_node *)ft_lstlast(exec_lst)->content;
		}
		if (token->type >= TOKEN_CMD && token->type <= TOKEN_STR)
		{
			handle_cmd(node, token);
			if (!node->cmd)
			{
				ft_lstclear(&exec_lst, del_exec_node);
				return (NULL);
			}
		}
		else if (token->type == TOKEN_REDIRECT)
			node->oflags[redir_type] = handle_redirect(node, token, &redir_type);
		else if (token->type == TOKEN_FILE)
			handle_file(node, token, redir_type);
		tokens = tokens->next;
	}
	return (exec_lst);
}

void	print_exec(t_list	*exec_lst)
{
	t_exec_node	*current;

	while (exec_lst)
	{
		current = (t_exec_node *)exec_lst->content;
		ft_printf("========EXEC NODE=========\n\n");
		ft_printf("IO:	[%d;%d]\n", (current->io)[0], (current->io)[1]);
		ft_printf("infile:	%s\noutfile:	%s\n", (current->filename)[0], (current->filename)[1]);
		ft_printf("argv:	\n");
		ft_print_arr(current->cmd);
		ft_printf("=================\n\n");
		exec_lst = exec_lst->next;
	}
}

void	print_lst(t_list *lst)
{
	while (lst)
	{
		ft_printf("current : %p\nnext : %p\n\n", lst, lst->next);
		lst = lst->next;
	}
}
