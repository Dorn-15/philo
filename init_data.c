/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:31 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/26 17:06:14 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	result;

	i = 0;
	sign = 1;
	result = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9' && result < 2147483647)
		result = result * 10 + (str[i++] - '0');
	if (result > 2147483647)
		return (-2);
	return ((int)(result * sign));
}

static int	ft_isdigit(char *str)
{
	int	i;
	int	bool;

	i = 0;
	bool = 0;
	if (!str || !str[i])
		return (0);
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	while (str[i] && str[i] >= '0' && str[i] <= '9')
	{
		bool = 1;
		i++;
	}
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] || bool == 0)
		return (0);
	return (1);
}

static t_data	init_data(char **av)
{
	int		i;
	t_data	data;

	i = 1;
	while (av[i])
	{
		if (!ft_isdigit(av[i]))
		{
			data.nb_philo = -1;
			return (data);
		}
		i++;
	}
	data.nb_philo = ft_atoi(av[1]);
	data.time_to_die = ft_atoi(av[2]);
	data.time_to_eat = ft_atoi(av[3]);
	data.time_to_sleep = ft_atoi(av[4]);
	if (av[5])
		data.nb_eat = ft_atoi(av[5]);
	else
		data.nb_eat = -1;
	if (data.nb_philo < 0 || data.time_to_die < 0
		|| data.time_to_eat < 0 || data.time_to_sleep < 0 || data.nb_eat < -1)
		data.nb_philo = -2;
	return (data);
}

t_data	get_data(char **av)
{
	static t_data	data;
	static int		initialized = 0;

	if (!initialized)
	{
		data = init_data(av);
		initialized = 1;
	}
	return (data);
}
