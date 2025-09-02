/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 13:16:33 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 12:30:35 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "ms_utils.h"
#include "minishell.h"
#include "error.h"
#include "env.h"
#include "history.h"
#include "exec.h"
#include "parsing.h"
#include "signals.h"
#include <readline/readline.h>
#include "prompt.h"

/**
* @brief displays the correct error msg according to the error code.
* @brief only works with custom minishell errors (> 300)
* then substracts 300 to have a correct exit status to return.
*/
void	error_handler(t_minishell *ms)
{
	if (ms && ms->error > 300)
	{
		if (ms->error == ERR_ARGS)
			ft_putstr_fd("ERROR : incorrect arguments\n", 2);
		if (ms->error == ERR_PARSING)
			ft_putstr_fd("ERROR : wrong syntax\n", 2);
		if (ms->error == ERR_ALLOC)
		{
			ft_putstr_fd("ERROR : memory allocation failed\n", 2);
			ms->is_exit = TRUE;
		}
		ms->error -= 300;
	}
}

/**
	* @brief adds the line to history, formats it and looks for syntax errors.
	* @brief then sends it for tokenizing / executing.
*/
int	handle_line(t_minishell *ms, char cmd[])
{
	char	*formatted;

	if (g_signal == 2)
		ms->error = 130;
	if (cmd[0])
	{
		if (ft_add_history(ms, cmd))
			return (ERR_FAIL);
		formatted = format_cmd(ms, cmd);
		if (!formatted)
			return (ERR_FAIL);
		if (!ft_strncmp(formatted, "\0", 1))
			return (ms->error);
		ms->error = interpret_line(ms, formatted);
		return (ms->error);
	}
	return (ms->error);
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
		{
			ms_data->error = ERR_ALLOC;
			return (ERR_ALLOC);
		}
		init_signals();
		cmd = readline(prompt);
		if (g_signal == 2 || g_signal == 3)
			ms_data->error = g_signal + 128;
		free(prompt);
		if (!cmd)
			break ;
		handle_line(ms_data, cmd);
		error_handler(ms_data);
	}
	return (ms_data->error);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_minishell	ms_data;

	init_ms(&ms_data);
	if (!DEBUG && (!isatty(STDIN_FILENO) || !isatty(STDOUT_FILENO) || argc > 1))
	{
		ft_putstr_fd("error : no redirecting/piping pls\n", 2);
		exit(1);
	}
	(void)argv;
	create_environment(&ms_data, envp);
	if (ms_data.env)
		readline_loop(&ms_data);
	else
	{
		ft_putstr_fd("error creating environment\n", 2);
		ms_data.error = ERR_ALLOC;
	}
	error_handler(&ms_data);
	destroy_ms(&ms_data);
	printf("exit\n");
	return (ms_data.error);
}
