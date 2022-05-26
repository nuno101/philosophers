/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronnde>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/26 17:53:59 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 18:02:09 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	get_forks(t_Philo *ph, int philo_id)
{
	printf("philo nr %d\n", ph->nr_of_philos);
	printf("get forks for philo %d\n", philo_id);
}

void	put_forks(t_Philo *ph, int philo_id)
{
	printf("philo nr %d\n", ph->nr_of_philos);
	printf("put back forks for philo %d\n", philo_id);
}
