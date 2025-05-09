#include "minishell.h"

int	interpret_line(char cmd[], t_env_lst *env_lst)
{
	t_list	*tokens;

	tokens = NULL;
	tokenize(&tokens, cmd);
	print_token_list(tokens);
	(void)cmd;
	(void)env_lst;
	return (0);
}

int	readline_loop(t_env_lst *env_lst)
{
	char	*cmd;
	int		hist_fd;
	char	*last_cmd;
	int		status;

	last_cmd = NULL;
	hist_fd = retrieve_history(&last_cmd);
	while (TRUE)
	{
		cmd = readline("zinzinshell $");
		if (cmd && cmd[0])
		{
			ft_add_history(hist_fd, cmd, last_cmd);
			status = interpret_line(cmd, env_lst);
			free(last_cmd);
			last_cmd = ft_strdup(cmd);
		}
	}
	close(hist_fd);
	return (status);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_lst	*env_lst;
	int			exit_status;

	env_lst = NULL;
	(void)argc;
	(void)argv;
	env_lst = create_environment(&env_lst, envp);
	exit_status = readline_loop(env_lst);
	return (exit_status);
}
