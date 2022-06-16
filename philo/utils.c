/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:22:20 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/15 16:32:56 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * called after all threads have been created
 * used to sync the threads start
 */
void	set_time_zero(t_Philo *ph)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	ph->stime = current_time.tv_sec;
	ph->utime = current_time.tv_usec;
	if (VERBOSE > 1)
		printf("sec: %ld usec: %d\n", current_time.tv_sec, current_time.tv_usec);
}

int	get_rel_time(t_Philo *ph)
{
	struct timeval	current_time;
	int			sec_from_zero;
	int			usec_from_zero;

	gettimeofday(&current_time, NULL);
	sec_from_zero = current_time.tv_sec - ph->stime;
	usec_from_zero = current_time.tv_usec - ph->utime;
	return (sec_from_zero * 1000 + usec_from_zero / 1000);
}

/*
 * target wake-up time: wake_at 
 * idea is to call usleep with smaller time periods
 */
void	sleep_until(t_Philo *ph, int wake_at)
{
	int	now;

	now = get_rel_time(ph);
	while(now < wake_at)
	{
		usleep(100);
		now = get_rel_time(ph);
	}
}

/*
 * initialize the forks mutexes
 * these mutexes ensure each fork is only used by a philo at a time
 * see also free_mutex_forks which frees the memory allocated here
 */
void	init_mutex_forks(t_Philo *ph)
{
	int	i;

	i = 0;
	ph->mutex_forks = malloc(ph->nr_of_philos * sizeof(pthread_mutex_t));
	ph->forks = malloc(ph->nr_of_philos * sizeof(pthread_mutex_t));
	while (i < ph->nr_of_philos)
	{
		pthread_mutex_init(&ph->mutex_forks[i], NULL);
		ph->forks[i] = ph->mutex_forks[i];
		i++;
	}
}

/*
 * free the memory allocated by the init_mutex_forks function
 */
void	free_mutex_forks(t_Philo *philos)
{
	int	i;

	i = 0;
	while (i < philos->nr_of_philos)
	{
		pthread_mutex_destroy(&philos->forks[i]);
		i++;
	}
	free(philos->forks);
	free(philos->mutex_forks);
}
