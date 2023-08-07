/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:21 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/14 12:40:29 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>

# define INT_OVERFLOW 1
# define NEGATIVE_NB 2
# define CONTAINS_ALPHA 3

typedef struct s_rules
{
	int	required_eat_count;
	int	amount;
	int	time_to_die;
	int	time_to_eat;
	int	time_to_sleep;
	int	starting_time;
	int	start_philos;
	pthread_mutex_t	start_philos_mutex;
}				t_rules;

typedef struct s_philosopher
{
	int				id;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	pthread_mutex_t	eating_count_mutex;
	pthread_mutex_t	last_meal_mutex;
	int				last_meal_time;
	int				eating_count;
	pthread_mutex_t	*print_mutex;
	pthread_mutex_t	*some_dead_mutex;
	int				*some_dead;
	t_rules			*rules;
}				t_philosopher;

typedef struct s_data
{
	t_philosopher	*philos;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	some_dead_mutex;
	int				some_dead;
	t_rules			rules;
}				t_data;

int				ft_atoi(char *str, int *status);
int				now(void);
t_philosopher	*get_philosopher_to_left(t_philosopher *curr);
void			wait_time(t_philosopher *philo, int time);
int				has_eaten_enough(t_philosopher *curr);

void			handle_mutex(pthread_mutex_t *mutex, int *data, int new_value);
int				start_threads(t_data *data);
int				join_threads(t_data *data);
int				is_everybody_alive(t_philosopher *curr);

void			*routine(void *args);

void			check_for_deads(t_philosopher *philos, t_rules *rules);

void			put_philosopher_status(t_philosopher *curr, char *status);
void			take_forks(t_philosopher *left, t_philosopher *curr);
void			put_philosopher_to_bed(t_philosopher *curr);
void			think(t_philosopher *curr);
void			eat(t_philosopher *left, t_philosopher *curr);

int				create_philos(t_data *data);
int				init_data(t_data *data, int argc, char **argv);

#endif