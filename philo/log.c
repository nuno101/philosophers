/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:14:39 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/04 11:15:57 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_take_fork(t_Philo *ph, int philo_id, int fork_index)
{
	int	timestamp;

	timestamp = get_relative_time(ph);
	if (VERBOSE)
		printf("%dms %d took fork f%d\n", timestamp, philo_id, fork_index + 1);
	else
		printf("%dms %d has taken a fork\n", timestamp, philo_id);
}

void	log_eat(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_relative_time(ph);
	ph->last_meal[philo_id - 1] = timestamp + ph->time_to_eat;
	printf("%dms %d is eating\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	usleep(ph->time_to_eat);
}

void	log_sleep(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_relative_time(ph);
	printf("%dms %d is sleeping\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	usleep(ph->time_to_sleep);
}

void	log_think(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_relative_time(ph);
	printf("%dms %d is thinking\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
}

/*
 * death of a philosopher ends the simulation
 * upon exit the OS takes care of releasing the mutex lock
 */
void	log_death_and_exit(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_relative_time(ph);
	printf("%dms %d died\n", timestamp, philo_id);
	exit(1);
}
