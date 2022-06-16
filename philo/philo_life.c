/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_life.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:14:39 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/16 19:09:39 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_sleep(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%dms %d is sleeping\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	sleep_until(ph, timestamp + ph->time_to_sleep);
}

/*
 * thinking requires no time but a fraction
 * of the philo's free_time is added to avoid immediate
 * competition with philos who need to eat
 */
void	philo_think(t_Philo *ph, int philo_id)
{
	int	timestamp;
	int	time_free;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%dms %d is thinking\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	time_free = ph->time_to_die - ph->time_to_eat - ph->time_to_sleep;
	if (ph->nr_of_philos < 10)
		sleep_until(ph, timestamp + time_free / 10);
	else
		sleep_until(ph, timestamp + time_free / 3);
}

/*
 * death of a philosopher ends the simulation
 * upon exit the OS takes care of releasing the mutex lock
 */
void	philo_die_and_exit(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%dms %d died\n", timestamp, philo_id);
	exit(1);
}
