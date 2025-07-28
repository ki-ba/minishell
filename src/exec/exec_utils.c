#include "minishell.h"

void	set_io(t_list **exe_ls, t_exec_node *exe, int *nxt_pip, int p[2])
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

void	next_pipe(t_list **cur, t_exec_node *exe, int *nxt_pip, int pipe_fd[2])
{
	if (*nxt_pip > 0)
		close(*nxt_pip);
	*nxt_pip = pipe_fd[0];
	if (exe->io[0] != STDIN_FILENO && exe->io[0] > 0)
		close(exe->io[0]);
	if (exe->io[1] != STDOUT_FILENO && exe->io[1] > 0)
		close(exe->io[1]);
	if (!(*cur)->next && pipe_fd[0] > 0)
		close(pipe_fd[0]);
	if (pipe_fd[1] > 0)
		close(pipe_fd[1]);
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
	else if (S_ISDIR(fi.st_mode))
		err = 126;
	else if (access(path, X_OK))
		err = 126;
	else
		err = 0;
	return (err);
}
