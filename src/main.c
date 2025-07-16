#include "data_structures.h"
#include "minishell.h"
#include "exec.h"

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

int	interpret_line(char cmd[], t_env_lst *env_lst, t_bool *is_exit)
{
	t_list	*tokens;
	char	*expanded;
	char	*trim;
	t_list	*exec_lst;
	pid_t	pid;
	int		err;
	t_env_lst	*qm;

	err = 0;
	qm = search_env_var(env_lst, "?");
	if (g_signal == 2)
	{
		qm->value = ft_itoa(130);
		g_signal = 0;
	}
	tokens = NULL;
	if (check_meta_validity(cmd))
		return (ERR_PARSING);
	//? new trim
	trim = ft_strtrim(cmd, " \t\n\r\v");
	if (trim[0] == '|' || 
		trim[ft_strlen(trim) - 1] == '|' || trim[ft_strlen(trim) - 1] == '<'  || trim[ft_strlen(trim) - 1] == '>')
	{
		free(trim);
		// free(cmd);
		return (ERR_PARSING);
	}
	//? endtrim
	expanded = expand_line(env_lst, trim);
	free(trim);
	if (!expanded)
		return (ERR_ALLOC);
	// to_trim = expanded;
	// expanded = ft_strtrim(to_trim, " \t\n\r\v");
	// free(to_trim);
	// printf("exp= [%s] len-1[%c]\n", expanded, expanded[ft_strlen(expanded) - 1]);
	// if (expanded[0] == '|' || 
	// 	expanded[ft_strlen(expanded) - 1] == '|' || expanded[ft_strlen(expanded) - 1] == '<'  || expanded[ft_strlen(expanded) - 1] == '>')
	// {
	// 	free(expanded);
	// 	return (ERR_PARSING);
	// }
	if (!ft_strncmp(expanded, "\0", 1))
	{
		free (expanded);
		return (ft_atoi(qm->value));
	}
	if (check_quotes(expanded))
	{
		free(expanded);
		return (ERR_PARSING);
	}
	if (tokenize(&tokens, expanded) != 0)
	{
		free(expanded);
		return (ERR_ALLOC);
	}
	free(expanded);
	t_token	*token = (t_token*) tokens->content;
	if (!tokens->next && (token->type == TOKEN_PIPE || token->type == TOKEN_REDIRECT))
		return (ERR_PARSING);
	ft_lstiter(tokens, remove_quotes);
	if (DEBUG)
		print_token_list(tokens);
	if (!tokens)
		return (ERR_ALLOC);
	exec_lst = parse_tokens(tokens);
	ft_lstclear(&tokens, deltoken);
	if (!exec_lst)
		return (ERR_ALLOC);
	if (DEBUG)
		print_exec(exec_lst);
	//exit
	t_exec_node	*node;
	node = (t_exec_node *) exec_lst->content;
	if (!exec_lst->next && node->cmd[0] && !ft_strncmp(node->cmd[0], "exit", 5))
		*is_exit = 1;
	if (!exec_lst->next && is_builtin(node->cmd))
		err = exec_unique_cmd(&exec_lst, env_lst);
	else // if there is more than 1 command
	{
		pid = exec_pipeline(&exec_lst, env_lst);
		err = wait_processes(pid, err);
	}
	//TODO: another function for stuff bellow to get the right err
	// 		(either parsing/alloc from above, or from the exec after)
	ft_lstclear(&exec_lst, del_exec_node);
	return (err);
}

#include <errno.h>
int	readline_loop(t_env_lst *env_lst)
{
	char	*cmd;
	int		hist_fd;
	char	*last_cmd;
	int		error;
	char	*hist_fd_str;
	t_env_lst	*qm_var;

	error = 0;
	last_cmd = NULL;
	cmd = NULL;
	hist_fd = retrieve_history(&last_cmd);
	hist_fd_str = ft_itoa(hist_fd);
	add_to_env(env_lst, HIST_FILE, hist_fd_str, 1);
	if (DEBUG)
		print_env(env_lst);
	free(hist_fd_str);
	qm_var = search_env_var(env_lst, "?");
	t_bool is_exit;
	is_exit = FALSE;
	while (error != ERR_ALLOC && !is_exit) // if error occured, quit program
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
			// printf("exit\n");
			break ;
		}
	}
	if (is_exit)
		error = ft_atoi(qm_var->value);
	if (last_cmd)
		free(last_cmd);
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
