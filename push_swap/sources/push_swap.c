/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/15 09:58:34 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/05/22 15:26:35 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/push_swap.h"

int main(int argc, char **argv)
{
    t_list  *a;
    t_list  *b;
    int     *tab;

    if (!check_args(argc, argv))
        return (0);
    a = create_list(argc, argv);
    b = NULL;
    tab = indexing_stack(a, argc - 1);
    replacing(&a, tab);
    free(tab);
    if (argc - 1 == 2)
        ft_sort_two(&a);
    else if (argc - 1 == 3)
        ft_sort_three(&a);
    else if (argc - 1 == 5)
        ft_sort_five(&a, &b);
    else
        ft_radix(&a, &b, argc - 1);
    free_list(a);
    free_list(b);
    return (0);
}