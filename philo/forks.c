/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 19:05:12 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_Philo *ph, int philo_id)
{
	int	errno;
	int	fork1;
	int	fork2;

	fork1 = philo_id;
	fork2 = philo_id - 1; 
	if (fork2 < 0)
		fork2 = ph->nr_of_philos - 1;
	//printf("get forks for philo %d\n", philo_id);
	// TODO: wait until the forks are available
	if (0 != (errno = pthread_mutex_lock(&ph->forks_ar[fork1])))
		printf("pthread_mutex_lock failed\n");
	if (0 != (errno = pthread_mutex_lock(&ph->forks_ar[fork2])))
		printf("pthread_mutex_lock failed\n");
}

void	put_forks(t_Philo *ph, int philo_id)
{
	int	errno;
	int	fork1;
	int	fork2;

	fork1 = philo_id;
	fork2 = philo_id - 1; 
	if (fork2 < 0)
		fork2 = ph->nr_of_philos - 1;
	//printf("put back forks for philo %d\n", philo_id);
	if (0 != (errno = pthread_mutex_unlock(&ph->forks_ar[fork1])))
		printf("pthread_mutex_lock failed\n");
	if (0 != (errno = pthread_mutex_unlock(&ph->forks_ar[fork2])))
		printf("pthread_mutex_lock failed\n");
}
