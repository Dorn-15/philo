/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   status.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 18:57:15 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/08 19:05:31 by adoireau         ###   ########.fr       */
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
		if (is_died(philo[i].last_meal, time_to_die) && !philo[i].end_eat)
		{
			pthread_mutex_lock(philo[i].print_mutex);
			*philo[i].someone_died = 1;
			pthread_mutex_unlock(philo[i].print_mutex);
			print_status(philo[i].id, "died",
				philo[i].print_mutex, philo[i].someone_died);
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

void	check_status(t_philo *philo, t_data data)
{
	int	status;

	status = 0;
	while (!status)
	{
		usleep(10000);
		status = check_philos_status(philo, data.nb_philo, data.time_to_die);
	}
}
