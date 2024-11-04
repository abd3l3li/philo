/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:39:26 by abel-baz          #+#    #+#             */
/*   Updated: 2024/11/02 12:39:29 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_sleep(t_philo *philos)
{
	print_message(philos, "is sleeping");
	usleep(philos->time_to_sleep * 1000);
	print_message(philos, "is thinking");
	usleep(500);
}

void	to_be_continued(t_philo *philos)
{
	if (philos->id % 2 == 0)
	{
		pthread_mutex_lock(philos->left_fork);
		print_message(philos, "has taken a fork");
		pthread_mutex_lock(philos->right_fork);
		print_message(philos, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philos->right_fork);
		print_message(philos, "has taken a fork");
		pthread_mutex_lock(philos->left_fork);
		print_message(philos, "has taken a fork");
	}
}

void	ft_eat(t_philo *philos)
{
	to_be_continued(philos);
	pthread_mutex_lock(philos->eat_lock);
	philos->eating = 1;
	print_message(philos, "is eating");
	philos->end = ft_time();
	pthread_mutex_unlock(philos->eat_lock);
	ft_usleep(philos->time_to_eat, philos);
	pthread_mutex_lock(philos->eat_lock);
	philos->eating = 0;
	philos->meals++;
	pthread_mutex_unlock(philos->eat_lock);
	pthread_mutex_unlock(philos->right_fork);
	pthread_mutex_unlock(philos->left_fork);
}

int	ru_starving(t_philo *philos)
{
	int		i;

	i = 0;
	while (i < philos[0].num_philos)
	{
		if (!still_alive(&philos[i], philos[i].time_to_die))
		{
			print_message(&philos[i], "died");
			pthread_mutex_lock(philos[0].dead_lock);
			*philos->dead = 1;
			pthread_mutex_unlock(philos[0].dead_lock);
			return (1);
		}
		i++;
	}
	return (0);
}

int	ru_full(t_philo *philos)
{
	int	i;
	int	eaten;

	i = 0;
	eaten = 0;
	if (philos[0].num_times_to_eat == -1)
		return (0);
	while (i < philos[0].num_philos)
	{
		pthread_mutex_lock(philos[i].eat_lock);
		if (philos[i].meals >= philos[i].num_times_to_eat)
			eaten++;
		pthread_mutex_unlock(philos[i].eat_lock);
		i++;
	}
	if (eaten == philos[0].num_philos)
	{
		pthread_mutex_lock(philos[0].dead_lock);
		*philos->dead = 1;
		pthread_mutex_unlock(philos[0].dead_lock);
		return (1);
	}
	return (0);
}
