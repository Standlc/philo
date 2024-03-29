/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:35 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 13:06:57 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philosopher *left, t_philosopher *curr)
{
	put_philosopher_status(curr, "is eating");
	count_philo_meals(curr);
	pthread_mutex_lock(&(curr->last_meal_mutex));
	curr->last_meal_time = now();
	pthread_mutex_unlock(&(curr->last_meal_mutex));
	wait_time(curr, curr->rules->time_to_eat);
	give_forks_back(left, curr);
}

void	think(t_philosopher *curr)
{
	put_philosopher_status(curr, "is thinking");
	usleep(500);
}

void	put_philosopher_to_bed(t_philosopher *curr)
{
	put_philosopher_status(curr, "is sleeping");
	wait_time(curr, curr->rules->time_to_sleep);
}

void	take_fork(t_philosopher *curr, pthread_mutex_t *fork_mutex)
{
	pthread_mutex_lock(fork_mutex);
	put_philosopher_status(curr, "has taken a fork");
}

void	take_forks(t_philosopher *left, t_philosopher *curr)
{
	if (curr->id % 2 == 0)
	{
		take_fork(curr, &(left->fork_mutex));
		take_fork(curr, &(curr->fork_mutex));
		return ;
	}
	take_fork(curr, &(curr->fork_mutex));
	take_fork(curr, &(left->fork_mutex));
}
