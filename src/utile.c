/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:32:37 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/07 15:30:26 by adoireau         ###   ########.fr       */
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

int	is_died(long last_meal, int time_to_die)
{
	return (ft_get_time() - last_meal > time_to_die);
}

void	print_status(int id, char *status)
{
	static pthread_mutex_t print_mutex = PTHREAD_MUTEX_INITIALIZER;
	
	pthread_mutex_lock(&print_mutex);
	printf("%ld %d %s\n", ft_get_time(), id, status);
	pthread_mutex_unlock(&print_mutex);
}
