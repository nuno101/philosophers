/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:49 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/03 09:05:19 by nlouro           ###   ########.fr       */
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
	int				philos_count;
	int				stime;
	int				utime;
	int				*meals_eaten;
	int				*last_meal;
}	t_Philo;

int		ft_atoi(const char *str);
void	set_time_zero(t_Philo *ph);
int		get_relative_time(t_Philo *ph);
void	log_input_params(int argc, t_Philo *philos);
void	pick_forks(t_Philo *philos, int philo_id);
void	put_forks(t_Philo *philos, int philo_id);
void	log_take_fork(t_Philo *ph, int philo_id, int fork_index);
void	log_put_fork(t_Philo *ph, int philo_id);
void	log_eat(t_Philo *ph, int philo_id);
void	log_sleep(t_Philo *ph, int philo_id);
void	log_think(t_Philo *ph, int philo_id);
void	log_death(t_Philo *ph, int philo_id);

#endif
