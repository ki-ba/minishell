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

#include "data_structures.h"
#include "libft.h"
#include "minishell.h"
#include "error.h"
#include "env.h"
#include "history.h"
#include "exec.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>

void			del_exec_node(void *node);
static void	print_error_msg(int status)
{
	if (status == ERR_ARGS)
		ft_putstr_fd("ERROR : incorrect arguments\n", 2);
	if (status == ERR_PARSING)
		ft_putstr_fd("ERROR : wrong syntax\n", 2);
	if (status == ERR_ALLOC)
		ft_putstr_fd("ERROR : memory allocation failed\n", 2);
}

int	handle_line(t_minishell *ms, char cmd[])
{
	char	*formatted;

	if (cmd[0])
	{
		formatted = format_cmd(ms->env, cmd);
		if (ft_add_history(ms, cmd) || !formatted)
			return (ERR_ALLOC);
		if (!ft_strncmp(cmd, "\0", 1))
			return (0);
		ms->error = interpret_line(ms, formatted);
		if (ms->error > 300)
		{
			print_error_msg(ms->error);
			ms->error -= 300;
		}
		return (0);
	}
	return (1);
}

int	readline_loop(t_minishell *ms_data)
{
	char		*cmd;
	int			error;
	t_bool		is_exit;

	error = 0;
	is_exit = FALSE;
	g_signal = 0;
	while (error != ERR_ALLOC && !is_exit)
	{
		ft_lstclear(&ms_data->exec_lst, del_exec_node);
		cmd = NULL;
		init_signals();
		cmd = readline("zinzinshell$ ");
		if (!cmd)
			break ;
		handle_line(ms_data, cmd);
		free(cmd);
	}
	return (error);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms_data;
	int			exit_status;

	ms_data.last_cmd = NULL;
	ms_data.env = NULL;
	ms_data.exec_lst = NULL;
	if (!DEBUG && (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || argc > 1))
	{
		ft_putstr_fd("error : zinzinshell neither support arguments,", 2);
		ft_putstr_fd("nor piping/redirecting its input / output.\n", 2);
		exit(1);
	}
	exit_status = 1;
	(void)argc;
	(void)argv;
	create_environment(&ms_data.env, envp);
	if (ms_data.env)
		exit_status = readline_loop(&ms_data);
	if (exit_status)
		print_error_msg(exit_status);
	destroy_env_lst(ms_data.env);
	printf("exit\n");
	return (exit_status);
}
