/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   id_token.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:08:33 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/19 16:34:03 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "data_structures.h"
#include "libft.h"

/**
	* @brief determines if the given string is a redirection meta-character.
*/
t_token_type	determine_redirect(char token_str[])
{
	if (ft_strncmp(token_str, ">", 2) == 0)
		return (T_REDIR_OUT);
	else if (ft_strncmp(token_str, "<", 2) == 0)
		return (T_REDIR_IN);
	else if (ft_strncmp(token_str, ">>", 3) == 0)
		return (T_APPEND);
	else if (ft_strncmp(token_str, "<<", 3) == 0)
		return (T_HD);
	return (0);
}

/**
	* @brief determines if the given string is an option meta-character.
*/
t_bool	determine_option(char token_str[])
{
	return (ft_strlen(token_str) == 2 && token_str[0] == '-');
}

/**
	* @brief determines if the given string is a pipe meta-character.
*/
t_bool	determine_pipe(char token_str[])
{
	return (!ft_strncmp(token_str, "|", 2));
}
