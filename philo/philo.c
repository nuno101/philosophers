/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/04 12:04:34 by nlouro           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
 * parse user input
 * FIXME: consider handling lack of times_must_eat argument differently 
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

/*
 * Philo nutrition monitor
 * Waits for all threads to be ready (stime > 0) to start
 * Checks whether each philosopher has starved to death
 * Thread ends when:
 * 1) if case a philo starves by calling log_death_and_exit
 * 2) when all philosophers have eaten [ph->times_must_eat] times
 */
void	*start_watcher(void *args)
{
	t_Philo	*ph;
	int		philo_id;
	int		time_since_eating;
	int		philos_done_eating;

	ph = (t_Philo *)args;
	philos_done_eating = 0;
	while (ph->stime == 0)
		usleep(10);
	while (philos_done_eating < ph->nr_of_philos)
	{
		philo_id = 0;
		while (philo_id < ph->nr_of_philos)
		{
			time_since_eating = get_relative_time(ph) - ph->last_meal[philo_id];
			if (time_since_eating > ph->time_to_die)
				log_death_and_exit(ph, philo_id + 1);
			else if (ph->meals_eaten[philo_id] == ph->times_must_eat)
				philos_done_eating++;
			philo_id++;
		}
	}
	return (NULL);
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
	while (ph->stime == 0)
		usleep(100);
	while (repeat > 0)
	{
		pick_forks(ph, philo_id - 1);
		log_eat(ph, philo_id);
		if (VERBOSE)
			printf("%d ate at: %d\n", philo_id, ph->last_meal[philo_id - 1]);
		put_forks(ph, philo_id - 1);
		log_sleep(ph, philo_id);
		log_think(ph, philo_id);
		if (repeat < INT_MAX)
			repeat--;
	}
	ph->meals_eaten[philo_id] = ph->times_must_eat;
	return (NULL);
}

/*
 * Create a thread per philosopher calling start_philo()
 * Initialise print mutex
 * Sets time zero 
 * Wait for threads to finish and call pthread_join()
 */
void	create_threads(t_Philo *ph)
{
	pthread_t		*threads;
	int				i;
	int				errno;

	i = 0;
	threads = malloc((ph->nr_of_philos + 1) * sizeof(pthread_t));
	while (i <= ph->nr_of_philos)
	{
		if (i < ph->nr_of_philos)
			errno = pthread_create(&threads[i], NULL, &start_philo, ph);
		else
			errno = pthread_create(&threads[i], NULL, &start_watcher, ph);
		if (errno != 0 && VERBOSE > 0)
			printf("Thread creation failed\n");
		else
			if (VERBOSE > 1)
				printf("Thread %d created - id %d\n", i + 1, (int) threads[i]);
		pthread_mutex_init(&ph->mutex_print, NULL);
		if (i == ph->nr_of_philos)
			set_time_zero(ph);
		i++;
	}
	while (i-- > 0)
	{
		errno = pthread_join(threads[i], NULL);
		if (errno != 0 && VERBOSE > 0)
			printf("pthread_join() [%d] failed\n", i);
	}
	pthread_mutex_destroy(&ph->mutex_print);
	free(threads);
}

/*
 * Parse user input
// TODO validate_user_input(t_Philo);
 * Initilise philos struct 
 * Create all threads
 * Free memory allocated
 */
int	main(int argc, char **argv)
{
	int		error;
	t_Philo	philos;

	error = parse_user_input(argc, argv, &philos);
	if (error == 1)
		return (1);
	philos.philos_count = 1;
	philos.stime = 0;
	philos.last_meal = malloc(philos.nr_of_philos * sizeof(int));
	philos.meals_eaten = malloc(philos.nr_of_philos * sizeof(int));
	init_mutex_forks(&philos);
	create_threads(&philos);
	free(philos.last_meal);
	free(philos.meals_eaten);
	free_mutex_forks(&philos);
	if (VERBOSE > 0)
	{
		printf("All done eating %d time(s)\n", philos.times_must_eat);
		getchar();
	}
	return (0);
}
