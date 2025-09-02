/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 16:29:09 by kbarru            #+#    #+#             */
/*   Updated: 2025/09/02 16:49:17 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "data_structures.h"
#include "minishell.h"

void	print_arr_oneline(char **arr)
{
	size_t	i;

	i = 0;
	if (!arr)
	{
		ft_printf("[NULL ARR]");
		return ;
	}
	while (arr[i])
	{
		ft_printf("%s ", arr[i]);
		++i;
	}
}
void	print_tokens(t_list *tokens)
{
	t_list	*current;
	t_token	*tok;

	current = tokens;
	while (current)
	{
		tok = current->content;
		ft_printf("%d '%s' ====> ", tok->type, tok->token);
		current = current->next;
	}
	ft_printf("NULL \n");
}

void	print_exec_lst(t_list *exec_lst)
{
	t_list		*current;
	t_exec_node	*node;

	current = exec_lst;
	while (current)
	{
		node = current->content;
		print_arr_oneline(node->cmd);
		ft_printf("[%d;%d] (%d) ->", node->io[0], node->io[1], node->status);
		current = current->next;
	}
	ft_printf("NULL \n");
}
