/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_deads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:26 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/15 15:26:27 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_eating_counts(t_philosopher *philos, t_rules *rules)
{
	int	i;

	if (rules->required_eat_count == -1)
		return (1);
	i = 0;
	while (i < rules->amount)
	{
		pthread_mutex_lock(&(philos[i].eating_count_mutex));
		if (philos[i].eating_count < rules->required_eat_count)
		{
			pthread_mutex_unlock(&(philos[i].eating_count_mutex));
			return (1);
		}
		pthread_mutex_unlock(&(philos[i].eating_count_mutex));
		i++;
	}
	return (0);
}

int	get_time_since_last_meal(t_philosopher *curr)
{
	int	result;

	pthread_mutex_lock(&(curr->last_meal_mutex));
	result = now() - curr->last_meal_time;
	pthread_mutex_unlock(&(curr->last_meal_mutex));
	return (result);
}

void	handle_philo_death(t_philosopher *curr)
{
	int	timestamp;

	pthread_mutex_lock(curr->some_dead_mutex);
	*(curr->some_dead) = 1;
	pthread_mutex_unlock(curr->some_dead_mutex);
	timestamp = now() - curr->rules->starting_time;
	pthread_mutex_lock(curr->print_mutex);
	printf("%d %d %s\n", timestamp, curr->id, "died");
	pthread_mutex_unlock(curr->print_mutex);
}

void	check_for_deads(t_philosopher *philos, t_rules *rules)
{
	int	i;

	if (!rules->amount)
		return ;
	while (check_eating_counts(philos, rules))
	{
		i = 0;
		while (i < rules->amount)
		{
			if (get_time_since_last_meal(philos + i) >= rules->time_to_die)
			{
				handle_philo_death(philos + i);
				if (rules->amount == 1)
					pthread_mutex_unlock(&(philos->fork_mutex));
				return ;
			}
			i++;
		}
		usleep(10);
	}
}
