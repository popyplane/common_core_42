/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 08:58:34 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 08:59:53 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newhead;
	t_list	*tmp;
	t_list	*ptr;

	if (!lst || !f || !del)
		return (NULL);
	newhead = ft_lstnew(f(lst->content));
	if (!newhead)
		return (NULL);
	ptr = newhead;
	lst = lst->next;
	while (lst)
	{
		tmp = ft_lstnew(f(lst->content));
		if (!tmp)
		{
			ft_lstclear(&newhead, del);
			return (0);
		}
		ptr->next = tmp;
		ptr = tmp;
		lst = lst->next;
	}
	return (newhead);
}
