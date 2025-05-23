#include "data_structures.h"
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

	arr2 = 0;
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
	return (arr2);
}

static void	handle_redirect(t_token *token, t_redir *redir_type)
{
	if (!strncmp(token->token, ">", 2) || !strncmp(token->token, ">>", 3))
		*redir_type = OUTFILE;
	else if (!strncmp(token->token, "<", 2) || !strncmp(token->token, "<<", 3))
		*redir_type = INFILE;
}

static void	handle_file(t_exec_node *node, t_token *token, t_redir redir_type)
{
	node->io[redir_type] = 3;
	node->filename[redir_type] = ft_strdup(token->token);
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
			node->cmd = add_to_array(node->cmd, token->token);
		else if (token->type == TOKEN_REDIRECT)
			handle_redirect(token, &redir_type);
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
		ft_printf("IO : [%d;%d]\n", (current->io)[0], (current->io)[1]);
		ft_printf("infile : %s\n outfile : %s\n", (current->filename)[0], (current->filename)[1]);
		ft_printf("argv : \n");
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
