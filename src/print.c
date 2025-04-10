/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:49 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/10 17:34:04 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	bad_args(int error)
{
	if (error == 2)
		printf("Error: Number of philosophers is more than 200\n");
	if (error == 1)
		printf("Error: Bad number of arguments: 4 or 5 are required\n");
	if (error == 0)
		printf("Error: Not a positive number\n");
	if (error == -1)
		printf("Error: Number is too big\n");
	printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat>"
		" <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
	return (1);
}

static int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return (*s1 - *s2);
}

pthread_mutex_t	*get_print_mutex(void)
{
	static pthread_mutex_t	print_mutex;
	static int				init = 0;

	if (!init)
	{
		pthread_mutex_init(&print_mutex, NULL);
		init = 1;
	}
	return (&print_mutex);
}

void	print_status(int id, char *status)
{
	static pthread_mutex_t	*print_mutex;
	static long				start_time = 0;
	long					current_time;

	if (id == -1)
	{
		start_time = ft_get_time();
		print_mutex = get_print_mutex();
		return ;
	}
	current_time = ft_get_time();
	pthread_mutex_lock(print_mutex);
	if (!should_die(0) || !ft_strcmp(status, "died"))
		printf("%ld %d %s\n", current_time - start_time, id, status);
	pthread_mutex_unlock(print_mutex);
}
