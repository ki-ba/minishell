/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:24 by mlouis            #+#    #+#             */
/*   Updated: 2025/07/30 14:09:27 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	deltoken(void *token)
{
	t_token	*ttoken;

	ttoken = (t_token *)token;
	if (token)
		free(ttoken->token);
	free(token);
}
