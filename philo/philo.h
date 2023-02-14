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

typedef struct s_philosopher
{
	int				id;
	int				fork;
	pthread_t		thread;
	pthread_mutex_t	fork_mutex;
	int 			philosophers_amount;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				is_alive;
	int				is_thinking;
	int				last_meal_time;
	int				starting_time;
	int				now;
	int				timestamps;
	int				required_eating_amount;
}				t_philosopher;

typedef struct s_data
{
	t_philosopher	*philosophers;
	int 			philosophers_amount;
	int				now;
	int				starting_time;
}				t_data;

int				ft_atoi(char *str);
void			free_philosophers(t_philosopher *philosophers, int size);
int				now(void);
t_philosopher	*get_philosopher_to_left(t_philosopher *curr);

void			*routine(void *args);

#endif