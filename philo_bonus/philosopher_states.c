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

	// pthread_mutex_lock(curr->print_mutex);
	timestamp = now() - curr->rules->starting_time;
	if (!curr->rules->some_dead)
		printf("%d %d %s\n", timestamp, curr->id, status);
	// pthread_mutex_unlock(curr->print_mutex);
}

void	eat(t_philosopher *left, t_philosopher *curr)
{
	curr->is_thinking = 0;
	curr->eating_count++;
	curr->last_meal_time = now();
	put_philosopher_status(curr, "is eating");
	wait(curr->rules->time_to_eat);
	// pthread_mutex_unlock(&(left->fork_mutex));
	// pthread_mutex_unlock(&(curr->fork_mutex));
}

void	think(t_philosopher *curr)
{
	if (!curr->is_thinking)
		put_philosopher_status(curr, "is thinking");
	curr->is_thinking = 1;
}

void	put_philosopher_to_bed(t_philosopher *curr)
{
	put_philosopher_status(curr, "is sleeping");
	wait(curr->rules->time_to_sleep);
}

void	take_forks(t_philosopher *left, t_philosopher *curr)
{
	// pthread_mutex_lock(&(left->fork_mutex));
	// pthread_mutex_lock(&(curr->fork_mutex));
	put_philosopher_status(curr, "has taken a fork");
	put_philosopher_status(curr, "has taken a fork");
}
