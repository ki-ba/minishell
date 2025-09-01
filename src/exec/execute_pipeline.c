/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:59:54 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/27 16:03:53 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "signals.h"
#include "env.h"
#include "minishell.h"
#include "parsing.h"
#include <unistd.h>

int	try_exec(t_minishell *ms, t_list **exec, char **cmd)
{
	char		*path;
	char		**env_arr;
	int			err;

	err = 127;
	if (is_builtin(cmd))
		err = call_cmd(ms, cmd);
	else
	{
		env_arr = envlist_to_arr(ms->env);
		path = path_to_cmd(cmd, ms->env);
		err = define_error(path, ms->env);
		if (path && env_arr && err == 0)
			execve(path, cmd, env_arr);
		ft_free_arr(env_arr);
		free(path);
		if (err == 127)
			ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
	}
	ft_lstdelone(*exec, del_exec_node);
	exec = NULL;
	destroy_ms(ms);
	ft_free_arr(cmd);
	exit(err);
	return (err);
}

int	exec_unique_cmd(t_minishell *ms_data, t_list **exec_lst)
{
	t_exec_node	*exe;
	int			saved;
	int			err;

	exe = (t_exec_node *)(*exec_lst)->content;
	if (exe->status || exe->io[0] == -1 || exe->io[1] == -1)
		return (1);
	saved = dup(STDOUT_FILENO);
	if (exe->io[1])
	{
		dup2(exe->io[1], STDOUT_FILENO);
		if (exe->io[1] != STDOUT_FILENO && exe->io[1] > 0)
			close(exe->io[1]);
	}
	err = call_cmd(ms_data, exe->cmd);
	if (exe->io[1] != STDOUT_FILENO)
		dup2(saved, STDOUT_FILENO);
	if (saved > STDOUT_FILENO)
		close (saved);
	return (err);
}

/**
* entry point of the execution part of the program.
* takes an exec_list and the environment and executes it.
*/
pid_t	exec_pipeline(t_minishell *ms)
{
	t_list		*current;
	pid_t		pid;

	g_signal = 0;
	pid = 0;
	ms->error = 0;
	current = ms->exec_lst;
	while (current && pid > -1)
	{
		pid = dup_n_fork(ms, &current);
		current = current->next;
	}
	if (pid == -1)
		ft_printf_fd(2, "error : failed to create process");
	return (pid);
}
