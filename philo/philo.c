/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 13:23:27 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_user_input(int argc, char **argv, t_Philo *philos)
{
	if (argc < 5)
	{
		printf("Error: missing arguments\n");
		return (1);
	}
	else
	{
		philos->nr_of_philos = ft_atoi(argv[1]);
		philos->time_to_die = ft_atoi(argv[2]);
		philos->time_to_eat = ft_atoi(argv[3]);
		philos->time_to_sleep = ft_atoi(argv[4]);
		printf("nr_of_philosophers: %d\n", philos->nr_of_philos);
		printf("time_to_die: %d\n", philos->time_to_die);
		printf("time_to_eat: %d\n", philos->time_to_eat);
		printf("time_to_sleep: %d\n", philos->time_to_sleep);
	}
	if (argc > 5)
	{
		philos->nr_of_times_philo_must_eat = ft_atoi(argv[5]);
		printf("nr_of_times_philo_must_eat (opt): %d\n", philos->nr_of_times_philo_must_eat);
	}
	return (0);
}

void *init_philo(void *arg)
{
	sleep(1);
	//printf("micro seconds : %d\n", (int) arg);
	printf("arg: %d\n", (int) arg);
	return NULL;
}

void	create_threads(t_Philo *philos)
{
	pthread_t	thread_id;
	struct	timeval current_time;
	int		i;
	int		error;

	i = 0;
	gettimeofday(&current_time, NULL);
	philos->stime = current_time.tv_usec;

	// Create 1 thread per philosopher calling threadFunc()
	while (i < philos->nr_of_philos)
	{
	    printf("Thread creation: %d\n", i);
		error = pthread_create(&thread_id, NULL, &init_philo, philos);
		if (error)
	    	printf("Thread creation failed\n");
		else
		    printf("Thread created with id %d\n", (int) thread_id);
		// Wait for thread to exit
		error = pthread_join(thread_id, NULL);
		i++;
	}
}

int	main(int argc, char **argv)
{
	int	error;
	t_Philo	philos;
	struct timeval current_time;

	gettimeofday(&current_time, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	error = parse_user_input(argc, argv, &philos);
	printf("nr_of_philos: %d time_to_die %d\n", philos.nr_of_philos, philos.time_to_die);
	// TODO validate_user_input(t_Philo);
	if (error == 1)
		return (1);
	create_threads(&philos);
	printf("seconds : %ld\nmicro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	return (0);
}
