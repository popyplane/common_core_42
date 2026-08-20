/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 09:00:11 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/22 09:00:35 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
		return (NULL);
	else
	{
		tmp->content = content;
		tmp->next = NULL;
	}
	return (tmp);
}
/* #include <stdlib.h> */
/* #include <stdio.h> */
/* int	main(void) */
/* { */
/* 	t_list	*head = ft_lstnew("Hello"); */
/* 	head->next = ft_lstnew("World"); */
/* 	printf("%s\n%s\n", (char *)head->content, (char *)head->next->content); */
/* 	return(0); */
/* } */
