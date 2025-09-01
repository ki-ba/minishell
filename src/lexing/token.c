/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlouis <mlouis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 14:09:24 by mlouis            #+#    #+#             */
/*   Updated: 2025/08/04 14:23:24 by mlouis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "error.h"
#include "libft.h"
#include "data_structures.h"
#include "lexing.h"
#include "libft.h"

/**
	* @brief called by tokenize() in case a token can't be created.
	* @brief frees stuff. (can't be part of tokenize() bc of norm)
	* @returns ERR_ALLOC error code.
*/
int	delete_tokens(t_list **tokens, t_token *cur_token)
{
	ft_lstclear(tokens, deltoken);
	deltoken(cur_token);
	return (ERR_ALLOC);
}

/**
	* @brief deletes given token.
	* @brief frees its value and the token itself.
*/
void	deltoken(void *token)
{
	t_token	*ttoken;

	ttoken = (t_token *)token;
	if (token)
		free(ttoken->token);
	free(token);
}
