/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_functions1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbarru <kbarru@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 13:17:30 by kbarru            #+#    #+#             */
/*   Updated: 2025/03/07 21:41:40 by kbarru           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		++i;
		lst = lst->next;
	}
	return (i);
}

t_list	*ft_lstnew(void *content)
{
	t_list	*head;

	if (!content)
		return (NULL);
	head = malloc(sizeof(t_list));
	if (!head)
		return (NULL);
	head->content = content;
	head->next = NULL;
	return (head);
}

t_list	*init_lst(void *temp, void (*del)(void *))
{
	t_list	*lst;

	if (!temp || !del)
		return (NULL);
	lst = ft_lstnew(temp);
	if (!lst)
	{
		del(temp);
		return (NULL);
	}
	return (lst);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*head2;
	t_list	*current2;
	void	*temp;

	if (!lst || !f || !del)
		return (NULL);
	temp = f(lst->content);
	current2 = init_lst(temp, del);
	if (!current2)
		return (NULL);
	head2 = current2;
	while (lst->next)
	{
		temp = f(lst->next->content);
		current2->next = ft_lstnew(temp);
		if (!(current2->next))
		{
			del(temp);
			ft_lstclear(&head2, del);
			return (NULL);
		}
		current2 = current2->next;
		lst = lst->next;
	}
	return (head2);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
