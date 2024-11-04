/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abel-baz <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 12:39:01 by abel-baz          #+#    #+#             */
/*   Updated: 2024/11/02 12:39:09 by abel-baz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <limits.h>

# define NUM 255

typedef struct s_philo
{
	int				id;
	int				eating;
	int				meals;
	int				num_philos;
	int				num_times_to_eat;
	int				*dead;
	pthread_t		thread;
	pthread_mutex_t	*right_fork;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*print_lock;
	pthread_mutex_t	*dead_lock;
	pthread_mutex_t	*eat_lock;
	size_t			end;
	size_t			start;
	size_t			time_to_die;
	size_t			time_to_eat;
	size_t			time_to_sleep;
}					t_philo;

typedef struct s_vars
{
	int				dead_flag;
	pthread_mutex_t	dead_lock;
	pthread_mutex_t	eat_lock;
	pthread_mutex_t	print_lock;
	t_philo			*philos;
}					t_vars;

/*init.c*/
void				init_input(t_philo *philo, char **args);
void				init_philos(t_philo *philos, t_vars *vars,
						pthread_mutex_t *forks, char **args);
void				init(t_vars *vars, t_philo *philos);
void				init_forks(pthread_mutex_t *forks, int philo_num);

/*thread.c*/
void				*philo_routine(void *pointer);
int					catched(t_philo *philo);
int					start(t_vars *vars, pthread_mutex_t *forks);

/*utils.c*/
size_t				ft_time(void);
void				clean_up(char *str, t_vars *vars,
						pthread_mutex_t *forks);
int					ft_usleep(size_t milliseconds, t_philo *philo);
int					ft_atoi(char *str);
void				print_message(t_philo *philo, char *str);

/*thread_utils.c*/
void				ft_eat(t_philo *philos);
void				ft_sleep(t_philo *philos);
int					still_alive(t_philo *philo, size_t time_to_die);
int					ru_starving(t_philo *philos);
int					ru_full(t_philo *philos);

#endif
