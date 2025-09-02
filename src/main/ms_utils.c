/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 10:35:28 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 10:37:40 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "stddef.h"
#include "parsing.h"
#include "env.h"
#include "ms_utils.h"
#include "minishell.h"

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

void	destroy_ms(t_minishell *ms)
{
	sclose(ms->interface);
	free(ms->last_cmd);
	destroy_env_lst(&ms->env);
	free(ms->cur_wd);
}
