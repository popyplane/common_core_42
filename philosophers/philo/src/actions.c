/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/20 12:50:21 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/09/21 16:28:14 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

static void	ft_print(t_philo *philo, char *msg, int arg_ms);

void	*ft_single_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->data->print_mutex);
	printf("[0ms] %d has taken a fork\n", philo->id);
	pthread_mutex_unlock(&philo->data->print_mutex);
	return (NULL);
}

void	ft_multiple_philos(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (pthread_mutex_lock(&philo->data->data_mutex) == 0
		&& !philo->data->is_ready)
		pthread_mutex_unlock(&philo->data->data_mutex);
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->id & 1)
	{
		pthread_mutex_lock(&philo->data->data_mutex);
		usleep(philo->data->time_to_eat_ms * 0.9 + 1);
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
	while (pthread_mutex_lock(&philo->data->meal_mutex) == 0
		&& !philo->data->is_game_over)
	{
		pthread_mutex_unlock(&philo->data->meal_mutex);
		ft_eat(philo);
		ft_sleep_and_think(philo);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
}

void	ft_eat(t_philo *philo)
{
	int	eat_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	eat_time = philo->data->time_to_eat_ms;
	pthread_mutex_unlock(&philo->data->data_mutex);
	if (philo->id & 1)
		pthread_mutex_lock(philo->fork_r);
	else
		pthread_mutex_lock(philo->fork_l);
	ft_print(philo, "has taken a fork", eat_time);
	if (philo->id & 1)
		pthread_mutex_lock(philo->fork_l);
	else
		pthread_mutex_lock(philo->fork_r);
	ft_print(philo, "has taken a fork", eat_time);
	ft_print(philo, "is eating", eat_time);
	pthread_mutex_lock(&philo->data->meal_mutex);
	philo->last_meal_time_ms = ft_get_time_in_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->meal_mutex);
	ft_usleep(eat_time);
	pthread_mutex_unlock(philo->fork_l);
	pthread_mutex_unlock(philo->fork_r);
}

void	ft_sleep_and_think(t_philo *philo)
{
	int	sleep_time;

	pthread_mutex_lock(&philo->data->data_mutex);
	sleep_time = philo->data->time_to_sleep_ms;
	pthread_mutex_unlock(&philo->data->data_mutex);
	ft_print(philo, "is sleeping", sleep_time);
	ft_usleep(sleep_time);
	ft_print(philo, "is thinking", sleep_time);
}

void	ft_print(t_philo *philo, char *msg, int arg_ms)
{
	pthread_mutex_lock(&philo->data->meal_mutex);
	if (!philo->data->is_game_over)
	{
		pthread_mutex_lock(&philo->data->print_mutex);
		printf("[%dms] %d %s\n", ft_get_rounded_time_diff(
			philo->data->start_time_ms, arg_ms), philo->id, msg);
		pthread_mutex_unlock(&philo->data->print_mutex);
	}
	pthread_mutex_unlock(&philo->data->meal_mutex);
}