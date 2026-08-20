/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 11:44:18 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/09/21 16:27:28 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

static t_bool	ft_did_die(t_data *data, t_philo *philo);
static t_bool	ft_did_eat(t_data *data, t_philo *philos);

void	wait_for_exit(t_data *data, t_philo *philos)
{
	int	i;

	while(true)
	{
		i = -1;
		while (++i < data->nb_of_philo)
		{
			if (ft_did_die(data, &philos[i]))
				return;
		}
		if (ft_did_eat(data, philos))
			return;
	}
}

t_bool	ft_did_die(t_data *data, t_philo *philo)
{
	pthread_mutex_lock(&data->meal_mutex);
	if (ft_get_time_diff(philo->last_meal_time_ms)
		> data->time_to_die_ms)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%dms] %d died\n", ft_get_rounded_time_diff(
			data->start_time_ms, data->time_to_die_ms), philo->id);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->print_mutex);
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}

t_bool	ft_did_eat(t_data *data, t_philo *philos)
{
	int	i;
	int	have_all_eaten;

	i = -1;
	have_all_eaten = 0;
	pthread_mutex_lock(&data->meal_mutex);
	while (++i < data->nb_of_philo && data->max_meal != -1)
		if (philos[i].eat_count >= data->max_meal)
			have_all_eaten++;
	if (have_all_eaten == data->nb_of_philo)
	{
		pthread_mutex_lock(&data->print_mutex);
		printf("[%dms] all philosophers have eaten %d times\n",
			ft_get_rounded_time_diff(data->start_time_ms, data->time_to_eat_ms),
			data->max_meal);
		pthread_mutex_unlock(&data->print_mutex);
		data->is_game_over = true;
		pthread_mutex_unlock(&data->meal_mutex);
		return (true);
	}
	pthread_mutex_unlock(&data->meal_mutex);
	return (false);
}