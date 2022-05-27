/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 10:14:45 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	find_fork2(int fork1, int nr_of_philos)
{
	int	fork2;

	fork2 = fork1 - 1; 
	if (fork2 < 0)
		fork2 = nr_of_philos - 1;
	return (fork2);
}
/*
int	lock_fork(t_Philo *ph, int fork_i)
{
	int	errno;

	if (0 != (errno = pthread_mutex_lock(&ph->forks_ar[fork_i])))
		printf("pthread_mutex_lock failed\n");
	return (errno);
}
	errno = lock_fork(ph, fork1);
	if (errno == 0)
		errno = lock_fork(ph, fork2);
	if (errno != 0)
		 pthread_mutex_unlock(&ph->forks_ar[fork1]);
		 */

int	pick_forks(t_Philo *ph, int philo_id)
{
	int	errno;
	int	fork1;
	int	fork2;

	fork1 = philo_id;
	fork2 = find_fork2(fork1, ph->nr_of_philos);
	//printf("fork1 index: %d\n", fork1);
	//printf("fork2 index: %d\n", fork2);
	if (0 != (errno = pthread_mutex_lock(&ph->forks_ar[fork1])))
		printf("pthread_mutex_lock_1 failed\n");
	if (0 != (errno = pthread_mutex_lock(&ph->forks_ar[fork2])))
		printf("pthread_mutex_lock_2 failed\n");
	return (errno);
}

void	put_forks(t_Philo *ph, int philo_id)
{
	int	errno;
	int	fork1;
	int	fork2;

	fork1 = philo_id;
	fork2 = find_fork2(fork1, ph->nr_of_philos);
	if (0 != (errno = pthread_mutex_unlock(&ph->forks_ar[fork1])))
		printf("pthread_mutex_unlock_1 failed\n");
	if (0 != (errno = pthread_mutex_unlock(&ph->forks_ar[fork2])))
		printf("pthread_mutex_unlock_2 failed\n");
}
