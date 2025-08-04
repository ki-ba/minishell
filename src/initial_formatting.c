/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initial_formatting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:08 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 15:44:55 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexing.h"
#include "parsing.h"

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

char	*format_cmd(t_env_lst *env, char *cmd)
{
	char	*expanded;

	if (check_meta_validity(cmd) || check_parsing(cmd))
	{
		free (cmd);
		return (NULL);
	}
	expanded = expand_line(env, cmd);
	free(cmd);
	expanded = trim_cmd(expanded);
	return (expanded);
}
