/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher_states.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:35 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/15 15:26:36 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_philosopher_status(t_philosopher *curr, char *status)
{
	int	timestamp;

	pthread_mutex_lock(curr->print_mutex);
	if (is_everybody_alive(curr) && !has_eaten_enough(curr))
	{
		timestamp = now() - curr->rules->starting_time;
		printf("%d %d %s\n", timestamp, curr->id, status);
	}
	pthread_mutex_unlock(curr->print_mutex);
}

void	eat(t_philosopher *left, t_philosopher *curr)
{
	put_philosopher_status(curr, "is eating");
	pthread_mutex_lock(&(curr->eating_count_mutex));
	curr->eating_count += 1;
	pthread_mutex_unlock(&(curr->eating_count_mutex));
	pthread_mutex_lock(&(curr->last_meal_mutex));
	curr->last_meal_time = now();
	pthread_mutex_unlock(&(curr->last_meal_mutex));
	wait_time(curr, curr->rules->time_to_eat);
	// if (curr->id % 2 == 0)
	// {
		pthread_mutex_unlock(&(left->fork_mutex));
		pthread_mutex_unlock(&(curr->fork_mutex));
	// }
	// else
	// {
	// 	pthread_mutex_unlock(&(curr->fork_mutex));
	// 	pthread_mutex_unlock(&(left->fork_mutex));
	// }
}

void	think(t_philosopher *curr)
{
	put_philosopher_status(curr, "is thinking");
	usleep(1000);
}

void	put_philosopher_to_bed(t_philosopher *curr)
{
	put_philosopher_status(curr, "is sleeping");
	wait_time(curr, curr->rules->time_to_sleep);
}

void	take_forks(t_philosopher *left, t_philosopher *curr)
{
	if (curr->id % 2 == 0)
	{
		pthread_mutex_lock(&(left->fork_mutex));
		put_philosopher_status(curr, "has taken a fork");
		pthread_mutex_lock(&(curr->fork_mutex));
		put_philosopher_status(curr, "has taken a fork");
		return ;
	}
	pthread_mutex_lock(&(curr->fork_mutex));
	put_philosopher_status(curr, "has taken a fork");
	pthread_mutex_lock(&(left->fork_mutex));
	put_philosopher_status(curr, "has taken a fork");
}
