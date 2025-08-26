/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/21 13:00:55 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/21 14:27:48 by kbarru           ###   ########lyon.fr   */
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

char	*def_cwd(void)
{
	char	*prompt;
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, PATH_MAX);
	prompt = ft_concat(5, BOLD, FG_CYAN, cwd, RESET, " % ");
	free(cwd);
	return (prompt);
}

char	*err_code(int error)
{
	char	*prompt;
	char	color[9];
	char	*err;

	err = ft_itoa(error);
	if (!err)
		return (NULL);
	if (error)
		ft_strlcpy(color, FG_RED, 9);
	else
		ft_strlcpy(color, FG_GREEN, 9);
	prompt = ft_concat(5, "[", color, err, RESET, "]	");
	free(err);
	return (prompt);
}
char	*create_prompt(void)
{
	char	*first_part;
	char	*second_part;
	char	*prompt;

	first_part = part_one();
	second_part = def_cwd();
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
