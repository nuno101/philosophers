/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 15:50:52 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * parse user input
 * TODO: consider handling lack of times_must_eat argument differently 
 */
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
	}
	if (argc > 5)
		philos->times_must_eat = ft_atoi(argv[5]);
	else
		philos->times_must_eat = INT_MAX;
	if (VERBOSE)
		log_input_params(argc, philos);
	return (0);
}

void	init_mutex_forks(t_Philo *philos)
{
	int				i;
	pthread_mutex_t	*mutexes;

	i = 0;
	mutexes = malloc(philos->nr_of_philos * sizeof(pthread_mutex_t));
	philos->forks = malloc(philos->nr_of_philos * sizeof(pthread_mutex_t));
	while (i < philos->nr_of_philos)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		philos->forks[i] = mutexes[i];
		i++;
	}
}

/*
 * Philo life manager
 * wait for all threads to be created before starting
 * TODO consider setting philo_id in a more clear way 
 */
void	*start_philo(void *args)
{
	t_Philo	*ph;
	int		philo_id;
	int		repeat;

	ph = (t_Philo *)args;
	repeat = ph->times_must_eat;
	philo_id = ph->philos_count++;
	while (ph->threads_count < ph->nr_of_philos)
		usleep(5);
	while (repeat > 0)
	{
		pick_forks(ph, philo_id - 1);
		log_eat(ph, philo_id);
		usleep(ph->time_to_eat);
		put_forks(ph, philo_id - 1);
		log_sleep(ph, philo_id);
		usleep(ph->time_to_sleep);
		log_think(ph, philo_id);
		if (repeat < INT_MAX)
			repeat--;
	}
	return (NULL);
}

/*
 * Parse user input
 * TODO validate_user_input(t_Philo);
 * Create a thread per philosopher calling start_philo()
 * Wait for threads to finish to call pthread_join()
 */
void	create_threads(t_Philo *philos)
{
	pthread_t		*threads;
	int				i;
	int				errno;

	i = 0;
	threads = malloc(philos->nr_of_philos * sizeof(pthread_t));
	set_time_zero(philos);
	while (i < philos->nr_of_philos)
	{
		errno = pthread_create(&threads[i], NULL, &start_philo, philos);
		if (errno != 0 && VERBOSE > 0)
			printf("Thread creation failed\n");
		else
			if (VERBOSE > 1)
				printf("Thread %d created - id %d\n", i + 1, (int) threads[i]);
		philos->threads_count++;
		i++;
	}
	while (i-- > 0)
	{
		errno = pthread_join(threads[i], NULL);
		if (errno != 0 && VERBOSE > 0)
			printf("pthread_join() [%d] failed\n", i);
	}
}

int	main(int argc, char **argv)
{
	int		error;
	t_Philo	philos;

	error = parse_user_input(argc, argv, &philos);
	if (error == 1)
		return (1);
	philos.philos_count = 1;
	philos.threads_count = 0;
	init_mutex_forks(&philos);
	create_threads(&philos);
	return (0);
}
