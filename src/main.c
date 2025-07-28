#include "minishell.h"
#include <errno.h>

int	process_tokens(t_list *tokens)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	if (!tokens->next)
	{
		if (token->type == TOKEN_PIPE || token->type == TOKEN_REDIRECT)
			return (ERR_PARSING);
	}
	ft_lstiter(tokens, remove_quotes);
	return (0);
}



int	interpret_line(char *cmd, t_env_lst *env_lst, t_bool *is_exit)
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
		return (tokenize(&tokens, cmd));
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

int	handle_line(t_env_lst *env, char cmd[], t_bool *is_exit, int *error)
{
	char	*tmp;

	if (cmd[0])
	{
		ft_add_history(cmd);
		tmp = ft_strtrim(cmd, " \t\n\r\v\f");
		cmd = ft_strdup(tmp);
		free(tmp);
		*error = interpret_line(cmd, env, is_exit);
		if (*error > 300)
		{
			print_error_msg(*error);
			*error -= 300;
		}
		return (0);
	}
	else
		return (1);
}

int	readline_loop(t_env_lst *env_lst)
{
	char		*cmd;
	int			error;
	t_bool		is_exit;

	error = 0;
	is_exit = FALSE;
	g_signal = 0;
	while (error != ERR_ALLOC && !is_exit)
	{
		init_signals();
		errno = 0;
		cmd = readline("zinzinshell$ ");
		if (errno != 0)
			;
		if (cmd && (handle_line(env_lst, cmd, &is_exit, &error) || 1))
			continue ;
		else if (g_signal == 2)
			error = 130;
		break ;
		g_signal = 0;
	}
	ft_add_history(NULL);
	return (error);
}

// TODO uncomment isatty part before submitting project
int	main(int argc, char *argv[], char *envp[])
{
	t_env_lst	*env_lst;
	int			exit_status;

	// if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || argc > 1)
	// {
	// 	if (!isatty(STDIN_FILENO))
	// 		ft_putstr_fd("error : funny business detected\n", 2);
	// 	exit(1);
	// }
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
