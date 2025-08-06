/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:01:26 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/06 18:03:21 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error.h"
#include "env.h"
#include "history.h"
#include "exec.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

static void	print_error_msg(int status)
{
	if (status == ERR_ARGS)
		ft_putstr_fd("ERROR : incorrect arguments\n", 2);
	if (status == ERR_PARSING)
		ft_putstr_fd("ERROR : wrong syntax\n", 2);
	if (status == ERR_ALLOC)
		ft_putstr_fd("ERROR : memory allocation failed\n", 2);
}

int	handle_line(ms_data, char cmd[], int *error)
{
	if (cmd[0])
	{
		if (ft_add_history(cmd) || !format_cmd(env, cmd))
			return (ERR_ALLOC);
		if (!ft_strncmp(cmd, "\0", 1))
		{
			free (cmd);
			return (0);
		}
		*error = interpret_line(cmd, env, is_exit);
		if (*error > 300)
		{
			print_error_msg(*error);
			*error -= 300;
		}
		return (0);
	}
	free(cmd);
	return (1);
}

int	readline_loop(t_minishell *ms_data, t_env_lst *env_lst)
{
	char		*cmd;
	int			error;
	t_bool		is_exit;

	error = 0;
	is_exit = FALSE;
	g_signal = 0;
	while (error != ERR_ALLOC && !is_exit)
	{
		cmd = NULL;
		init_signals();
		cmd = readline("zinzinshell$ ");
		if (cmd && (handle_line(ms_data, cmd, &error) || 1))
			continue ;
		break ;
	}
	ft_add_history(NULL);
	return (error);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env_lst	*env_lst;
	t_minishell	ms_data;
	int			exit_status;

	ms_data.last_cmd = NULL;
	if (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || argc > 1)
	{
		if (!isatty(STDIN_FILENO))
			ft_putstr_fd("error : funny business detected\n", 2);
		exit(1);
	}
	exit_status = 1;
	(void)argv;
	env_lst = create_environment(&env_lst, envp);
	if (env_lst)
		exit_status = readline_loop(&minishell_data, env_lst);
	if (exit_status)
		print_error_msg(exit_status);
	destroy_env_lst(env_lst);
	printf("exit\n");
	return (exit_status);
}
