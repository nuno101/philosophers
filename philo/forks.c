/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 19:53:22 by nlouro           ###   ########.fr       */
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

int	lock_fork(t_Philo *ph, int fork_i)
{
	int	errno;

	if (0 != (errno = pthread_mutex_lock(&ph->forks_ar[fork_i])))
		printf("pthread_mutex_lock failed\n");
	return (errno);
}

void	pick_forks(t_Philo *ph, int philo_id)
{
	//int	errno;
	int	fork1;
	int	fork2;

	fork1 = philo_id;
	fork2 = find_fork2(fork1, ph->nr_of_philos);
	// TODO: wait until the forks are available
	while (lock_fork(ph, fork1) > 0)
		usleep(50);
	while (lock_fork(ph, fork2) > 0)
		usleep(50);
}

void	put_forks(t_Philo *ph, int philo_id)
{
	int	errno;
	int	fork1;
	int	fork2;

	fork1 = philo_id;
	fork2 = find_fork2(fork1, ph->nr_of_philos);
	if (0 != (errno = pthread_mutex_unlock(&ph->forks_ar[fork1])))
		printf("pthread_mutex_lock failed\n");
	if (0 != (errno = pthread_mutex_unlock(&ph->forks_ar[fork2])))
		printf("pthread_mutex_lock failed\n");
}
