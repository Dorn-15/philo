/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:15 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:40 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	check_philos_status(t_philo *philo, int nb_philo, int time_to_die)
{
	int	i;
	int	finished;

	i = 0;
	finished = 0;
	while (i < nb_philo)
	{
		pthread_mutex_lock(get_eat_mutex(i));
		if (is_died(philo[i].last_meal, time_to_die) && !philo[i].end_eat)
		{
			pthread_mutex_unlock(get_eat_mutex(i));
			should_die(1);
			print_status(philo[i].id, "died");
			return (1);
		}
		if (philo[i].end_eat)
			finished++;
		pthread_mutex_unlock(get_eat_mutex(i));
		i++;
	}
	if (finished == nb_philo)
		return (2);
	return (0);
}

void	check_status(t_philo *philo, t_data data)
{
	int	status;

	status = 0;
	while (!status)
	{
		ft_usleep(5);
		status = check_philos_status(philo, data.nb_philo, data.time_to_die);
	}
}
