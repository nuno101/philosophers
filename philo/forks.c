/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/16 11:40:58 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * fork2 index definition
 */
int	find_fork2_index(int fork1_index, int nr_of_philos)
{
	int	fork2_index;

	fork2_index = fork1_index - 1;
	if (fork2_index < 0)
		fork2_index = nr_of_philos - 1;
	return (fork2_index);
}

/*
 * lock the fork mutex to avoid being used twice
 * pthread_mutex_lock waits until the fork lock is acquired
 */
/*
void	lock_fork(t_Philo *ph, int fork_index)
{
	if (0 != pthread_mutex_lock(&ph->forks[fork_index]))
		printf("pthread_mutex_lock failed\n");
}
*/

void	philo_take_forks(t_Philo *ph, int philo_id, int f1_index, int f2_index)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	if (VERBOSE)
	{
		printf("%dms %d took fork f%d\n", timestamp, philo_id, f1_index + 1);
		printf("%dms %d took fork f%d\n", timestamp, philo_id, f2_index + 1);
	}
	else
	{
		printf("%dms %d has taken a fork\n", timestamp, philo_id);
		printf("%dms %d has taken a fork\n", timestamp, philo_id);
	}
	pthread_mutex_unlock(&ph->mutex_print);
}

/*
 * pick the two closest forks as defined
 * lock the fork mutex to avoid being used twice
 * pthread_mutex_lock waits until the fork lock is acquired
 */
void	philo_pick_forks(t_Philo *ph, int philo_id)
{
	int	fork1_index;
	int	fork2_index;

	fork1_index = philo_id;
	fork2_index = find_fork2_index(fork1_index, ph->nr_of_philos);
	if (0 != pthread_mutex_lock(&ph->forks[fork1_index]))
		printf("pthread_mutex_lock failed\n");
	if (0 != pthread_mutex_lock(&ph->forks[fork2_index]))
		printf("pthread_mutex_lock failed\n");
	/*
	if (philo_id % 2 == 0)
	{
		lock_fork(ph, fork1_index);
		lock_fork(ph, fork2_index);
	}
	else
	{
		lock_fork(ph, fork2_index);
		lock_fork(ph, fork1_index);
	}
	*/
	philo_take_forks(ph, philo_id + 1, fork1_index, fork2_index);
}

/*
 * release both forks by unlocking their mutexes
 */
void	philo_put_forks(t_Philo *ph, int philo_id)
{
	int	fork1_index;
	int	fork2_index;
	int	error;

	fork1_index = philo_id;
	fork2_index = find_fork2_index(fork1_index, ph->nr_of_philos);
	error = pthread_mutex_unlock(&ph->forks[fork1_index]);
	error += pthread_mutex_unlock(&ph->forks[fork2_index]);
	if (error)
	{
		printf("pthread_mutex_unlock failed\n");
		exit(1);
	}
	if (VERBOSE)
		philo_put_fork(ph, philo_id + 1);
}

/*
 * time of last meal is defined as time at the start of last meal
 */
void	philo_eat(t_Philo *ph, int philo_id)
{
	int	timestamp;

	philo_pick_forks(ph, philo_id - 1);
	if (VERBOSE)
		ph->meals_eaten[philo_id] += 1;
	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	ph->last_meal[philo_id - 1] = timestamp;
	if (VERBOSE)
		printf("%dms %d is eating (meal #%d)\n", timestamp, philo_id, ph->meals_eaten[philo_id]);
	else
		printf("%dms %d is eating\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
	sleep_until(ph, timestamp + ph->time_to_eat);
	philo_put_forks(ph, philo_id - 1);
}
