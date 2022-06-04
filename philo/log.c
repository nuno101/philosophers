/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:14:39 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/04 20:51:41 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_take_fork(t_Philo *ph, int philo_id, int fork_index)
{
	long	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	if (VERBOSE)
		printf("%ldms %d took fork f%d\n", timestamp, philo_id, fork_index + 1);
	else
		printf("%ldms %d has taken a fork\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
}

/*
 * time of last meal is defined as time at the start of last meal
 */
void	log_eat(t_Philo *ph, int philo_id)
{
	long	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	ph->last_meal[philo_id - 1] = timestamp;
	printf("%ldms %d is eating\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	//usleep(ph->time_to_eat * 1000);
	usleep((ph->time_to_eat - (timestamp - get_rel_time(ph))) * 1000);
	//sleep_until(timestamp + ph->time_to_eat - get_rel_time(ph));
}

void	log_sleep(t_Philo *ph, int philo_id)
{
	long	timestamp;
	//long	last_meal_end;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%ldms %d is sleeping\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	//usleep(ph->time_to_sleep * 1000);
	usleep((ph->time_to_eat - (timestamp - get_rel_time(ph))) * 1000);
	//my_msleep(ph->time_to_sleep);
	//last_meal_end = ph->last_meal[philo_id - 1] + ph->time_to_eat;
	//printf("%ldms %d is sleeping\n", last_meal_end, philo_id);
	//my_usleep((ph->time_to_sleep - (timestamp - last_meal_end)) * 1000);
}

void	log_think(t_Philo *ph, int philo_id)
{
	long	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%ldms %d is thinking\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
}

/*
 * death of a philosopher ends the simulation
 * upon exit the OS takes care of releasing the mutex lock
 */
void	log_death_and_exit(t_Philo *ph, int philo_id)
{
	long	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%ldms %d died\n", timestamp, philo_id);
	exit(1);
}
