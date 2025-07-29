#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

int	try_exec(t_list **exec, char **cmd, t_env_lst *env)
{
	char		*path;
	char		**env_arr;
	int			err;

	err = 127;
	if (is_builtin(cmd))
		err = call_cmd(cmd, env);
	else
	{
		env_arr = envlist_to_arr(env);
		path = path_to_cmd(cmd, env);
		err = define_error(path, env);
		if (path && env_arr && !err)
			execve(path, cmd, env_arr);
		ft_free_arr(env_arr);
		free(path);
		if (err == 127)
			ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
	}
	destroy_env_lst(env);
	ft_lstdelone(*exec, del_exec_node);
	exec = NULL;
	ft_free_arr(cmd);
	exit(err);
	return (err);
}

void	exec_child(t_list **cur, t_env_lst **env, int *next_pipe, int pipe[2])
{
	t_exec_node	*exe;
	char		**cmd;

	signal(SIGQUIT, SIG_DFL);
	exe = (t_exec_node *)(*cur)->content;
	set_child_io(cur, exe, next_pipe, pipe);
	cmd = duplicate_arr(exe->cmd);
	try_exec(cur, cmd, *env);
}

void	exec_parent(t_exec_node *exe, int *nxt_pipe, int pipe[2])
{
	update_signals(1);
	if (*nxt_pipe > 0)
		close(*nxt_pipe);
	*nxt_pipe = pipe[0];
	if (exe->io[0] != STDIN_FILENO && exe->io[0] > 0)
		close(exe->io[0]);
	if (exe->io[1] != STDOUT_FILENO && exe->io[1] > 0)
		close(exe->io[1]);
}

int	exec_unique_cmd(t_list **exec_lst, t_env_lst *env)
{
	t_exec_node	*exe;
	int			saved;
	int			err;

	exe = (t_exec_node *)(*exec_lst)->content;
	if (exe->status || exe->io[0] == -1 || exe->io[1] == -1)
		return (1);
	saved = dup(STDOUT_FILENO);
	if (exe->filename[1])
	{
		dup2(exe->io[1], STDOUT_FILENO);
		if (exe->io[1] != STDOUT_FILENO && exe->io[1] > 0)
			close(exe->io[1]);
	}
	err = call_cmd(exe->cmd, env);
	if (exe->filename[1])
		dup2(saved, STDOUT_FILENO);
	if (saved > 0)
		close (saved);
	return (err);
}

/**
* entry point of the execution part of the program.
* takes an exec_list and the environment and executes it.
*/
pid_t	exec_pipeline(t_list **exec_lst, t_env_lst **env)
{
	t_list		*current;
	pid_t		pid;
	int			next_pipe_entry;

	next_pipe_entry = 0;
	current = *exec_lst;
	while (current)
	{
		pid = dup_n_fork(exec_lst, &current, env, &next_pipe_entry);
		current = current->next;
	}
	return (pid);
}
