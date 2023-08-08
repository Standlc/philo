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
	wait_time(curr, 0.5);
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
