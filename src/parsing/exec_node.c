#include "minishell.h"
#include <unistd.h>

/** @brief create a new empty t_exec_node structure */
t_exec_node	*create_exec_node(void)
{
	t_exec_node	*new;

	new = ft_calloc(1, sizeof (*new));
	new->cmd = ft_calloc(1, sizeof(char *));
	new->filename[0] = NULL;
	new->filename[1] = NULL;
	new->io[0] = STDIN_FILENO;
	new->io[1] = STDOUT_FILENO;
	new->status = 0;
	new->file_exist = FALSE;
	return (new);
}

/** destroys given t_exec_node structure. */
void	del_exec_node(void *node)
{
	t_exec_node	*nnode;

	nnode = (t_exec_node *) node;
	free(nnode->filename[0]);
	free(nnode->filename[1]);
	ft_free_arr(nnode->cmd);
	if (nnode->io[0] != STDIN_FILENO)
		close(nnode->io[0]);
	if (nnode->io[1] != STDOUT_FILENO)
		close(nnode->io[1]);
	free(nnode);
}
