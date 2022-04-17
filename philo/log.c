/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/17 07:14:39 by nlouro            #+#    #+#             */
/*   Updated: 2022/04/17 07:22:18 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	log_fork(int philo, int timestamp)
{
	printf("%d %d has taken a fork\n", timestamp, philo);
} 

void	log_eat(int philo, int timestamp)
{
	printf("%d %d is eating\n", timestamp, philo);
} 

void	log_sleep(int philo, int timestamp)
{
	printf("%d %d is sleeping\n", timestamp, philo);
} 

void	log_think(int philo, int timestamp)
{
	printf("%d %d is thinking\n", timestamp, philo);
} 

void	log_die(int philo, int timestamp)
{
	printf("%d %d died\n", timestamp, philo);
} 
