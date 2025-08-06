/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/29 13:35:23 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 15:32:11 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "parsing.h"
#include "env.h"
#include "signals.h"
#include <sys/stat.h>

void	failed_file_handler(t_list **exec, t_env_lst **env, int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
	destroy_env_lst(*env);
	ft_lstclear(exec, del_exec_node);
	exit(1);
}

/** creates a separate process for each command, 
 * creating pipes when necessary.*/
pid_t	dup_n_fork(t_list **exec, t_list **cur, t_env_lst **env, int *nxt_pip)
{
	pid_t		pid;
	int			pipe_fd[2];
	t_exec_node	*exe;

	exe = (t_exec_node *)(*cur)->content;
	if (pipe(pipe_fd) < 0)
		return (-1);
	pid = fork();
	if (pid == 0)
	{
		if (exe->status || exe->io[0] == -1 || exe->io[1] == -1)
			failed_file_handler(exec, env, pipe_fd);
		ft_lstclear_but(exec, del_exec_node, *cur);
		exec_child(cur, env, nxt_pip, pipe_fd);
	}
	else
		exec_parent(exe, nxt_pip, pipe_fd);
	if (!(*cur)->next && pipe_fd[0] > 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] > 0)
		close(pipe_fd[1]);
	return (pid);
}

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

void	set_child_io(t_list **exe_ls, t_exec_node *exe, int *nxt_pip, int p[2])
{
	if (p[0] > 0)
		close(p[0]);
	if ((*exe_ls)->next && exe->io[1] == STDOUT_FILENO)
		exe->io[1] = p[1];
	if (*nxt_pip && exe->io[0] == STDIN_FILENO)
		exe->io[0] = *nxt_pip;
	dup2(exe->io[1], STDOUT_FILENO);
	if (exe->io[1] != STDOUT_FILENO && exe->io[1] > 0)
		close(exe->io[1]);
	dup2(exe->io[0], STDIN_FILENO);
	if (exe->io[0] != STDIN_FILENO)
	{
		if (g_signal == 2 && exe->file_exist)
			unlink(exe->filename[1]);
		if (exe->io[0] > 0)
			close(exe->io[0]);
	}
	if (p[1] > 0)
		close(p[1]);
	if (*nxt_pip > 0)
		close(*nxt_pip);
}
