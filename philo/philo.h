/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:49 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/04 12:05:46 by nlouro           ###   ########.fr       */
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
# define VERBOSE 0

typedef struct Philo
{
	int				nr_of_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				times_must_eat;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*mutex_forks;
	int				philos_count;
	int				stime;
	int				utime;
	int				*meals_eaten;
	int				*last_meal;
	pthread_mutex_t	mutex_print;
}	t_Philo;

int		ft_atoi(const char *str);
void	set_time_zero(t_Philo *ph);
int		get_relative_time(t_Philo *ph);
void	init_mutex_forks(t_Philo *ph);
void	free_mutex_forks(t_Philo *philos);
void	log_input_params(int argc, t_Philo *philos);
void	pick_forks(t_Philo *philos, int philo_id);
void	put_forks(t_Philo *philos, int philo_id);
void	log_take_fork(t_Philo *ph, int philo_id, int fork_index);
void	log_put_fork(t_Philo *ph, int philo_id);
void	log_eat(t_Philo *ph, int philo_id);
void	log_sleep(t_Philo *ph, int philo_id);
void	log_think(t_Philo *ph, int philo_id);
void	log_death_and_exit(t_Philo *ph, int philo_id);

#endif
