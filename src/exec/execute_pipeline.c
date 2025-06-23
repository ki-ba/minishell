#include "minishell.h"

int	try_exec(char **cmd, t_env_lst *env)
{
	char	*path;
	char	**env_arr;

	if (is_builtin(cmd))
		return (call_cmd(cmd, env));
	env_arr = envlist_to_arr(env);
	if (ft_strnstr(cmd[0], "/", ft_strlen(cmd[0])))
		path = ft_strdup(cmd[0]);
	else
		path = find_path(cmd[0], env);
	if (!path)
		return (ERR_ALLOC);
	execve(path, cmd, env_arr);
	ft_free_arr(env_arr);
	free(path);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd[0]);
	exit(127);
}
#include <signal.h>
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
		close(exe->io[0]);
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

	if (pipe(pipe_fd) < 0)
		return (-1);
	pid = fork();
	(void)exec_list;
	if (pid == 0)
		exec_child(current, env, next_pipe_entry, pipe_fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		if (*next_pipe_entry)
			close(*next_pipe_entry);
		*next_pipe_entry = pipe_fd[0];
		exe = (t_exec_node *)(*current)->content;
		if (exe->io[0] != STDIN_FILENO)
			close(exe->io[0]);
		if (exe->io[1] != STDOUT_FILENO)
			close(exe->io[1]);
	}
	if (!(*current)->next)
		close(pipe_fd[0]);
	close(pipe_fd[1]);
	return (pid);
}

/**
* entry point of the execution part of the program.
* takes an exec_list and the environment and executes it.
*/
pid_t	exec_pipeline(t_list **exec_lst, t_env_lst *env)
{
	t_list	*current;
	pid_t	pid;
	int		next_pipe_entry;
	t_exec_node	*exe;

	next_pipe_entry = 0;
	current = *exec_lst;
	exe = (t_exec_node *)(*exec_lst)->content;
	if (!current->next && is_builtin(exe->cmd))
	{
		call_cmd(exe->cmd, env);
		return (-1);
	}
	while (current)
	{
		pid = dup_and_fork(exec_lst, &current, env, &next_pipe_entry);
		current = current->next;
	}
	return (pid);
}
