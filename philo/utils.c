/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 12:22:20 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 12:25:07 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_relative_time(int stime)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	if (VERBOSE > 1)
		printf("s: %ld ms: %d\n", current_time.tv_sec, current_time.tv_usec);
	return (current_time.tv_usec - stime);
}

void	log_put_fork(int stime, int philo)
{
	int	timestamp;

	timestamp = get_relative_time(stime);
	printf("%dms %d has released its forks\n", timestamp, philo);
}
