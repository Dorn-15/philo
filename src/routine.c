/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:00:03 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/09 17:39:17 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	take_forks(t_philo *philo, int id)
{
	if (*philo->someone_died)
		return (1);
	if (philo->id % 2 == 0 || philo->id == id)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->id, "has taken a lp fork",
			philo->print_mutex, philo->someone_died);
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->id, "has taken a rp fork",
			philo->print_mutex, philo->someone_died);
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		print_status(philo->id, "has taken a ri fork",
			philo->print_mutex, philo->someone_died);
		pthread_mutex_lock(philo->left_fork);
		print_status(philo->id, "has taken a li fork",
			philo->print_mutex, philo->someone_died);
	}
	return (0);
}

static int	handle_eating(t_philo *philo, t_data *data)
{
	if (take_forks(philo, data->nb_philo))
		return (1);
	philo->last_meal = ft_get_time();
	print_status(philo->id, "is eating",
		philo->print_mutex, philo->someone_died);
	usleep(data->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	return (0);
}

static int	handle_sleep_think(t_philo *philo, t_data *data)
{
	if (*philo->someone_died)
		return (1);
	print_status(philo->id, "is sleeping",
		philo->print_mutex, philo->someone_died);
	usleep(data->time_to_sleep * 1000);
	if (*philo->someone_died)
		return (1);
	print_status(philo->id, "is thinking",
		philo->print_mutex, philo->someone_died);
	if (data->nb_philo % 2 != 0 && data->time_to_sleep < data->time_to_eat)
		usleep(1000 * (data->time_to_eat - data->time_to_sleep + 1));
	return (0);
}

void	*routine(void *arg)
{
	t_philo	*philo;
	t_data	data;

	philo = (t_philo *)arg;
	data = get_data(NULL);
	philo->last_meal = ft_get_time();
	philo->meals_eaten = 0;
	if (philo->id % 2 == 0)
		usleep(800 * data.time_to_eat);
	else if (philo->id == data.nb_philo)
		usleep(500 * data.time_to_eat);
	while (!(*philo->someone_died)
		&& (philo->meals_eaten < data.nb_eat || data.nb_eat == -1))
	{
		if (handle_eating(philo, &data))
			break ;
		if (handle_sleep_think(philo, &data))
			break ;
		if (data.nb_eat > 0)
			philo->meals_eaten++;
	}
	philo->end_eat = 1;
	return (NULL);
}
