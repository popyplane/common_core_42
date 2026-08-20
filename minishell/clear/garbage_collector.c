/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   garbage_collector.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/20 15:06:48 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/12/20 17:48:33 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "clear.h"

static void	delete(void *ptr);
void		*ft_garbage_collector(void *ptr, t_bool clean);

void	*ft_garbage_collector(void *ptr, t_bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, delete);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}

static void	delete(void *ptr)
{
	free(ptr);
	ptr = NULL;
}
