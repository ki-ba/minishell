#include "libft.h"
#include "minishell.h"

int	interpret_line(char cmd[], t_env_lst *env_lst)
{
	t_list	*tokens;
	char	*expanded;
	t_list	*exec_lst;

	tokens = NULL;
	expanded = expand_line(env_lst, cmd);
	tokenize(&tokens, expanded);
	print_token_list(tokens);
	ft_printf("%s\n", expanded);
	exec_lst = parse_tokens(tokens);
	print_exec(exec_lst);
	free(expanded);
	ft_lstclear(&tokens, deltoken);
	ft_lstclear(&exec_lst, del_exec_node);
	return (0);
}

int	readline_loop(t_env_lst *env_lst)
{
	char	*cmd;
	int		hist_fd;
	char	*last_cmd;
	int		status;

	last_cmd = NULL;
	cmd = NULL;
	hist_fd = retrieve_history(&last_cmd);
	while (TRUE && (!cmd || strncmp(cmd, "exit", ft_strlen(cmd))))
	{
		cmd = readline("zinzinshell $");
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

	env_lst = create_environment(&env_lst, envp);
	exit_status = readline_loop(env_lst);
	destroy_env_lst(env_lst);
	return (exit_status);
}
