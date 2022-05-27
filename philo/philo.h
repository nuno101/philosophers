/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:49 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 10:53:54 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h> // used for printf
#include <stdlib.h> // used for malloc 
#include <pthread.h> // used for mutex functions 
#include <sys/time.h> // used for gettimeofday

#define INT_MAX 2147483647

typedef struct Philo 
{
	int	nr_of_philos;
	pthread_mutex_t *forks_ar;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	nr_of_times_philo_must_eat;
	int	philo_id;
	int	stime;
	int	nr_threads_created;
}	t_Philo;

int		ft_atoi(const char *str);
int		pick_forks(t_Philo *philos, int philo_id);
void	put_forks(t_Philo *philos, int philo_id);
void	log_take_fork(int philo, int timestamp);
void	log_put_fork(int philo, int timestamp);
void	log_eat(int philo, int timestamp);
void	log_sleep(int philo, int timestamp);
void	log_think(int philo, int timestamp);
void	log_die(int philo, int timestamp);

#endif
