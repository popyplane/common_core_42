/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 15:25:51 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/09/21 16:27:41 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

void	init_data(t_data *data)
{
	data->nb_of_philo = 0;
	data->time_to_die_ms = 0;
	data->time_to_eat_ms = 0;
	data->time_to_sleep_ms = 0;
	data->max_meal = -1;
	data->start_time_ms = 0;
	data->is_game_over = false;
	data->is_ready = false;
	data->philo = NULL;
}

t_bool	parse_input(int argc, char **argv, t_data *data)
{
	if (argc < 5 || argc > 6)
		return (false);
	data->nb_of_philo = ft_atoi(argv[1]);
	data->time_to_die_ms = ft_atoi(argv[2]);
	data->time_to_eat_ms = ft_atoi(argv[3]);
	data->time_to_sleep_ms = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_meal = ft_atoi(argv[5]);
	if (data->nb_of_philo < 1
		|| data->time_to_die_ms < 1
		|| data->time_to_eat_ms < 1
		|| data->time_to_sleep_ms < 1
		|| (argc == 6 && data->max_meal < 1))
		return (false);
	return (true);
}

void	init_philo(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		data->philo[i].data = data;
		data->philo[i].id = i + 1;
		data->philo[i].eat_count = 0;
		data->philo[i].fork_l = &data->forks[i];
		data->philo[i].fork_r = &data->forks[(i + 1) % data->nb_of_philo];
	}
}
