/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:59:54 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 10:46:58 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "libft.h"
#include "data_structures.h"
#include "ms_utils.h"
#include "exec.h"
#include "signals.h"
#include "env.h"
#include "minishell.h"
#include "parsing.h"

/**
 * @brief cleans memory before exit()ing.
 * Should only be called in children processes, after execve has failed or 
 * a builtin has been executed.
 */
int	clean_exit_child(t_minishell *ms, t_list **node, char **cmd)
{
	ft_lstdelone(*node, del_exec_node);
	destroy_ms(ms);
	if (ms->error == ERR_ALLOC)
		error_handler(ms);
	ft_free_arr(cmd);
	return (ms->error);
}

/** tries to execute the current exec node. determines a path to the wanted
 * command and creates an env. array, then execve. exits on failure.
 */
int	try_exec(t_minishell *ms, t_list **exec, char **cmd)
{
	char		*path;
	char		**env_arr;

	ms->error = 127;
	if (is_builtin(cmd))
		ms->error = call_cmd(ms, cmd);
	else
	{
		env_arr = envlist_to_arr(ms->env);
		path = path_to_cmd(cmd, ms->env);
		ms->error = define_error(path);
		if (path && env_arr && ms->error == 0)
			execve(path, cmd, env_arr);
		else if (!path || !env_arr)
			ms->error = ERR_ALLOC;
		ft_multifree(1, 1, path, env_arr);
		if (ms->error == 127)
			ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
	}
	clean_exit_child(ms, exec, cmd);
	exit(ms->error);
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
