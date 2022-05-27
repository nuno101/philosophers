/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 12:01:58 by nlouro           ###   ########.fr       */
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
void	lock_fork(t_Philo *ph, int fork_index)
{
	if (0 != pthread_mutex_lock(&ph->forks[fork_index]))
		printf("pthread_mutex_lock failed\n");
}

/*
 * pick the two closest forks as defined
 */
void	pick_forks(t_Philo *ph, int philo_id)
{
	int	fork1_index;
	int	fork2_index;

	fork1_index = philo_id;
	fork2_index = find_fork2_index(fork1_index, ph->nr_of_philos);
	lock_fork(ph, fork1_index);
	lock_fork(ph, fork2_index);
	log_take_fork(ph->stime, philo_id + 1, fork1_index);
	log_take_fork(ph->stime, philo_id + 1, fork2_index);
}

/*
 * release both forks by unlocking their mutexes
 */
void	put_forks(t_Philo *ph, int philo_id)
{
	int	fork1_index;
	int	fork2_index;

	fork1_index = philo_id;
	fork2_index = find_fork2_index(fork1_index, ph->nr_of_philos);
	if (pthread_mutex_unlock(&ph->forks[fork1_index]))
		printf("pthread_mutex_unlock_1 failed\n");
	if (pthread_mutex_unlock(&ph->forks[fork2_index]))
		printf("pthread_mutex_unlock_2 failed\n");
	if (VERBOSE)
		log_put_fork(ph->stime, philo_id + 1);
}
