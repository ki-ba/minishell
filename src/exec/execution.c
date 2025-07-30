/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 13:59:34 by kbarru            #+#    #+#             */
/*   Updated: 2025/07/30 13:59:35 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	wait_processes(pid_t pid, int err)
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

int	start_execution(t_list *exec, t_env_lst *env, t_bool *is_exit)
{
	t_exec_node	*node;
	t_env_lst	*qm;

	qm = search_env_var(env, "?");
	node = (t_exec_node *) exec->content;
	if (ft_strlen(node->cmd[0]) == 0)
		update_qm(env, 0, 0);
	if (!exec->next && node->cmd[0] && !ft_strncmp(node->cmd[0], "exit", 5))
		*is_exit = is_correct_exit(node->cmd);
	if (!exec->next && is_builtin(node->cmd))
		update_qm(env, exec_unique_cmd(&exec, env), 1);
	else
		update_qm(env, wait_processes(exec_pipeline(&exec, &env), 0), 0);
	if (node->io[0] == -1 && !node->filename[1])
		ft_putendl_fd("minishell: no such file", 2);
	return (ft_atoi(qm->value));
}

int	interpret_line(char *cmd, t_env_lst *env_lst, t_bool *is_exit)
{
	t_list		*tokens;
	t_list		*exec_lst;
	int			err;

	update_qm(env_lst, 0, 1);
	tokens = NULL;
	cmd = format_cmd(env_lst, cmd);
	if (!cmd)
		return (SUCCESS);
	if (tokenize(&tokens, cmd) != 0)
		return (tokenize(&tokens, cmd));
	free(cmd);
	if (process_tokens(tokens))
		return (ERR_PARSING);
	exec_lst = parse_tokens(tokens);
	ft_lstclear(&tokens, deltoken);
	if (!exec_lst)
		return (ERR_ALLOC);
	if (g_signal == 2)
		err = 130;
	else
		err = start_execution(exec_lst, env_lst, is_exit);
	ft_lstclear(&exec_lst, del_exec_node);
	return (err);
}
