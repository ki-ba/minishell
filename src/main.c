/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:16:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/25 13:16:35 by kbarru           ###   ########lyon.fr   */
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
#include "prompt.h"
#include <errno.h>

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

	if (g_signal == 2)
		ms->error = 130;
	if (cmd[0])
	{
		formatted = format_cmd(ms, cmd);
		if (!formatted)
			return (ERR_PARSING);
		if (ft_add_history(ms, formatted))
			return (ERR_ALLOC);
		if (!ft_strncmp(formatted, "\0", 1))
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
	char		*prompt;
	char		*err_str;

	g_signal = 0;
	while (ms_data->error != ERR_ALLOC && !(ms_data->is_exit))
	{
		ft_lstclear(&ms_data->exec_lst, del_exec_node);
		prompt = create_prompt(ms_data);
		if (!prompt)
			return (ERR_ALLOC);
		init_signals();
		errno = 0;
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
		err_str = err_code(ms_data->error);
		if (!err_str)
			return (1);
		ft_printf("%s", err_str);
		free(err_str);
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
	(void)argc;
	(void)argv;
	create_environment(&ms_data.env, envp);
	if (ms_data.env)
	{
		printf("[\033[0;32m0\033[0m]	");
		exit_status = readline_loop(&ms_data);
	}
	if (exit_status)
		print_error_msg(exit_status);
	destroy_env_lst(&ms_data.env);
	printf("exit\n");
	return (exit_status);
}
