#include "minishell.h"
#include "error.h"
#include "exec.h"
#include <unistd.h>
#include <sys/wait.h>

size_t	envlist_len(t_env_lst *env)
{
	size_t		i = 1;
	t_env_lst	*tmp;

	tmp = env;
	while (tmp->next)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

char	**envlist_to_arr(t_env_lst *env_lst)
{
	char		**env;
	t_env_lst	*tmp;
	size_t		i;
	size_t		len;

	tmp = env_lst;
	env = ft_calloc(envlist_len(env_lst), sizeof(char *));
	i = 0;
	while(tmp->next)
	{
		len = ft_strlen(tmp->name);
		len += ft_strlen(tmp->value);
		env[i] = ft_calloc(len + 2, sizeof(char));
		// ft_strncpy(env[i], tmp->name, ft_strlen(tmp->name));
		env[i] = ft_concat(3, tmp->name, "=", tmp->value);
		tmp = tmp->next;
		i++;
	}
	return (env);
}

int	simple_cmd(t_exec_node *exe, t_env_lst *env)
{
	int		pid;
	char	**env_arr;
	char	*path;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (ERR_FAIL);
	}
	env_arr = envlist_to_arr(env);
	if (pid == 0)
	{
		dup2(STDOUT_FILENO, exe->io[0]);
		path = find_path(exe->cmd[0], env);
		if (!path)
		{
			return (ERR_ALLOC);
		}
		if (execve(path, exe->cmd, env_arr) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(exe->cmd[0]);
			return (ERR_FAIL);
		}
	}
	else
	{
		dup2(STDIN_FILENO, exe->io[1]);
		waitpid(pid, NULL, 0);
		ft_free_arr(env_arr);
	}
	return(0);
}
