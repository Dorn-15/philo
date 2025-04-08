/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:38:53 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/07 16:19:54 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	take_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->id, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->id, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->id, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->id, "has taken a fork");
	}
	return (0);
}

static int	handle_eating(t_philo *philo, t_data *data)
{
	take_forks(philo);
	philo->last_meal = ft_get_time();
	print_status(philo->id, "is eating");
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static void	handle_sleep_think(t_philo *philo, t_data *data)
{
	print_status(philo->id, "is sleeping");
	usleep(data->time_to_sleep * 1000);
	print_status(philo->id, "is thinking");
}

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	data;

	philo = (t_philo *)arg;
	data = get_data(NULL);
	philo->last_meal = ft_get_time();
	if (philo->id % 2 == 0)
		usleep(1000 * (data.time_to_eat / 2));
	else if (philo->id == data.nb_philo)
		usleep(1000 * data.time_to_eat / 4);
	while (philo->meals_eaten < data.nb_eat || data.nb_eat == -1)
	{
		handle_eating(philo, &data);
		handle_sleep_think(philo, &data);
		if (data.nb_eat > 0)
			philo->meals_eaten++;
	}
	philo->end_eat = 1;
	return (NULL);
}

static void	init_forks(t_philo *philo, int i, int nb_philo, pthread_mutex_t *forks)
{
	philo[i].id = i + 1;
	philo[i].end_eat = 0;
	philo[i].meals_eaten = 0;
	philo[i].right_fork = &forks[i];
	
	if (i == nb_philo - 1 && nb_philo != 1)
		philo[i].left_fork = &forks[0];
	else
		philo[i].left_fork = &forks[i + 1];
}

static int	check_philos_status(t_philo *philo, int nb_philo, int time_to_die)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < nb_philo)
	{
		if (is_died(philo[i].last_meal, time_to_die) && !philo[i].end_eat)
		{
			print_status(philo[i].id, "died");
			return (1);
		}
		if (philo[i].end_eat)
			finished++;
		i++;
	}
	if (finished == nb_philo)
		return (2);
	return (0);
}

static void	join_threads(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
}

static void	destroy_mutexes(pthread_mutex_t *forks, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

static int	init_resources(t_philo **philo, pthread_mutex_t **forks, t_data data)
{
	*philo = malloc(sizeof(t_philo) * data.nb_philo);
	if (!*philo)
		return (0);
	if (data.nb_philo == 1)
		*forks = malloc(sizeof(pthread_mutex_t) * 2);
	else
		*forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	if (!*forks)
	{
		free(*philo);
		return (0);
	}
	return (1);
}

static void	init_philo(t_data data)
{
	int		i;
	int		die;
	t_philo	*philo;
	pthread_mutex_t *forks;

	if (!init_resources(&philo, &forks, data))
		return;
	i = -1;
	while (++i < data.nb_philo)
		pthread_mutex_init(&forks[i], NULL);
	i = -1;
	while (++i < data.nb_philo)
		init_forks(philo, i, data.nb_philo, forks);
	i = -1;
	while (++i < data.nb_philo)
		pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
	while (1)
	{
		usleep(data.time_to_die * 1000 / 2);
		die = check_philos_status(philo, data.nb_philo, data.time_to_die);
		if (die)
			break;
	}
	if (die == 2)
		join_threads(philo, data.nb_philo);
	destroy_mutexes(forks, data.nb_philo);
	free(forks);
	free(philo);
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (bad_args(1));
	data = get_data(av);
	if (data.nb_philo <= 0)
		return (bad_args(data.nb_philo));
	if (data.nb_philo > 200)
		return (bad_args(-2));
	init_philo(data);
	return (0);
}
