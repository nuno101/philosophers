/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 11:43:18 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	find_fork2_index(int fork1_index, int nr_of_philos)
{
	int	fork2_index;

	fork2_index = fork1_index - 1; 
	if (fork2_index < 0)
		fork2_index = nr_of_philos - 1;
	return (fork2_index);
}


void	lock_fork(t_Philo *ph, int fork_index)
{
	if (0 != pthread_mutex_lock(&ph->forks[fork_index]))
		printf("pthread_mutex_lock failed\n");
}

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

void	put_forks(t_Philo *ph, int philo_id)
{
	int	errno;
	int	fork1_index;
	int	fork2_index;

	fork1_index = philo_id;
	fork2_index = find_fork2_index(fork1_index, ph->nr_of_philos);
	if (0 != (errno = pthread_mutex_unlock(&ph->forks[fork1_index])))
		printf("pthread_mutex_unlock_1 failed\n");
	if (0 != (errno = pthread_mutex_unlock(&ph->forks[fork2_index])))
		printf("pthread_mutex_unlock_2 failed\n");
	if (DEBUG)
		log_put_fork(ph->stime, philo_id + 1);
}
