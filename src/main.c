#include "builtins.h"
#include "data_structures.h"
#include <errno.h>
#include "error.h"
#include "libft.h"
#include "minishell.h"

void	print_error_msg(int status)
{
	if (status == ERR_ARGS)
		ft_putstr_fd("ERROR : incorrect arguments\n", 2);
	if (status == ERR_PARSING)
		ft_putstr_fd("ERROR : wrong syntax\n", 2);
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

char	*trim_cmd(char *cmd)
{
	char	*trim;
	size_t	len;

	trim = ft_strtrim(cmd, " \t\n\r\v\f");
	len = ft_strlen(trim);
	free(cmd);
	if (!trim)
		return (NULL);
	if (trim[0] && (trim[0] == '|' || trim[len - 1] == '|'))
	{
		free(trim);
		return (NULL);
	}
	if (trim[0] && (trim[len - 1] == '<' || trim[len - 1] == '>'))
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

int	process_tokens(t_list *tokens)
{
	t_token	*token;

	token = (t_token *) tokens->content;
	if (!tokens->next
		&& (token->type == TOKEN_PIPE || token->type == TOKEN_REDIRECT))
		return (ERR_PARSING);
	ft_lstiter(tokens, remove_quotes);
	return (0);
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
		update_qm(env, wait_processes(exec_pipeline(&exec, &env), 0), 0);
	if (node->io[0] == -1 && !node->filename[1])
		ft_putendl_fd("minishell: no such file", 2);
	return (ft_atoi(qm->value));
}

int	interpret_line(char *cmd, t_env_lst *env_lst, t_bool *is_exit)
{
	t_list		*tokens;
	t_list		*exec_lst;
	int			err;

	update_qm(env_lst, 0, 1);
	tokens = NULL;
	cmd = format_cmd(env_lst, cmd);
	if (!cmd)
		return (SUCCESS);
	if (tokenize(&tokens, cmd) != 0)
		return (tokenize(&tokens, cmd));
	free(cmd);
	if (process_tokens(tokens))
		return (ERR_PARSING);
	exec_lst = parse_tokens(tokens);
	ft_lstclear(&tokens, deltoken);
	if (!exec_lst)
		return (ERR_ALLOC);
	if (g_signal == 2)
		err = 130;
	else
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
			return (ERR_ALLOC);
		if (cmd && (handle_line(env_lst, cmd, &is_exit, &error) || 1))
			continue ;
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
