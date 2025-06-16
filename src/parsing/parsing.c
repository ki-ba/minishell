#include "data_structures.h"
#include "error.h"
#include "libft.h"
#include "minishell.h"
#include <fcntl.h>

/* handles current TOKEN_REDIRECT */
static int	handle_redir(t_exec_node *node, t_token *token, t_redir *redir)
{
	if (!ft_strncmp(token->token, ">", 2) || !ft_strncmp(token->token, ">>", 3))
	{
		printf("token: [%s]\n", token->token);
		*redir = OUTFILE;
		if (!ft_strncmp(token->token, ">", 2))
			node->oflags[*redir] = (O_CREAT | O_TRUNC | O_WRONLY);
		else
			node->oflags[*redir] = (O_CREAT | O_APPEND | O_WRONLY);
		printf("redir= %d\n", *redir);
	}
	if (!ft_strncmp(token->token, "<", 2) || !ft_strncmp(token->token, "<<", 3))
	{
		*redir = INFILE;
		if (!ft_strncmp(token->token, "<<", 2))
			node->io[0] = MAX_FD + 1;
		node->oflags[*redir] = (O_RDONLY);
	}
	return (0);
}

/* handles current TOKEN_FILE */
static int	handle_file(t_exec_node *node, t_token *token, t_redir redir, t_list **exec_lst)
{
	int	fd;

	if (redir == 0 && node->io[redir] > MAX_FD)
		node->io[0] = read_input(token->token);
	else
	{
		node->filename[redir] = ft_strdup(token->token);
		if (!node->filename[redir])
		{
			ft_lstclear(exec_lst, del_exec_node);
			return (ERR_ALLOC);
		}
		fd = open(node->filename[redir], node->oflags[redir], 0644);
		if (fd < 0)
		{
			perror("open");
			node->io[redir] = open("/dev/null", O_RDWR);
			return (ERR_FAIL);
		}
		node->io[redir] = fd;
	}
	return (SUCCESS);
}

/* handles current TOKEN_CMD */
static int	handle_cmd(t_exec_node *node, t_token *token, t_list **exec_list)
{
	char	**old_arr;

	old_arr = node->cmd;
	node->cmd = add_to_array(node->cmd, token->token);
	if (!node->cmd)
	{
		ft_free_arr(old_arr);
		ft_lstclear(exec_list, del_exec_node);
		return (ERR_ALLOC);
	}
	return (SUCCESS);
}

static int	handle_pipe(t_exec_node **node, t_list **exec_lst)
{
	t_list		*new_list_node;
	t_exec_node	*new_node;

	new_node = create_exec_node();
	new_list_node = ft_lstnew(new_node);
	if (!new_node || !new_list_node)
	{
		ft_multifree(2, 0, new_node, new_list_node);
		return (ERR_ALLOC);
	}
	ft_lstadd_back(exec_lst, new_list_node);
	*node = (t_exec_node *)ft_lstlast(*exec_lst)->content;
	return (SUCCESS);
}

/**
* Parse the token list and create a process list with correct infiles,
* outfiles, argv and environments.
*
*/
t_list	*parse_tokens(t_list *tokens)
{
	t_list		*exec_lst;
	t_token		*token;
	t_exec_node	*node;
	t_redir		redir_type;
	int			status;

	status = 0;
	node = NULL;
	exec_lst = NULL;
	while (tokens && !status)
	{
		token = (t_token *)(tokens)->content;
		if (!node || token->type == TOKEN_PIPE)
			status = handle_pipe(&node, &exec_lst);
		if (token->type >= TOKEN_CMD && token->type <= TOKEN_STR)
			status = handle_cmd(node, token, &exec_lst);
		else if (token->type == TOKEN_REDIRECT)
			status = handle_redir(node, token, &redir_type);
		else if (token->type == TOKEN_FILE)
			status = handle_file(node, token, redir_type, &exec_lst);
		tokens = tokens->next;
	}
	return (exec_lst);
}
