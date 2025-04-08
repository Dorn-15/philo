/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utile.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:32:37 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/08 19:15:53 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

long	ft_get_time(void)
{
	struct timeval	now;
	long			time;

	time = 0;
	if (gettimeofday(&now, NULL) == -1)
		return (0);
	time = (now.tv_sec * 1000) + (now.tv_usec / 1000);
	return (time);
}

int	is_died(long last_meal, int time_to_die)
{
	long	current_time;

	current_time = ft_get_time();
	return (current_time - last_meal > time_to_die);
}

void	print_status(int id, char *status,
	pthread_mutex_t *print_mutex, int *someone_died)
{
	static long	start_time = 0;
	long		current_time;

	if (start_time == 0)
		start_time = ft_get_time();
	current_time = ft_get_time();
	pthread_mutex_lock(print_mutex);
	if (!*someone_died || !ft_strcmp(status, "died"))
		printf("%ld %d %s\n", current_time - start_time, id, status);
	pthread_mutex_unlock(print_mutex);
}
