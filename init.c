/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:38:11 by abel-baz          #+#    #+#             */
/*   Updated: 2024/11/02 12:38:14 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_input(t_philo *philo, char **args)
{
	philo->time_to_die = ft_atoi(args[2]);
	philo->time_to_eat = ft_atoi(args[3]);
	philo->time_to_sleep = ft_atoi(args[4]);
	philo->num_philos = ft_atoi(args[1]);
	if (args[5])
		philo->num_times_to_eat = ft_atoi(args[5]);
	else
		philo->num_times_to_eat = -1;
}

void	init_philos(t_philo *philos, t_vars *vars, pthread_mutex_t *forks,
		char **args)
{
	int	i;

	i = 0;
	while (i < ft_atoi(args[1]))
	{
		philos[i].id = i + 1;
		philos[i].eating = 0;
		philos[i].meals = 0;
		init_input(&philos[i], args);
		philos[i].dead = &vars->dead_flag;
		philos[i].print_lock = &vars->print_lock;
		philos[i].dead_lock = &vars->dead_lock;
		philos[i].eat_lock = &vars->eat_lock;
		philos[i].start = ft_time();
		philos[i].end = ft_time();
		philos[i].right_fork = &forks[i];
		if (i == 0)
			philos[i].left_fork = &forks[philos[i].num_philos - 1];
		else
			philos[i].left_fork = &forks[i - 1];
		i++;
	}
}

void	init(t_vars *vars, t_philo *philos)
{
	vars->dead_flag = 0;
	vars->philos = philos;
	pthread_mutex_init(&vars->print_lock, NULL);
	pthread_mutex_init(&vars->dead_lock, NULL);
	pthread_mutex_init(&vars->eat_lock, NULL);
}

void	init_forks(pthread_mutex_t *forks, int philo_num)
{
	int	i;

	i = 0;
	while (i < philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
}
