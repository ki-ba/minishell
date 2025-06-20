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
	if (err == 0 && status > 0)
		err = status / 256;
	while (wait(&status) > -1)
		;
	if (status == 2) //! not working
		err = 130;
	return (err);
}

int	interpret_line(char cmd[], t_env_lst *env_lst)
{
	t_list	*tokens;
	char	*expanded;
	t_list	*exec_lst;
	pid_t	pid;
	int		err;

	err = 0;
	tokens = NULL;
	if (check_meta_validity(cmd))
		return (ERR_PARSING);
	expanded = expand_line(env_lst, cmd);
	if (!expanded)
		return (ERR_ALLOC);
	if (check_quotes(expanded))
		return (ERR_PARSING);
	if (tokenize(&tokens, expanded) != 0)
	{
		free(expanded);
		return (ERR_ALLOC);
	}
	free(expanded);
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
	//TODO: another function for stuff bellow to get the right err
	// 		(either parsing/alloc from above, or from the exec after)
	pid = exec_pipeline(&exec_lst, env_lst);
	err = wait_processes(pid, err);
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
	init_signals(env_lst);
	qm_var = search_env_var(env_lst, "?");
	while (error != ERR_ALLOC) // if error occured, quit program
	{
		if (error > -1)
			qm_var->value = ft_itoa(error);
		cmd = readline("zinzinshell $");
		if (cmd && cmd[0])
		{
			ft_add_history(hist_fd, cmd, last_cmd);
			error = interpret_line(cmd, env_lst);
			if (last_cmd)
				free(last_cmd);
			last_cmd = cmd;
			if (error == ERR_PARSING)
				print_error_msg(error);
		}
		if (!cmd)
		{
			printf("exit\n");
			break ;
		}
	}
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
	return (exit_status);
}
