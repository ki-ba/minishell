/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:59:34 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/01 17:11:23 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "exec.h"
#include "error.h"
#include "parsing.h"
#include "minishell.h"
#include "env.h"
#include "lexing.h"
#include "builtins.h"
#include "signals.h"
#include <sys/wait.h>

static int	wait_processes(pid_t pid, int err)
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

static int	start_execution(t_minishell *ms)
{
	t_exec_node	*node;
	t_list		*exec_lst;

	node = (t_exec_node *) ms->exec_lst->content;
	exec_lst = ms->exec_lst;
	if (ft_strlen(node->cmd[0]) == 0)
		update_qm(&ms->error, 0, 0);
	if (!exec_lst->next && node->cmd[0] && !ft_strncmp(node->cmd[0], "exit", 5))
		ms->is_exit = is_correct_exit(node->cmd);
	if (!exec_lst->next && is_builtin(node->cmd))
		update_qm(&ms->error, exec_unique_cmd(ms, &exec_lst), 1);
	else
	{
		update_signals(1);
		update_qm(&ms->error, wait_processes(exec_pipeline(ms), ms->error), 0);
	}
	return (ms->error);
}

int	interpret_line(t_minishell *ms, char *cmd)
{
	t_list		*tokens;

	update_qm(&ms->error, 0, 1);
	tokens = NULL;
	if (tokenize(&tokens, cmd) != 0)
		return (ERR_ALLOC);
	free(cmd);
	if (process_tokens(tokens))
		return (ERR_PARSING);
	ms->error = parse_tokens(ms, tokens);
	ft_lstclear(&tokens, deltoken);
	if (ms->error == ERR_ALLOC || !(ms->exec_lst))
	{
		if (ms->exec_lst)
			ft_lstclear(&ms->exec_lst, del_exec_node);
		return (ERR_ALLOC);
	}
	if (g_signal == 2)
		ms->error = 130;
	else
		ms->error = start_execution(ms);
	if (ms->exec_lst)
		ft_lstclear(&ms->exec_lst, del_exec_node);
	return (ms->error);
}
