/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_formatting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:12:18 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 20:43:57 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minishell.h"
#include "lexing.h"
#include "parsing.h"

static char	*trim_cmd(int *err, char *cmd)
{
	char	*trim;
	size_t	len;

	trim = ft_strtrim(cmd, " \t\n\r\v\f");
	len = ft_strlen(trim);
	free(cmd);
	if (!trim)
	{
		*err = ERR_ALLOC;
		return (NULL);
	}
	if (trim[0] && (trim[0] == '|' || trim[len - 1] == '|'))
	{
		free(trim);
		*err = ERR_PARSING;
		return (NULL);
	}
	if (trim[0] && (trim[len - 1] == '<' || trim[len - 1] == '>'))
	{
		free(trim);
		*err = ERR_PARSING;
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
	char	*tmp;

	if (!cmd)
		return (NULL);
	if (check_meta_validity(cmd) || check_parsing(cmd))
	{
		free (cmd);
		ms->error = ERR_PARSING;
		return (NULL);
	}
	tmp = expand_line(ms, cmd, DOLLAR);
	free(cmd);
	if (!tmp)
		return (NULL);
	expanded = expand_line(ms, tmp, METACHAR);
	free(tmp);
	expanded = trim_cmd(&ms->error, expanded);
	return (expanded);
}
