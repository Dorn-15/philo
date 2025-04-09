/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:38:53 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/09 18:16:47 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"
// proteger les forks avec un mutex
// utiliser valgrind --tool=helgrind --leak-check=full ./philo 5 800 200 200 10
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

static void	destroy_mutexes(pthread_mutex_t *forks,
	int nb_philo, pthread_mutex_t *print_mutex)
{
	int	i;

	i = 0;
	while (i < nb_philo)
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
	pthread_mutex_destroy(print_mutex);
}

static void	init_philo(t_data data)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*print_mutex;
	int				*someone_died;

	if (!init_resources(&philo, &forks, &someone_died, &print_mutex))
		return ;
	set_resources(philo, forks, someone_died, print_mutex);
	check_status(philo, data);
	join_threads(philo, data.nb_philo);
	destroy_mutexes(forks, data.nb_philo, print_mutex);
	free(print_mutex);
	free(someone_died);
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
		return (bad_args(2));
	if (data.time_to_die == 0)
		printf("0 1 died\n");
	else
		init_philo(data);
	return (0);
}
