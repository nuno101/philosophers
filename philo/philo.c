/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/04/18 22:27:33 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	parse_user_input(int argc, char **argv, struct Philo t_Philo)
{
	if (argc < 5)
	{
		printf("Error: missing arguments\n");
		return (1);
	}
	else
	{
		t_Philo.number_of_philosophers = ft_atoi(argv[1]);
		t_Philo.time_to_die = ft_atoi(argv[2]);
		t_Philo.time_to_eat = ft_atoi(argv[3]);
		t_Philo.time_to_sleep = ft_atoi(argv[4]);
		printf("number_of_philosophers: %d\n", t_Philo.number_of_philosophers);
		printf("time_to_die: %s\n", argv[2]);
		printf("time_to_eat: %s\n", argv[3]);
		printf("time_to_sleep: %s\n", argv[4]);
	}
	if (argc > 5)
	{
		printf("number_of_times_each_philosopher_must_eat (opt): %s\n", argv[5]);
		t_Philo.number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	}
	return (0);
}

void *threadFunc(void *arg)
{
	sleep(10);
	printf("micro seconds : %d\n", (int) arg);
	return NULL;
}

void	create_threads(struct Philo t_Philo)
{
	pthread_t	thread_id;
	struct	timeval current_time;
	int		error;

	gettimeofday(&current_time, NULL);
	t_Philo.stime = current_time.tv_usec;
	// Create a thread calling threadFunc()
	error = pthread_create(&thread_id, NULL, &threadFunc, &t_Philo);
	if (error)
	    printf("Thread creation failed\n");
	else
	    printf("Thread created with id %d\n", (int) thread_id);
	// Wait for thread to exit
	error = pthread_join(thread_id, NULL);
}

int	main(int argc, char **argv)
{
	int	error;
	struct Philo	t_Philo;
	struct timeval current_time;

	t_Philo.number_of_philosophers = 0;
	gettimeofday(&current_time, NULL);
	printf("seconds : %ld\nmicro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	error = parse_user_input(argc, argv, t_Philo);
	if (error == 1)
		return (1);
	create_threads(t_Philo);
	getchar();	
	return (0);
}
