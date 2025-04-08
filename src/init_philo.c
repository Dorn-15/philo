/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:17:01 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/08 19:54:57 by adoireau         ###   ########.fr       */
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
	if (i == nb_philo - 1)
	{
		philo[i].right_fork = &forks[0];
	}
	else
	{
		philo[i].right_fork = &forks[i + 1];
	}
}

void	set_resources(t_philo *philo, pthread_mutex_t *forks,
	int *someone_died, pthread_mutex_t *print_mutex)
{
	int		i;
	t_data	data;

	data = get_data(NULL);
	*someone_died = 0;
	pthread_mutex_init(print_mutex, NULL);
	i = -1;
	while (++i < data.nb_philo)
		pthread_mutex_init(&forks[i], NULL);
	i = 0;
	while (i < data.nb_philo)
	{
		philo[i].someone_died = someone_died;
		philo[i].print_mutex = print_mutex;
		init_forks(philo, i, data.nb_philo, forks);
		i++;
	}
	i = -1;
	while (++i < data.nb_philo)
		pthread_create(&philo[i].thread, NULL, routine, (void *)&philo[i]);
}

int	init_resources(t_philo **philo, pthread_mutex_t **forks,
	int **someone_died, pthread_mutex_t **print_mutex)
{
	t_data	data;

	data = get_data(NULL);
	*philo = malloc(sizeof(t_philo) * data.nb_philo);
	*forks = malloc(sizeof(pthread_mutex_t) * data.nb_philo);
	*someone_died = malloc(sizeof(int));
	*print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!*philo || !*forks || !*someone_died || !*print_mutex)
	{
		if (*philo)
			free(*philo);
		if (*forks)
			free(*forks);
		if (*someone_died)
			free(*someone_died);
		if (*print_mutex)
			free(*print_mutex);
		return (0);
	}
	return (1);
}
