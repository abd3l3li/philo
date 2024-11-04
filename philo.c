/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:38:45 by abel-baz          #+#    #+#             */
/*   Updated: 2024/11/02 12:38:48 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	still_alive(t_philo *philo, size_t time_to_die)
{
	int	dead;

	pthread_mutex_lock(philo->eat_lock);
	if (philo->eating == 0 && ft_time() - philo->end > time_to_die)
		dead = 0;
	else
		dead = 1;
	pthread_mutex_unlock(philo->eat_lock);
	return (dead);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long long	result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
	{
		sign = -1;
		i++;
	}
	else if (str[i] == '+')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		if ((result * sign) > INT_MAX || (result * sign) < INT_MIN)
			return (-1);
		i++;
	}
	return (result * sign);
}

int	ft_isdigit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (0);
		i++;
	}
	return (1);
}

int	ft_checks(char **argv)
{
	int	i;

	i = 1;
	if (ft_atoi(argv[1]) > 200)
	{
		printf("\033[33mError: Too many philosophers\n");
		return (1);
	}
	while (argv[i])
	{
		if ((ft_atoi(argv[i]) <= 0) || (ft_isdigit(argv[i])) == 0)
		{
			if (ft_atoi(argv[i]) == -1)
				printf("\033[33mError: Integer overflow\n");
			else
				printf("\033[33mError: Invalid arguments\n");
			return (1);
		}
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_vars			*vars;
	t_philo			*philos;
	pthread_mutex_t	*forks;

	if (ac != 5 && ac != 6)
	{
		printf("\033[36mUsage: num_philosophers time_to_die time_to_eat "
			"time_to_sleep [num_meals](optional)\n");
		return (1);
	}
	if (ft_checks(av))
		return (1);
	vars = malloc(sizeof(t_vars));
	forks = malloc(sizeof(pthread_mutex_t) * ft_atoi(av[1]));
	philos = malloc(sizeof(t_philo) * ft_atoi(av[1]));
	init(vars, philos);
	init_forks(forks, ft_atoi(av[1]));
	init_philos(philos, vars, forks, av);
	start(vars, forks);
	clean_up(NULL, vars, forks);
	return (0);
}
