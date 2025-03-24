/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 12:38:53 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/24 17:03:06 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	print_philo(t_philo philo)
{
	printf("nb_philo: %d\n", philo.nb_philo);
	printf("time_to_die: %d\n", philo.time_to_die);
	printf("time_to_eat: %d\n", philo.time_to_eat);
	printf("time_to_sleep: %d\n", philo.time_to_sleep);
	printf("nb_eat: %d\n", philo.nb_eat);
}

int	main(int ac, char **av)
{
	t_philo	philo;

	if (ac < 5 || ac > 6)
		return (bad_args(1));
	philo = init_philo(av);
	if (philo.nb_philo <= 0)
		return (bad_args(philo.nb_philo));
	print_philo(philo);
	return (0);
}
