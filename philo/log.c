/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:14:39 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 16:29:07 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_relative_time(int stime)
{
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
    //printf("seconds : %ld micro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	return (current_time.tv_usec - stime);
}

void	log_take_fork(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d has taken a fork\n", timestamp, philo);
} 

void	log_put_fork(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d has released a fork\n", timestamp, philo);
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
