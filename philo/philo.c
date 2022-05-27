/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/27 10:14:35 by nlouro           ###   ########.fr       */
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
	else
		//TODO: handle case
		philos->nr_of_times_philo_must_eat = INT_MAX;
	return (0);
}

void	init_mutex_forks(t_Philo *philos)
{
	int	i;
	pthread_mutex_t	mutexes[philos->nr_of_philos];

	i = 0;
	philos->forks_ar = malloc(philos->nr_of_philos * sizeof(pthread_mutex_t));
	while (i < philos->nr_of_philos)
	{
		//printf("fork i=%d initialised\n", i);
		pthread_mutex_init(&mutexes[i], NULL);
		philos->forks_ar[i] = mutexes[i];
		i++;
	}
}

void *start_philo(void *args)
{
	t_Philo *ph;
	int	philo_id;
	int	repeat;

	ph = (t_Philo *)args;
	repeat = ph->nr_of_times_philo_must_eat;
	philo_id = ph->philo_id++;
	//ph->philo_id++;
	while (repeat > 0)
	{
		pick_forks(ph, philo_id - 1);
		log_take_fork(ph->stime, philo_id);
		log_eat(ph->stime, philo_id);
		usleep(ph->time_to_eat);
		put_forks(ph, philo_id - 1);
		log_put_fork(ph->stime, philo_id);
		log_sleep(ph->stime, philo_id);
		usleep(ph->time_to_sleep);
		log_think(ph->stime, philo_id);
		if (repeat < INT_MAX)
			repeat--;
	}
	return (NULL);
}

void	create_threads(t_Philo *philos)
{
	pthread_t	threads[philos->nr_of_philos];
	struct	timeval current_time;
	int		i;
	int		errno;

	i = 0;
	gettimeofday(&current_time, NULL);
	philos->stime = current_time.tv_usec;
	// Create a thread per philosopher calling start_philo()
	while (i < philos->nr_of_philos)
	{
		errno = pthread_create(&threads[i], NULL, &start_philo, philos);
		if (errno != 0)
	    	printf("Thread creation failed\n");
		//else
		//    printf("Thread %d created with id %d\n", i+1, (int) threads[i]);
		i++;
	}
	// Wait for threads to finish
	while (i-- > 0)
    {
        if (0 != (errno = pthread_join(threads[i], NULL))) {
            printf("pthread_join() [%d] failed\n", i);
            //return (1);
        }
		//else
        //    printf("pthread_join() [%d] ok\n", i);
    }
}

int	main(int argc, char **argv)
{
	int	error;
	t_Philo	philos;

	error = parse_user_input(argc, argv, &philos);
	philos.philo_id = 1;
	init_mutex_forks(&philos);
	// TODO validate_user_input(t_Philo);
	if (error == 1)
		return (1);
	create_threads(&philos);
	return (0);
}
