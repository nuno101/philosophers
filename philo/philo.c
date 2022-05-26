/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 15:16:28 by nlouro           ###   ########.fr       */
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

pthread_mutex_t	init_mutex()
{
	pthread_mutex_t	mutex;

	pthread_mutex_init(&mutex, NULL);
	return (mutex);
}

void	init_forks(t_Philo *philos)
{
	int	i;

	i = 0;
	philos->forks_ar = malloc(philos->nr_of_philos * sizeof(pthread_mutex_t));
	while (i < philos->nr_of_philos)
	{
		//philos->forks_ar[0] = init_mutex();
		i++;
	}
}

void *start_philo(void *arg)
//void *start_philo(t_Philo *arg)
{
	log_take_fork(1,0);
	//log_take_fork(1,100);
	//sleep(1);
	//log_put_fork(1,200);
	//log_sleep(1,300);
	//log_think(1,400);
	printf("arg: %d\n", (int) arg);
	//printf("arg: %d\n", (int) arg->nr_of_philos);
	//printf("arg: %d\n", philos->nr_of_philos);
	return (NULL);
}

void	create_threads(t_Philo *philos)
{
	pthread_t	threads[philos->nr_of_philos];
	struct	timeval current_time;
	int		i;
	int		error;
	int		errno;

	i = 0;
	gettimeofday(&current_time, NULL);
	philos->stime = current_time.tv_usec;

	// Create a thread per philosopher calling start_philo()
	while (i < philos->nr_of_philos)
	{
		error = pthread_create(&threads[i], NULL, &start_philo, philos);
		if (error)
	    	printf("Thread creation failed\n");
		else
		    printf("Thread %d created with id %d\n", i, (int) threads[i]);
		i++;
	}
	// Wait for threads to finish
	while (i-- > 0)
    {
        if (0 != (errno = pthread_join(threads[i], NULL))) {
            printf("pthread_join() [%d] failed\n", i);
            //return (1);
        }
		else
            printf("pthread_join() [%d] ok\n", i);
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
	init_forks(&philos);
	// TODO validate_user_input(t_Philo);
	if (error == 1)
		return (1);
	create_threads(&philos);
	printf("seconds : %ld\nmicro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	return (0);
}
