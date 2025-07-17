#include "builtins.h"
#include "minishell.h"
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

int	try_exec(char **cmd, t_env_lst *env)
{
	char		*path;
	char		**env_arr;
	int			err;
	struct stat	info;

	err = 127;
	if (is_builtin(cmd))
		err = call_cmd(cmd, env);
	else
	{
		env_arr = envlist_to_arr(env);
		if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
			path = ft_strdup(cmd[0]);
		else
			path = find_path(cmd[0], env);
		if (path && access(path, F_OK) == 0)
		{
			stat(path, &info);
			if (access(path, X_OK) != 0 || S_ISDIR(info.st_mode))
				err = 126;
		}
		if (path)
			execve(path, cmd, env_arr);
		ft_free_arr(env_arr);
		free(path);
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
	}
	destroy_env_lst(env);
	ft_free_arr(cmd);
	exit(err);
}

void	exec_child(t_list **exe_ls, t_env_lst *env, int *next_pipe, int pipe[2])
{
	t_exec_node	*exe;
	char		**cmd;

	signal(SIGQUIT, SIG_DFL);
	close(ft_atoi(get_env_val(env, HIST_FILE, 1)));
	exe = (t_exec_node *)(*exe_ls)->content;
	close(pipe[0]);
	if ((*exe_ls)->next && exe->io[1] == STDOUT_FILENO)
		exe->io[1] = pipe[1];
	if (*next_pipe && exe->io[0] == STDIN_FILENO)
		exe->io[0] = *next_pipe;
	dup2(exe->io[1], STDOUT_FILENO);
	if (exe->io[1] != STDOUT_FILENO)
		close(exe->io[1]);
	dup2(exe->io[0], STDIN_FILENO);
	if (exe->io[0] != STDIN_FILENO)
	{
		if (g_signal == 2 && exe->file_exist)
			unlink(exe->filename[1]);
		close(exe->io[0]);
	}
	close(pipe[1]);
	if (*next_pipe)
		close(*next_pipe);
	cmd = duplicate_arr(exe->cmd);
	ft_lstclear(exe_ls, del_exec_node);
	try_exec(cmd, env);
}

/** creates a separate process for each command, 
 * creating pipes when necessary.*/
pid_t	dup_and_fork(t_list **exec_list, t_list **current, t_env_lst *env, int *next_pipe_entry)
{
	pid_t		pid;
	int			pipe_fd[2];
	t_exec_node	*exe;

	exe = (t_exec_node *)(*current)->content;
	if (pipe(pipe_fd) < 0)
		return (-1);
	pid = fork();
	(void)exec_list;
	if (pid == 0)
	{
		if (exe->io[0] == -1 || exe->io[1] == -1)
			exit(1);
		exec_child(current, env, next_pipe_entry, pipe_fd);
	}
	else
	{
		update_signals(1);
		if (*next_pipe_entry)
			close(*next_pipe_entry);
		*next_pipe_entry = pipe_fd[0];
		if (exe->io[0] != STDIN_FILENO)
			close(exe->io[0]);
		if (exe->io[1] != STDOUT_FILENO)
			close(exe->io[1]);
		// destroy_env_lst(env);
	}
	if (!(*current)->next)
		close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (pid);
}

int exec_unique_cmd(t_list **exec_lst, t_env_lst *env)
{
	t_exec_node	*exe;
	int			saved;
	int			err;

	exe = (t_exec_node *)(*exec_lst)->content;
	if (exe->io[0] == -1 || exe->io[1] == -1)
	{
		return (1);
	}
	saved = dup(STDOUT_FILENO);
	if (exe->filename[1])
	{
		dup2(exe->io[1], STDOUT_FILENO);
		if (exe->io[1] != STDOUT_FILENO)
			close(exe->io[1]);
	}
	err = call_cmd(exe->cmd, env);
	if (exe->filename[1])
		dup2(saved, STDOUT_FILENO);
	close (saved);
	return (err);
}
/**
* entry point of the execution part of the program.
* takes an exec_list and the environment and executes it.
*/
pid_t	exec_pipeline(t_list **exec_lst, t_env_lst *env)
{
	t_list		*current;
	pid_t		pid;
	int			next_pipe_entry;

	next_pipe_entry = 0;
	current = *exec_lst;
	while (current)
	{
		pid = dup_and_fork(exec_lst, &current, env, &next_pipe_entry);
		current = current->next;
	}
	return (pid);
}
