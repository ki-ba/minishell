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
#include "data_structures.h"

void	deltoken(void *token)
{
	t_token	*ttoken;

	ttoken = (t_token *)token;
	if (token)
		free(ttoken->token);
	free(token);
}
