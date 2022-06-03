/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/06/03 18:12:51 by nlouro           ###   ########.fr       */
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

void	*start_watcher(void *args)
{
	t_Philo	*ph;
	int		philo_id;
	int		now;
	int		time_since_eating;
	int		serving;
	int		i;
	int		philos_done;

	ph = (t_Philo *)args;
	serving = 1;
	i = 0;
	philos_done = 0;
	while (ph->stime == 0)
		usleep(10);
	while (serving)
	{
		now = get_relative_time(ph);
		philo_id = 0;
		while (philo_id < ph->nr_of_philos)
		{
			time_since_eating = now - ph->last_meal[philo_id];
			if (time_since_eating > ph->time_to_die)
			{
				log_death(ph, philo_id + 1);
				philos_done++;
				exit(1);
			}
			else if (ph->meals_eaten[philo_id] == ph->times_must_eat)
				philos_done++;
			philo_id++;
		}
		if (philos_done == ph->nr_of_philos)
			serving = 0;
		//else
		//	usleep(10);
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
 * Parse user input
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
		if (i ==  ph->nr_of_philos)
			set_time_zero(ph);
		i++;
	}
	while (i-- > 0)
	{
		errno = pthread_join(threads[i], NULL);
		if (errno != 0 && VERBOSE > 0)
			printf("pthread_join() [%d] failed\n", i);
	}
	//TODO free threads
}

// TODO validate_user_input(t_Philo);
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
	//TODO: free philos->forks and mutexes
	getchar();
	return (0);
}
