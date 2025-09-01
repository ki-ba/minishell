/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:00:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/01 14:29:16 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"
#include <linux/limits.h>
#include "signals.h"
#include "env.h"

static char	*def_cwd(t_minishell *ms_data)
{
	char	*prompt;

	if (!search_env_var(ms_data->env, "TERM"))
		prompt = ft_concat(2, ms_data->cur_wd, " % ");
	else
		prompt = ft_concat(5, BOLD, FG_CYAN, ms_data->cur_wd, RESET, " % ");
	return (prompt);
}

char	*create_prompt(t_minishell *ms_data)
{
	char	*first_part;
	char	*second_part;
	char	*prompt;

	if (!search_env_var(ms_data->env, "TERM"))
		first_part = ft_strdup("zzsh ");
	else
		first_part = ft_concat(4, BG_BLUE, "zzsh", RESET, " ");
	second_part = def_cwd(ms_data);
	if (!first_part || !second_part)
	{
		if (first_part)
			free(first_part);
		if (second_part)
			free(second_part);
		return (NULL);
	}
	prompt = ft_concat(2, first_part, second_part);
	free(first_part);
	free(second_part);
	return (prompt);
}
