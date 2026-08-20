/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:00:23 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/09/21 17:13:16 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes.h"

static t_bool	init_mutexes(t_data *data);
static void	*redirect_philo(void *arg);
static void	ft_destroy_threads(t_data *data, t_philo *philos);

t_bool	spawn_threads(t_data *data)
{
	int	i;

	if (!init_mutexes(data))
		return (false);
	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (pthread_create(&data->philo[i].thread, NULL,
				&redirect_philo, &data->philo[i]))
			return (false);
	}
	pthread_mutex_lock(&data->data_mutex);
	data->start_time_ms = ft_get_time_in_ms();
	i = -1;
	while (++i < data->nb_of_philo)
		data->philo[i].last_meal_time_ms = data->start_time_ms;
	data->is_ready = true;
	pthread_mutex_unlock(&data->data_mutex);
	wait_for_exit(data, data->philo);
	ft_destroy_threads(data, data->philo);
	return (true);
}

static t_bool	init_mutexes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i], NULL) != 0)
			return (false);
	}
	if (pthread_mutex_init(&data->data_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->meal_mutex, NULL) != 0)
		return (false);
	if (pthread_mutex_init(&data->print_mutex, NULL) != 0)
		return (false);
	return (true);
}

static void	*redirect_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_of_philo == 1)
		ft_single_philo(philo);
	else
		ft_multiple_philos(philo);
	return (NULL);
}

static void	ft_destroy_threads(t_data *data, t_philo *philos)
{
	int	i;

	i = -1;
	while (++i < data->nb_of_philo)
		pthread_join(philos[i].thread, NULL);
	i = -1;
	while (++i < data->nb_of_philo)
		pthread_mutex_destroy(&data->forks[i]);
	pthread_mutex_destroy(&data->data_mutex);
	pthread_mutex_destroy(&data->meal_mutex);
	pthread_mutex_destroy(&data->print_mutex);
}