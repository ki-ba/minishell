#include "minishell.h"

t_exec_node	*create_exec_node(void)
{
	t_exec_node	*new;

	new = ft_calloc(1, sizeof (*new));
	// new->cmd = NULL;
	new->cmd = ft_calloc(1, sizeof(char *));
	new->filename[0] = NULL;
	new->filename[1] = NULL;
	new->io[0] = STDIN_FILENO;
	new->io[1] = STDOUT_FILENO;
	return (new);
}

void	del_exec_node(void *node)
{
	t_exec_node	*nnode;

	nnode = (t_exec_node *) node;
	free(nnode->filename[0]);
	free(nnode->filename[1]);
	ft_free_arr(nnode->cmd);
	free(nnode);
}
