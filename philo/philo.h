/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:49 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 12:26:33 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h> // used for printf
# include <stdlib.h> // used for malloc 
# include <pthread.h> // used for mutex functions 
# include <sys/time.h> // used for gettimeofday

# define INT_MAX 2147483647
# define VERBOSE 1 

typedef struct Philo
{
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	int				threads_count;
	int				philos_count;
	int				stime;
}	t_Philo;

int		ft_atoi(const char *str);
int		get_relative_time(int stime);
void	pick_forks(t_Philo *philos, int philo_id);
void	put_forks(t_Philo *philos, int philo_id);
void	log_take_fork(int philo, int timestamp, int fork_index);
void	log_put_fork(int philo, int timestamp);
void	log_eat(int philo, int timestamp);
void	log_sleep(int philo, int timestamp);
void	log_think(int philo, int timestamp);
void	log_die(int philo, int timestamp);

#endif
