/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:40:17 by adoireau          #+#    #+#             */
/*   Updated: 2025/03/26 17:06:13 by adoireau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>

typedef struct s_data
{
	int		nb_philo;
	int		time_to_die;
	int		time_to_eat;
	int		time_to_sleep;
	int		nb_eat;
}	t_data;

typedef struct s_philo
{
	int		id;
	pthread_t	thread;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	long			last_meal;
	int				end_eat;
	int				meals_eaten;
}	t_philo;

//error.c
int		bad_args(int error);

//init_data.c
t_data	get_data(char **av);

//utile.c
long	ft_get_time(void);
int		is_died(long last_meal, int time_to_die);
void	print_status(int id, char *status);

#endif
