/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:22:20 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/03 09:37:06 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_time_zero(t_Philo *ph)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	ph->stime = current_time.tv_sec;
	ph->utime = current_time.tv_usec;
	if (VERBOSE > 1)
		printf("sec: %ld usec: %d\n", current_time.tv_sec, current_time.tv_usec);
}

int	get_relative_time(t_Philo *ph)
{
	struct timeval	current_time;
	int				sec_from_zero;
	int				usec_from_zero;

	gettimeofday(&current_time, NULL);
	sec_from_zero = current_time.tv_sec - ph->stime;
	usec_from_zero = current_time.tv_usec - ph->utime;
	return (sec_from_zero * 1000000 + usec_from_zero);
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

void	log_put_fork(t_Philo *ph, int philo_id)
{
	int	timestamp;

	timestamp = get_relative_time(ph);
	printf("%dms %d has released its forks\n", timestamp, philo_id);
}
