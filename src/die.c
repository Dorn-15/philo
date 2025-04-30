/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   die.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:32:37 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/11 12:20:10 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	is_died(long last_meal, int time_to_die)
{
	return (ft_get_time() - last_meal > time_to_die);
}

pthread_mutex_t	*get_die_mutex(void)
{
	static pthread_mutex_t	die_mutex;
	static int				init = 0;

	if (!init)
	{
		pthread_mutex_init(&die_mutex, NULL);
		init = 1;
	}
	return (&die_mutex);
}

int	should_die(int i)
{
	static pthread_mutex_t	*die_mutex;
	static int				die = 0;
	int						ret;

	if (i == -1)
	{
		die_mutex = get_die_mutex();
		return (0);
	}
	pthread_mutex_lock(die_mutex);
	if (i == 1)
		die = 1;
	ret = die;
	pthread_mutex_unlock(die_mutex);
	return (ret);
}
