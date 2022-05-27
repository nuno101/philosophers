/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:14:39 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 12:23:32 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_take_fork(int stime, int philo, int fork_index)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	if (VERBOSE)
		printf("%dms %d has taken fork f%d\n", timestamp, philo, fork_index + 1);
	else
		printf("%dms %d has taken a fork\n", timestamp, philo);
}

void	log_eat(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d is eating\n", timestamp, philo);
}

void	log_sleep(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d is sleeping\n", timestamp, philo);
}

void	log_think(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d is thinking\n", timestamp, philo);
}

void	log_die(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d died\n", timestamp, philo);
}
