/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bvieilhe <bvieilhe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 12:57:07 by bvieilhe          #+#    #+#             */
/*   Updated: 2023/09/21 16:08:49 by bvieilhe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCTIONS_H
# define FUNCTIONS_H

# include "../includes.h"

/**
 * ----- init.c ------
*/
void			init_data(t_data *data);
t_bool			parse_input(int argc, char **argv, t_data *data);
void			init_philo(t_data *data);

/**
 * ----- actions.c -----
*/
void			*ft_single_philo(void *arg);
void			ft_multiple_philos(void *arg);
void			ft_eat(t_philo *philo);
void			ft_sleep_and_think(t_philo *philo);

/**
 * ----- threads.c -----
*/
t_bool			spawn_threads(t_data *data);

/**
 * ----- exit.c -----
*/
void			wait_for_exit(t_data *data, t_philo *philos);

/**
 * ----- utils.c -----
*/
int				ft_atoi(char *str);

/**
 * ----- time.c -----
*/
unsigned long	ft_get_time_in_ms(void);
int				ft_get_time_diff(unsigned long time);
int				ft_get_rounded_time_diff(unsigned long time, int round);
void			ft_usleep(unsigned long time);

/**
 * ----- err.c -----
*/
int             err(char*err);

#endif