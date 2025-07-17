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

int	check_parsing(char str[])
{
	if (!str || !ft_strncmp(str, "\0", 1) || check_quotes(str))
	{
		free (str);
		return (1);
	}
	return (0);
}

char	*trim_cmd(char cmd[])
{
	char	*trim;

	trim = ft_strtrim(cmd, " \t\n\r\v");
	if (trim[0] == '|' || trim[ft_strlen(trim) - 1] == '|')
		return (NULL);
	if (trim[ft_strlen(trim) - 1] == '<' || trim[ft_strlen(trim) - 1] == '>')
		return (NULL);
	return (trim);
}

char	*format_cmd(t_env_lst *env, char cmd[])
{
	char	*expanded;

	if (check_meta_validity(cmd))
		return (NULL);
	cmd = trim_cmd(cmd);
	expanded = expand_line(env, cmd);
	free(cmd);
	if (check_parsing(expanded))
		return (NULL);
	return (expanded);
}

int	process_tokens(t_list *tokens)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	if (!tokens->next && (token->type == TOKEN_PIPE || token->type == TOKEN_REDIRECT))
		return (ERR_PARSING);
	ft_lstiter(tokens, remove_quotes);
	return (0);
}

int	start_execution(t_list *exec, t_env_lst *env, t_bool *is_exit)
{
	t_exec_node	*node;

	node = (t_exec_node *) exec->content;
	if (!exec->next && node->cmd[0] && !ft_strncmp(node->cmd[0], "exit", 5))
		*is_exit = 1;
	if (!exec->next && is_builtin(node->cmd))
		return (exec_unique_cmd(&exec, env));
	else
		return (wait_processes(exec_pipeline(&exec, env), 0));
}

int	interpret_line(char cmd[], t_env_lst *env_lst, t_bool *is_exit)
{
	t_list		*tokens;
	t_list		*exec_lst;
	int			err;
	t_env_lst	*qm;

	qm = search_env_var(env_lst, "?");
	if (g_signal == 2)
	{
		qm->value = ft_itoa(130);
		g_signal = 0;
	}
	tokens = NULL;
	cmd = format_cmd(env_lst, cmd);
	if (tokenize(&tokens, cmd) != 0)
		return (ERR_ALLOC);
	free(cmd);
	if (process_tokens(tokens))
		return (ERR_PARSING);
	exec_lst = parse_tokens(tokens);
	ft_lstclear(&tokens, deltoken);
	if (!exec_lst)
		return (ERR_ALLOC);
	err = start_execution(exec_lst, env_lst, is_exit);
	ft_lstclear(&exec_lst, del_exec_node);
	return (err);
}

// start_interpreter(t_env_lst *env)
// {
//
// }
int	readline_loop(t_env_lst *env_lst)
{
	char		*cmd;
	int			hist_fd;
	char		*last_cmd;
	int			error;
	t_bool		is_exit;
	t_env_lst	*qm_var;

	error = 0;
	last_cmd = NULL;
	hist_fd = retrieve_history(env_lst, &last_cmd);
	qm_var = search_env_var(env_lst, "?");
	is_exit = FALSE;
	while (error != ERR_ALLOC && !is_exit)
	{
		g_signal = 0;
		init_signals();
		if (error > -1)
		{
			free(qm_var->value);
			qm_var->value = ft_itoa(error);
		}
		else
			error = ft_atoi(qm_var->value);
		cmd = readline("zinzinshell$ ");
		if (cmd && cmd[0])
		{
			ft_add_history(hist_fd, cmd, last_cmd);
			error = interpret_line(cmd, env_lst, &is_exit);
			last_cmd = cmd;
			if (error == ERR_PARSING)
				print_error_msg(error);
		}
		if (!cmd)
		{
			if (g_signal == 2)
				error = 130;
			break ;
		}
	}
	if (is_exit)
		error = ft_atoi(qm_var->value);
	close(hist_fd);
	return (error);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_lst	*env_lst;
	int			exit_status;

	exit_status = 1;
	(void)argc;
	(void)argv;
	env_lst = create_environment(&env_lst, envp);
	if (env_lst)
		exit_status = readline_loop(env_lst);
	if (exit_status)
		print_error_msg(exit_status);
	destroy_env_lst(env_lst);
	printf("exit\n");
	return (exit_status);
}
