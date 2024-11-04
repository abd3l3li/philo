/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:39:50 by abel-baz          #+#    #+#             */
/*   Updated: 2024/11/02 12:40:14 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_message(t_philo *philo, char *str)
{
	pthread_mutex_lock(philo->print_lock);
	if (!catched(philo))
		printf("%ld %d %s\n", ft_time() - philo->start, philo->id,
			str);
	pthread_mutex_unlock(philo->print_lock);
}

int	catched(t_philo *philo)
{
	pthread_mutex_lock(philo->dead_lock);
	if (*philo->dead == 1)
		return (pthread_mutex_unlock(philo->dead_lock), 1);
	pthread_mutex_unlock(philo->dead_lock);
	return (0);
}

void	clean_up(char *str, t_vars *vars, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	if (str)
		printf("%s\n", str);
	if (&vars->print_lock)
		pthread_mutex_destroy(&vars->print_lock);
	if (&vars->eat_lock)
		pthread_mutex_destroy(&vars->eat_lock);
	if (&vars->dead_lock)
		pthread_mutex_destroy(&vars->dead_lock);
	while (i < vars->philos[0].num_philos)
	{
		if (&forks[i])
			pthread_mutex_destroy(&forks[i]);
		i++;
	}
	if (forks)
		free(forks);
	if (vars->philos)
		free(vars->philos);
	if (vars)
		free(vars);
}

int	ft_usleep(size_t milliseconds, t_philo *philo)
{
	size_t	start;

	start = ft_time();
	while ((ft_time() - start) < milliseconds && !catched(philo))
		usleep(60);
	return (0);
}

size_t	ft_time(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL) == -1)
		printf("Error: gettimeofday\n");
	return (time.tv_sec * 1000 + time.tv_usec / 1000);
}
