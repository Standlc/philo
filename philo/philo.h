/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:28:21 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/10 18:09:50 by stde-la-         ###   ########.fr       */
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
	int				time;
	int				required_eating_amount;
	pthread_t		starving_thread;
	pthread_mutex_t	starving_mutex;

}				t_philosopher;

typedef struct s_data
{
	t_philosopher	*philosophers;
	int 			philosophers_amount;
	int				time;
}				t_data;

#endif