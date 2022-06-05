/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:22:20 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/05 09:54:53 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * called only in VERBOSE mode for debugging purposes
 */
void	log_input_params(int argc, t_Philo *philos)
{
	printf("nr_of_philosophers: %d\n", philos->nr_of_philos);
	printf("time_to_die: %d\n", philos->time_to_die);
	printf("time_to_eat: %d\n", philos->time_to_eat);
	printf("time_to_sleep: %d\n", philos->time_to_sleep);
	if (argc > 5)
		printf("times_must_eat (opt): %d\n", philos->times_must_eat);
}

/*
 * called only in VERBOSE mode for debugging purposes
 */
void	philo_put_fork(t_Philo *ph, int philo_id)
{
	int	timestamp;

	pthread_mutex_lock(&ph->mutex_print);
	timestamp = get_rel_time(ph);
	printf("%dms %d has released its forks\n", timestamp, philo_id);
	pthread_mutex_unlock(&ph->mutex_print);
}
