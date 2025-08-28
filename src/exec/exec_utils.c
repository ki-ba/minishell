/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:35:23 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/27 15:04:38 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "parsing.h"
#include "env.h"
#include "signals.h"
#include <sys/stat.h>
#include "minishell.h"
#include <unistd.h>

char	*path_to_cmd(char *cmd[], t_env_lst *env)
{
	char	*path;

	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd[0], env);
	return (path);
}

int	define_error(char path[], t_env_lst *env)
{
	int			err;
	struct stat	fi;

	(void)env;
	stat(path, &fi);
	if (access(path, F_OK))
		err = 127;
	else if (S_ISDIR(fi.st_mode) || access(path, X_OK))
	{
		ft_printf_fd(2, "minishell: %s: Permission denied\n", path);
		err = 126;
	}
	else
		err = 0;
	return (err);
}

int	sclose(int fd)
{
	if (fd >= 0 && fd <= 2)
		return (1);
	else
		return (close(fd));
}
int	apply_redirections(t_list **cur_node)
{
	t_exec_node	*exe;
	int			err;

	err = 0;
	exe = (t_exec_node *)(*cur_node)->content;
	if (exe->io[1] != STDOUT_FILENO)
		err = dup2(exe->io[1], STDOUT_FILENO);
	if (err >= 0 && exe->io[0] != STDIN_FILENO)
		err = dup2(exe->io[0], STDIN_FILENO);
	sclose (exe->io[0]);
	sclose (exe->io[1]);
	return (err);
}

void	set_child_io(t_minishell *ms, t_list **cur, int pipe_fd[2])
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

int	child(t_minishell *ms, t_list **cur, int pipe_fd[2])
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
		cmd = duplicate_arr(exe->cmd);
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
	// if (((t_exec_node *)(*cur)->content)->io[0] != STDIN_FILENO)
	return (pid);
}
