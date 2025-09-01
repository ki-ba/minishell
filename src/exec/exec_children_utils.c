/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_children_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:35:23 by mlouis            #+#    #+#             */
/*   Updated: 2025/09/01 20:09:58 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "parsing.h"
#include <sys/stat.h>
#include "minishell.h"
#include <unistd.h>

static void	set_child_io(t_minishell *ms, t_list **cur, int pipe_fd[2])
{
	if ((*cur)->next)
	{
		dup2(pipe_fd[1], STDOUT_FILENO);
		sclose(pipe_fd[0]);
		sclose(pipe_fd[1]);
	}
	if (ms->interface)
	{
		dup2(ms->interface, STDIN_FILENO);
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
		set_child_io(ms, cur, pipe_fd);
		ft_lstclear_but(&ms->exec_lst, del_exec_node, *cur);
		if (apply_redirections(cur) < 0)
		{
			destroy_ms(ms);
			exit(1);
		}
		cmd = duplicate_arr(exe->cmd); //! LEAK && INV READ
		if (cmd)
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
