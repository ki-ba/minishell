#include "libft.h"

void	ft_lstclear_but(t_list **lst, void (*f)(void *), t_list *item)
{
	t_list	*cur;
	t_list	*next;

	if (!lst)
		return ;
	cur = *lst;
	while (cur)
	{
		next = cur->next;
		if (cur != item)
		{
			f(cur->content);
			cur->next = NULL;
			free(cur);
		}
		cur = next;
	}
	*lst = item;
}
