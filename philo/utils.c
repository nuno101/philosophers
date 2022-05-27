/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:22:20 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 12:42:48 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_relative_time(int stime)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (VERBOSE > 1)
		printf("s: %ld ms: %d\n", current_time.tv_sec, current_time.tv_usec);
	return (current_time.tv_usec - stime);
}

void	log_input_params(int argc, t_Philo *philos)
{
	printf("nr_of_philosophers: %d\n", philos->nr_of_philos);
	printf("time_to_die: %d\n", philos->time_to_die);
	printf("time_to_eat: %d\n", philos->time_to_eat);
	printf("time_to_sleep: %d\n", philos->time_to_sleep);
	if (argc > 5)
		printf("times_must_eat (opt): %d\n", philos->times_must_eat);
}

void	log_put_fork(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d has released its forks\n", timestamp, philo);
}
