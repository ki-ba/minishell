/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:35:23 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/06 13:36:54 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "parsing.h"
#include <readline/readline.h>

static void	set_child_io(t_minishell *ms, t_list **cur, int pipe_fd[2])
{
	if ((*cur)->next)
	{
		if (dup2(pipe_fd[1], STDOUT_FILENO) < 0)
			ms->error = ERR_DUP;
		sclose(pipe_fd[0]);
		sclose(pipe_fd[1]);
	}
	if (ms->interface)
	{
		if (dup2(ms->interface, STDIN_FILENO) < 0)
			ms->error = ERR_DUP;
		sclose(ms->interface);
	}
}

static int	child(t_minishell *ms, t_list **cur, int pipe_fd[2])
{
	int			pid;
	char		**cmd;
	t_exec_node	*exe;

	exe = (t_exec_node *)(*cur)->content;
	pid = fork();
	if (pid == 0)
	{
		rl_clear_history();
		set_child_io(ms, cur, pipe_fd);
		ft_lstclear_but(&ms->exec_lst, del_exec_node, *cur);
		cmd = duplicate_arr(exe->cmd);
		ms->error = apply_redirections(ms, cur);
		if (ms->error == ERR_DUP || !cmd)
		{
			if (!cmd)
				ms->error = ERR_ALLOC;
			clean_exit_child(ms, cur, cmd);
			exit(ms->error);
		}
		ms->error = try_exec(ms, &ms->exec_lst, cmd);
	}
	sclose(exe->io[0]);
	return (pid);
}

int	dup_n_fork(t_minishell *ms, t_list **cur)
{
	int		pipe_fd[2];
	int		pid;

	pipe_fd[0] = 0;
	pipe_fd[1] = 0;
	if ((*cur)->next)
	{
		if (pipe(pipe_fd) != 0)
			return (-1);
	}
	pid = child(ms, cur, pipe_fd);
	if (ms->interface)
	{
		sclose(ms->interface);
	}
	if ((*cur)->next)
	{
		ms->interface = dup(pipe_fd[0]);
		sclose(pipe_fd[0]);
		sclose(pipe_fd[1]);
	}
	return (pid);
}
