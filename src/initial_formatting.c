/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_formatting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:12:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/04 16:06:23 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "error.h"
#include "minishell.h"
#include "lexing.h"
#include "parsing.h"

// TODO document this function
char	*trim_cmd(char *cmd)
{
	char	*trim;
	size_t	len;

	trim = ft_strtrim(cmd, " \t\n\r\v\f");
	len = ft_strlen(trim);
	free(cmd);
	if (!trim)
		return (NULL);
	if (trim[0] && (trim[0] == '|' || trim[len - 1] == '|'))
	{
		free(trim);
		return (NULL);
	}
	if (trim[0] && (trim[len - 1] == '<' || trim[len - 1] == '>'))
	{
		free(trim);
		return (NULL);
	}
	return (trim);
}

/**
* @brief checks parsing of current string, expands the $variables inside,
* @brief then trims it.
* @param env the environment
* @param cmd the line to format
* @return the formatted string
*/
char	*format_cmd(t_minishell *ms, char *cmd)
{
	char	*expanded;

	if (check_meta_validity(cmd) || check_parsing(cmd))
	{
		free (cmd);
		return (NULL);
	}
	expanded = expand_line(ms, cmd);
	free(cmd);
	expanded = trim_cmd(expanded);
	return (expanded);
}
