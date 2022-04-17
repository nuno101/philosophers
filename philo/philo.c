/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/04/17 21:52:34 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	int	number_of_philosophers;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int number_of_times_each_philosopher_must_eat;

	if (argc < 5)
	{
		printf("Error: missing arguments\n");
		return (1);
	}
	else
	{
		printf("number_of_philosophers: %s\n", argv[1]);
		printf("time_to_die: %s\n", argv[2]);
		printf("time_to_eat: %s\n", argv[3]);
		printf("time_to_sleep: %s\n", argv[4]);
		number_of_philosophers = ft_atoi(argv[1]);
		time_to_die = ft_atoi(argv[2]);
		time_to_eat = ft_atoi(argv[3]);
		time_to_sleep = ft_atoi(argv[4]);
	}
	if (argc > 5)
	{
		printf("number_of_times_each_philosopher_must_eat (opt): %s\n", argv[5]);
		number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
	return (0);
}
