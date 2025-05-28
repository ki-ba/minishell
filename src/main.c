#include "libft.h"
#include "error.h"
#include "minishell.h"
#include "builtins.h"
#include "exec.h"

int	interpret_line(char cmd[], t_env_lst *env_lst)
{
	t_list	*tokens;
	char	*expanded;
	t_list	*exec_lst;
	int		err;

	tokens = NULL;
	expanded = expand_line(env_lst, cmd);
	tokenize(&tokens, expanded);
	free(expanded);
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
	err = builtins_call(exec_lst->content, env_lst);
	ft_lstclear(&exec_lst, del_exec_node);
	if (!ft_strncmp(cmd, "exit", ft_strlen("exit")))
	{
		ft_printf("exiting\n");
		exit(EXIT_SUCCESS);
	}
	return (err);
}

int	readline_loop(t_env_lst *env_lst)
{
	char	*cmd;
	int		hist_fd;
	char	*last_cmd;
	int		status;

	status = 0;
	last_cmd = NULL;
	cmd = NULL;
	hist_fd = retrieve_history(&last_cmd);
	while (!status) // if error occured, quit program
	{
		cmd = readline("zinzinshell $");
		builtins_call(cmd, env_lst);
		if (cmd && cmd[0])
		{
			ft_add_history(hist_fd, cmd, last_cmd);
			status = interpret_line(cmd, env_lst);
			if (last_cmd)
				free(last_cmd);
			last_cmd = cmd;
		}
	}
	close(hist_fd);
	return (status);
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
	destroy_env_lst(env_lst);
	return (exit_status);
}
