/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlouro <nlouro@student.42heilbronn.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 12:34:25 by nlouro            #+#    #+#             */
/*   Updated: 2022/05/26 16:47:17 by nlouro           ###   ########.fr       */
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

void *start_philo(void *args)
{
	t_Philo *ph;
	int	philo_id;
	int	repeat;

	ph = (t_Philo *)args;
	repeat = ph->nr_of_times_philo_must_eat;
	//FIXME
	philo_id = 1;
	//printf("nr_of_philos: %d\n", ph->nr_of_philos);
	while (repeat > 0)
	{
		//TODO: get forks
		log_take_fork(ph->stime, philo_id);
		log_eat(ph->stime, philo_id);
		usleep(ph->time_to_eat);
		//TODO: put forks
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

	error = parse_user_input(argc, argv, &philos);
	init_forks(&philos);
	// TODO validate_user_input(t_Philo);
	if (error == 1)
		return (1);
	gettimeofday(&current_time, NULL);
	printf("seconds : %ld micro seconds : %d\n", current_time.tv_sec, current_time.tv_usec);
	philos.stime = current_time.tv_sec;
	create_threads(&philos);
	return (0);
}
