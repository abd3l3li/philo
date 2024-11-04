/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:39:18 by abel-baz          #+#    #+#             */
/*   Updated: 2024/11/02 12:39:21 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_monitor(void *pointer)
{
	t_philo	*philos;

	philos = (t_philo *)pointer;
	while (1)
	{
		if (ru_starving(philos) || ru_full(philos))
			return (pointer);
	}
	return (pointer);
}

void	*philo_routine(void *pointer)
{
	t_philo	*philo;

	philo = (t_philo *)pointer;
	if (philo->id % 2 == 0)
		usleep(500);
	while (!catched(philo))
	{
		if (philo->num_philos == 1)
		{
			pthread_mutex_lock(philo->left_fork);
			print_message(philo, "has taken a fork");
			ft_usleep(philo->time_to_die, philo);
			pthread_mutex_unlock(philo->left_fork);
			return (NULL);
		}
		ft_eat(philo);
		ft_sleep(philo);
	}
	return (pointer);
}

int	start(t_vars *vars, pthread_mutex_t *forks)
{
	pthread_t	philo;
	int			i;

	if (pthread_create(&philo, NULL, &philo_monitor, vars->philos) != 0)
		clean_up("Error: thread creation", vars, forks);
	i = 0;
	while (i < vars->philos[0].num_philos)
	{
		if (pthread_create(&vars->philos[i].thread, NULL, &philo_routine,
				&vars->philos[i]) != 0)
			clean_up("Error: thread creation", vars, forks);
		i++;
	}
	i = 0;
	if (pthread_join(philo, NULL) != 0)
		clean_up("Error: thread join", vars, forks);
	while (i < vars->philos[0].num_philos)
	{
		if (pthread_join(vars->philos[i].thread, NULL) != 0)
			clean_up("Error: thread join", vars, forks);
		i++;
	}
	return (0);
}
