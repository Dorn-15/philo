/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:38:53 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/10 17:19:12 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static void	join_threads(t_philo *philo, int nb_philo)
{
	int	i;

	i = 0;
	while (i < nb_philo)
		pthread_join(philo[i++].thread, NULL);
	free(philo);
}

static void	destroy_mutexes(pthread_mutex_t *forks, int nb_philo)
{
	int				i;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*die_mutex;
	pthread_mutex_t	*eat_mutex;

	print_mutex = get_print_mutex();
	die_mutex = get_die_mutex();
	eat_mutex = get_eat_mutex(-1);
	i = 0;
	while (i < nb_philo)
		pthread_mutex_destroy(&forks[i++]);
	i = 0;
	while (i < nb_philo)
		pthread_mutex_destroy(&eat_mutex[i++]);
	pthread_mutex_destroy(print_mutex);
	pthread_mutex_destroy(die_mutex);
	free(eat_mutex);
	free(forks);
}

static void	init_philo(t_data data)
{
	t_philo			*philo;
	pthread_mutex_t	*forks;

	if (!init_resources(&philo, &forks))
		return ;
	set_resources(philo, forks);
	check_status(philo, data);
	join_threads(philo, data.nb_philo);
	destroy_mutexes(forks, data.nb_philo);
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
