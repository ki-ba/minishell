#include "minishell.h"

void	print_error_msg(int status)
{
	if (status == ERR_ARGS)
		ft_putstr_fd("ERROR : incorrect arguments\n", 2);
	if (status == ERR_PARSING)
		ft_putstr_fd("ERROR : parsing failed\n", 2);
	if (status == ERR_ALLOC)
		ft_putstr_fd("ERROR : memory allocation failed\n", 2);
	if (status == ERR_FAIL)
		ft_putstr_fd("ERROR : unspecified issue\n", 2);
}

int	wait_processes(pid_t pid, int err)
{
	int	status;

	status = 0;
	if (pid == -1)
		return (-1);
	if (pid > 0)
		waitpid(pid, &status, 0);
	if (WIFSIGNALED(status) || g_signal != 0)
	{
		if (WIFSIGNALED(status))
			err = WTERMSIG(status) + 128;
		else
			err = g_signal + 128;
		if (err == 131)
			printf("(core dumped)");
		printf("\n");
	}
	if (err == 0 && status > 0)
		err = status / 256;
	while (wait(&status) > -1)
		;
	return (err);
}

char	*trim_cmd(char *cmd)
{
	char	*trim;

	trim = ft_strtrim(cmd, " \t\n\r\v\f");
	free(cmd);
	if (!trim)
		return (NULL);
	if (trim[0] && (trim[0] == '|' || trim[ft_strlen(trim) - 1] == '|'))
	{
		free(trim);
		return (NULL);
	}
	if (trim[0] && (trim[ft_strlen(trim) - 1] == '<' || trim[ft_strlen(trim) - 1] == '>'))
	{
		free(trim);
		return (NULL);
	}
	return (trim);
}

char	*format_cmd(t_env_lst *env, char *cmd)
{
	char	*expanded;

	if (check_meta_validity(cmd))
		return (NULL);
	expanded = expand_line(env, cmd);
	free(cmd);
	expanded = trim_cmd(expanded);
	if (check_parsing(expanded))
		return (NULL);
	return (expanded);
}

int	start_execution(t_list *exec, t_env_lst *env, t_bool *is_exit)
{
	t_exec_node	*node;
	t_env_lst	*qm;

	qm = search_env_var(env, "?");
	node = (t_exec_node *) exec->content;
	if (ft_strlen(node->cmd[0]) == 0)
	{
		update_qm(env, 0, 0);
		return (0);
	}
	if (!exec->next && node->cmd[0] && !ft_strncmp(node->cmd[0], "exit", 5))
		*is_exit = is_correct_exit(node->cmd);
	if (!exec->next && is_builtin(node->cmd))
		update_qm(env, exec_unique_cmd(&exec, env), 1);
	else
		update_qm(env, wait_processes(exec_pipeline(&exec, env), 0), 0);
	return (ft_atoi(qm->value));
}
