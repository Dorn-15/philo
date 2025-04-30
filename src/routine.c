/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:00:03 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/11 13:01:44 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	pthread_mutex_lock(fork);
	print_status(philo->id, "has taken a fork");
	if (should_die(0))
	{
		pthread_mutex_unlock(fork);
		return (1);
	}
	return (0);
}

static int	take_forks(t_philo *philo, int id)
{
	pthread_mutex_t	*first_fork;
	pthread_mutex_t	*second_fork;

	if (philo->id % 2 == 0 || philo->id == id)
	{
		first_fork = philo->left_fork;
		second_fork = philo->right_fork;
	}
	else
	{
		first_fork = philo->right_fork;
		second_fork = philo->left_fork;
	}
	if (take_fork(philo, first_fork))
		return (1);
	if (take_fork(philo, second_fork))
	{
		pthread_mutex_unlock(first_fork);
		return (1);
	}
	return (0);
}

static int	handle_eating(t_philo *philo, t_data *data)
{
	if (take_forks(philo, data->nb_philo) || should_die(0))
		return (1);
	pthread_mutex_lock(get_eat_mutex(philo->id - 1));
	philo->last_meal = ft_get_time();
	pthread_mutex_unlock(get_eat_mutex(philo->id - 1));
	print_status(philo->id, "is eating");
	ft_usleep(data->time_to_eat);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static int	handle_sleep_think(t_philo *philo, t_data *data)
{
	print_status(philo->id, "is sleeping");
	ft_usleep(data->time_to_sleep);
	print_status(philo->id, "is thinking");
	if (data->nb_philo != 1)
	{
		if (data->nb_philo % 2 == 0 && data->time_to_sleep < data->time_to_eat)
			ft_usleep(data->time_to_eat - data->time_to_eat);
		else if (data->nb_philo % 2 != 0
			&& data->time_to_sleep <= data->time_to_eat)
			ft_usleep(data->time_to_eat - data->time_to_sleep + 1);
	}
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	data;

	philo = (t_philo *)arg;
	data = get_data(NULL);
	if (philo->id % 2 == 0)
		ft_usleep(0.8 * data.time_to_eat);
	else if (philo->id == data.nb_philo && data.nb_philo != 1)
		ft_usleep(0.5 * data.time_to_eat);
	while ((philo->meals_eaten < data.nb_eat || data.nb_eat == -1)
		&& !should_die(0))
	{
		if (handle_eating(philo, &data))
			break ;
		handle_sleep_think(philo, &data);
		if (data.nb_eat > 0)
			philo->meals_eaten++;
	}
	pthread_mutex_lock(get_eat_mutex(philo->id - 1));
	philo->end_eat = 1;
	pthread_mutex_unlock(get_eat_mutex(philo->id - 1));
	return (NULL);
}
