/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adoireau <adoireau@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 14:40:17 by adoireau          #+#    #+#             */
/*   Updated: 2025/04/10 16:44:16 by adoireau         ###   ########.fr       */
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
	pthread_t		thread;
	int				id;
	long			last_meal;
	int				end_eat;
	int				meals_eaten;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
}	t_philo;

//print.c
int				bad_args(int error);
pthread_mutex_t	*get_print_mutex(void);
void			print_status(int id, char *status);

//init_data.c
t_data			get_data(char **av);

//init_philo.c
int				init_resources(t_philo **philo, pthread_mutex_t **forks);
void			set_resources(t_philo *philo, pthread_mutex_t *forks);

//routine.c
void			*routine(void *arg);

//status.c
void			check_status(t_philo *philo, t_data data);

//utile.c
long			ft_get_time(void);
void			ft_usleep(long time);
pthread_mutex_t	*get_eat_mutex(int nb_philo);
//die.c
int				is_died(long last_meal, int time_to_die);
int				should_die(int i);
pthread_mutex_t	*get_die_mutex(void);

#endif
