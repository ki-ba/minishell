#include "builtins.h"
#include "libft.h"
#include "minishell.h"
#include <signal.h>
#include <sys/stat.h>
#include <sys/types.h>

static char	*path_to_cmd(char *cmd[], t_env_lst *env)
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
	else if (S_ISDIR(fi.st_mode))
		err = 126;
	else if (access(path, X_OK))
		err = 126;
	else
		err = 0;
	return (err);
}

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
		if (path && env_arr)
			execve(path, cmd, env_arr);
		ft_free_arr(env_arr);
		free(path);
		ft_printf_fd(2, "minishell: %s: command not found\n", cmd[0]);
	}
	destroy_env_lst(env);
	// ft_lstclear(exec, del_exec_node);
	ft_lstdelone(*exec, del_exec_node);
	exec = NULL;
	ft_free_arr(cmd);
	exit(err);
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

void	exec_child(t_list **cur, t_env_lst *env, int *next_pipe, int pipe[2])
{
	t_exec_node	*exe;
	char		**cmd;

	signal(SIGQUIT, SIG_DFL);
	exe = (t_exec_node *)(*cur)->content;
	set_child_io(cur, exe, next_pipe, pipe);
	cmd = duplicate_arr(exe->cmd);
	try_exec(cur, cmd, env);
}

void	ft_lstclear_but(t_list **lst, void (*f)(void *), t_list *item)
{
	t_list	*cur;
	t_list	*next;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		if (cur != item)
		{
			f(cur->content);
			cur->next = NULL;
			free(cur);
		}
		cur = next;
	}
	*lst = item;
}

/** creates a separate process for each command, 
 * creating pipes when necessary.*/
pid_t	dup_and_fork(t_list **exec, t_list **cur, t_env_lst *env, int *nxt_pip)
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
			exit(1);
		ft_lstclear_but(exec, del_exec_node, *cur);
		exec_child(cur, env, nxt_pip, pipe_fd);
		// ft_lstclear(exec, del_exec_node);
	}
	else
	{
		update_signals(1);
		if (*nxt_pip > 0)
			close(*nxt_pip);
		*nxt_pip = pipe_fd[0];
		if (exe->io[0] != STDIN_FILENO && exe->io[0] > 0)
			close(exe->io[0]);
		if (exe->io[1] != STDOUT_FILENO && exe->io[1] > 0)
			close(exe->io[1]);
	// }
		if (!(*cur)->next && pipe_fd[0] > 0)
			close(pipe_fd[0]);
		if (pipe_fd[1] > 0)
			close(pipe_fd[1]);
	} /*this one*/
	return (pid);
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
