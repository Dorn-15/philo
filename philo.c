/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:38:53 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/25 17:16:19 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	get_time(void)
{
	struct timeval	now;

	gettimeofday(&now, NULL);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

static int	is_died(long last_meal, int time_to_die)
{
	return (get_time() - last_meal > time_to_die);
}

static void	print_status(int id, char *status)
{
	printf("%ld %d %s\n", get_time(), id, status);
}

static int	handle_eating(t_philo *philo, t_data *data)
{
	pthread_mutex_lock(&philo->left_fork);
	pthread_mutex_lock(&philo->right_fork);
	print_status(philo->id, "has taken fork");
	if (is_died(philo->last_meal, data->time_to_die))
	{
		print_status(philo->id, "is dead");
		return (1);
	}
	print_status(philo->id, "is eating");
	philo->last_meal = get_time();
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(&philo->right_fork);
	pthread_mutex_unlock(&philo->left_fork);
	return (0);
}

static void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	data;

	philo = (t_philo *)arg;
	data = get_data(NULL);
	philo->last_meal = get_time();
	usleep((data.time_to_eat * 1000) * philo->id % 2);

	while (1)
	{
		if (handle_eating(philo, &data))
			break;
		print_status(philo->id, "is sleeping");
		usleep(data.time_to_sleep * 1000);
		if (data.nb_eat > 0)
			data.nb_eat--;
		else if (data.nb_eat != -1)
			return (NULL);
	}
	print_status(philo->id, "is dead");
	exit(0);
	return (NULL);
}

static void	init_forks(t_philo *philo, int i, int nb_philo)
{
	philo[i].id = i + 1;
	if (i == 0)
		pthread_mutex_init(&philo[i].left_fork, NULL);
	else
		philo[i].left_fork = philo[i - 1].right_fork;
	if (i + 1 < nb_philo || nb_philo == 1)
		pthread_mutex_init(&philo[i].right_fork, NULL);
	else
		philo[i].right_fork = philo[0].left_fork;
}

static void	init_philo(t_data data)
{
	int		i;
	t_philo	philo[data.nb_philo];

	i = 0;
	while (i < data.nb_philo)
	{
		init_forks(philo, i, data.nb_philo);
		pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
		i++;
	}
	i = 0;
	while (i < data.nb_philo)
		pthread_join(philo[i++].thread, NULL);
	i = 0;
	while (i < data.nb_philo)
	{
		pthread_mutex_destroy(&philo[i].left_fork);
		pthread_mutex_destroy(&philo[i].right_fork);
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (ac < 5 || ac > 6)
		return (bad_args(1));
	data = get_data(av);
	if (data.nb_philo <= 0)
		return (bad_args(data.nb_philo));
	init_philo(data);
	return (0);
}
