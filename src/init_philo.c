/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:17:01 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/10 17:22:28 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	init_forks(t_philo *philo, int i,
	int nb_philo, pthread_mutex_t *forks)
{
	philo[i].id = i + 1;
	philo[i].end_eat = 0;
	philo[i].meals_eaten = 0;
	philo[i].left_fork = &forks[i];
	if (i == nb_philo - 1 && nb_philo != 1)
		philo[i].right_fork = &forks[0];
	else
		philo[i].right_fork = &forks[i + 1];
}

void	set_resources(t_philo *philo, pthread_mutex_t *forks)
{
	int		i;
	long	last_meal;
	t_data	data;

	data = get_data(NULL);
	last_meal = ft_get_time();
	i = -1;
	while (++i < data.nb_philo || i < 2)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < data.nb_philo)
	{
		philo[i].last_meal = last_meal;
		init_forks(philo, i, data.nb_philo, forks);
		pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
		i++;
	}
}

int	init_resources(t_philo **philo, pthread_mutex_t **forks)
{
	t_data	data;

	data = get_data(NULL);
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
	get_eat_mutex(data.nb_philo);
	print_status(-1, "");
	should_die(-1);
	return (1);
}
