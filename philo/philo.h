/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:49 by nlouro            #+#    #+#             */
/*   Updated: 2022/04/18 22:18:37 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h> // used for printf
#include <pthread.h> // used for mutex functions 
#include <sys/time.h> // used for gettimeofday

typedef struct Philo 
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	number_of_times_each_philosopher_must_eat;
	int	stime;
}	t_Philo;

int		ft_atoi(const char *str);
void	log_fork(int philo, int timestamp);
void	log_eat(int philo, int timestamp);
void	log_sleep(int philo, int timestamp);
void	log_think(int philo, int timestamp);
void	log_die(int philo, int timestamp);

#endif
