/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafoulon <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 11:32:16 by mafoulon          #+#    #+#             */
/*   Updated: 2022/11/08 14:25:33 by mafoulon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (!(s1[i] == s2[i]))
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}
/* void	ft_print_result(int n) */
/* { */
/* 	if (n > 0) */
/* 		write(1, "1", 1); */
/* 	else if (n < 0) */
/* 		write(1, "-1", 2); */
/* 	else */
/* 		write(1, "0", 1); */
/* } */
/* int	main(void) */
/* { */
/* 	ft_print_result(ft_strncmp("test\200", "test\0", 6)); */	
/* } */
