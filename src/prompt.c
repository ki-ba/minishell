/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:00:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/27 15:24:31 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "color.h"
#include <linux/limits.h>
#include "signals.h"

char	*part_one(void)
{
	char	*prompt;

	prompt = ft_concat(4, BG_BLUE, "zzsh", RESET, " ");
	return (prompt);
}

char	*def_cwd(t_minishell *ms_data)
{
	char	*prompt;

	prompt = ft_concat(5, BOLD, FG_CYAN, ms_data->cur_wd, RESET, " % ");
	return (prompt);
}

char	*create_prompt(t_minishell *ms_data)
{
	char	*first_part;
	char	*second_part;
	char	*prompt;

	first_part = part_one();
	second_part = def_cwd(ms_data);
	if (!first_part || !second_part)
	{
		free(first_part);
		free(second_part);
		return (NULL);
	}
	prompt = ft_concat(2, first_part, second_part);
	free(first_part);
	free(second_part);
	return (prompt);
}
