/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/21 15:05:04 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/05/22 15:45:16 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

t_list	*create_list(int argc, char **argv)
{
	t_list	*head;
	int		i;

	head = ft_lstnew(ft_atoi(argv[1]));
	i = 1;
	while (++i < argc)
		ft_lstadd_back(&head, ft_lstnew(ft_atoi(argv[i])));
	return (head);
}

static int	is_valid_arg(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '-' || s[i] == '+')
		i++;
	if (!s[i])
		return (0);
	while (s[i])
	{
		if (s[i] < '0' || s[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	check_args(int argc, char **argv)
{
	int a;
	int	b;

	if (argc < 2)
		return (0);
	a = 0;
	while (++a < argc)
	{
		if (!is_valid_arg(argv[a]))
			return (ft_putstr_fd("Error\n", 2), 0);
		b = 0;
		while (++b < argc)
			if (a != b && ft_atoi(argv[a]) == ft_atoi(argv[b]))
				return (ft_putstr_fd("Error\n", 2), 0);
		if (ft_atol(argv[a]) < -2147483648 || ft_atol(argv[a]) > 2147483647)
			return (ft_putstr_fd("Error\n", 2), 0);
	}
	return (1);
}

int	*copy_as_tab(t_list *lst, int size)
{
	int	*tab;
	int	i;

	tab = malloc(size * sizeof(int));
	if (!tab)
		return (NULL);
	i = 0;
	while (i < size)
	{
		*(tab + i) = lst->v;
		lst = lst->n;
		i++;
	}
	return (tab);
}

void	sort_tab(int *tab, int size)
{
	int	i;
	int temp;

	i = -1;
	while (++i < size - 1)
	{
		if (tab[i] > tab[i + 1])
		{
			temp = tab[i];
			tab[i] = tab[i + 1];
			tab[i + 1] = temp;
			i = -1;
		}
	}
}

void	replace_args_by_indices(int *sorted_array, int size, t_list *lst)
{
	int i;

	while (lst)
	{
		i = -1;
		while (++i < size)
		{
			if (lst->v == sorted_array[i])
				lst->v = i;
		}
		lst = lst->n; 
	}
}