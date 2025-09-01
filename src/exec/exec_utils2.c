/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 14:52:56 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/01 14:53:16 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	sclose(int fd)
{
	if (fd >= 0 && fd <= 2)
		return (1);
	else
		return (close(fd));
}

int	apply_redirections(t_list **cur_node)
{
	t_exec_node	*exe;
	int			err;

	err = 0;
	exe = (t_exec_node *)(*cur_node)->content;
	if (exe->io[1] != STDOUT_FILENO)
		err = dup2(exe->io[1], STDOUT_FILENO);
	if (err >= 0 && exe->io[0] != STDIN_FILENO)
		err = dup2(exe->io[0], STDIN_FILENO);
	sclose (exe->io[0]);
	sclose (exe->io[1]);
	return (err);
}
