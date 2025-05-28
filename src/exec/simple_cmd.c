#include "minishell.h"
#include "error.h"
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
	int		pipefd[2];
	char	**env_arr;

	(void) env;
	if (pipe(pipefd) == -1)
	{
		perror("minishell: pipe");
		return (ERR_FAIL);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (ERR_FAIL);
	}
	if (pid == 0)
	{
		env_arr = envlist_to_arr(env);
		close(pipefd[1]);
		ft_putstr_fd("child: [", 1);
		dup2(pipefd[0], exe->io[0]);
		if (execve("/usr/bin/echo", exe->cmd, env_arr) == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			perror(exe->cmd[0]);
			return (ERR_FAIL);
		}
		ft_putstr_fd("]\n", 1);
		ft_free_arr(env_arr);
		close(pipefd[0]);
	}
	else
	{
		close(pipefd[0]);
		dup2(pipefd[1], exe->io[1]);
		close(pipefd[1]);
		wait(NULL);
	}

	return(0);
}
