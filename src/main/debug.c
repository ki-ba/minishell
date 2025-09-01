/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 16:27:50 by kbarru            #+#    #+#             */
/*   Updated: 2025/08/19 16:28:20 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "minishell.h"

// TODO: REMOVE THIS FILE

t_exec_node	getnode(t_list *exec_lst)
{
	t_exec_node	node;

	node = *((t_exec_node *)(exec_lst->content));
	return (node);
}

void	print_exec_lst(t_list *exec_lst)
{
	t_list		*current;
	t_exec_node	node;

	current = exec_lst;
	while (current)
	{
		node = getnode(current);
		ft_print_arr(node.cmd);
		ft_printf("io : %d ; %d\n", node.io[0], node.io[1]);
		current = current->next;
	}
}
