/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:04:49 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/07 12:22:51 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	bad_args(int error)
{
	if (error == 1)
		printf("Error: Bad number of arguments: 4 or 5 are required\n");
	else if (error == -1 || error == 0)
		printf("Error: Not a positive number\n");
	else if (error == -2)
		printf("Error: Number is too big\n");
	printf("Usage: ./philo <number_of_philosophers> <time_to_die> <time_to_eat>"
		" <time_to_sleep> [number_of_times_each_philosopher_must_eat]\n");
	return (1);
}
