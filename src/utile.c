/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:32:37 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/10 17:28:35 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

long	ft_get_time(void)
{
	struct timeval	now;

	if (gettimeofday(&now, NULL) == -1)
		return (0);
	return ((now.tv_sec * 1000) + (now.tv_usec / 1000));
}

void	ft_usleep(long time)
{
	long	start;

	start = ft_get_time();
	while (ft_get_time() - start < time)
		usleep(100);
}

pthread_mutex_t	*get_eat_mutex(int nb_philo)
{
	static pthread_mutex_t	*eat_mutex = NULL;
	int						i;

	if (!eat_mutex && nb_philo > 0)
	{
		eat_mutex = malloc(sizeof(pthread_mutex_t) * nb_philo);
		i = 0;
		while (i < nb_philo)
			pthread_mutex_init(&eat_mutex[i++], NULL);
		return (NULL);
	}
	if (nb_philo == -1)
		return (eat_mutex);
	return (&eat_mutex[nb_philo]);
}
