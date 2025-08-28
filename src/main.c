/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:16:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/27 15:42:33 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "libft.h"
#include "minishell.h"
#include "error.h"
#include "env.h"
#include "history.h"
#include "exec.h"
#include "parsing.h"
#include "signals.h"
#include <readline/readline.h>
#include <readline/history.h>
#include "prompt.h"
#include "color.h"
#include <errno.h>

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
	int		err;

	if (g_signal == 2)
		ms->error = 130;
	if (cmd[0])
	{
		if (ft_add_history(ms, cmd))
			return (ERR_ALLOC);
		formatted = format_cmd(ms, cmd);
		if (!formatted)
			return (ERR_PARSING);
		if (!ft_strncmp(formatted, "\0", 1))
			return (ms->error);
		ms->error = interpret_line(ms, formatted);
		if (ms->error > 300)
		{
			print_error_msg(ms->error);
			ms->error -= 300;
		}
		return (ms->error);
	}
	return (ms->error);
}


int	handle_error(int error)
{
	if (error > 300)
	{
		print_error_msg(error);
		return (error - 300);
	}
	return (error);
}

int	readline_loop(t_minishell *ms_data)
{
	char		*cmd;
	char		*prompt;

	g_signal = 0;
	while (ms_data->error != ERR_ALLOC && !(ms_data->is_exit))
	{
		ft_lstclear(&ms_data->exec_lst, del_exec_node);
		prompt = create_prompt(ms_data);
		if (!prompt)
			return (ERR_ALLOC);
		init_signals();
		cmd = readline(prompt);
		free(prompt);
		if (!cmd)
			break ;
		ms_data->error = handle_line(ms_data, cmd);
		if (ms_data->error > 300)
		{
			print_error_msg(ms_data->error);
			ms_data->error -= 300;
		}
		if (ms_data->error && !(ms_data->is_exit))
			printf("[%s%d%s]  ", FG_RED, ms_data->error, RESET);
		else if (!(ms_data->error) && !(ms_data->is_exit))
			printf("[%s%d%s]  ", FG_GREEN, ms_data->error, RESET);
	}
	return (ms_data->error);
}

void	init_ms(t_minishell *ms)
{
	ms->interface = 0;
	ms->last_cmd = NULL;
	ms->error = 0;
	ms->env = NULL;
	ms->cur_wd = NULL;
	ms->exec_lst = NULL;
	ms->is_exit = 0;
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms_data;
	int			exit_status;

	init_ms(&ms_data);
	if (!DEBUG && (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || argc > 1))
	{
		ft_putstr_fd("error : zinzinshell neither support arguments,", 2);
		ft_putstr_fd("nor piping/redirecting its input / output.\n", 2);
		exit(1);
	}
	exit_status = 1;
	(void)argv;
	create_environment(&ms_data, envp);
	if (ms_data.env)
	{
		printf("[%s0%s]  ", FG_GREEN, RESET);
		exit_status = readline_loop(&ms_data);
	}
	if (exit_status > 300)
		exit_status -= 300;
	if (exit_status)
		print_error_msg(exit_status);
	destroy_env_lst(&ms_data.env);
	printf("exit\n");
	return (exit_status);
}
