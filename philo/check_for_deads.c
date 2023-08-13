/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_deads.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:26 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 12:28:39 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	end_simulation(t_philosopher *philos)
{
	pthread_mutex_lock(philos->is_end_mutex);
	*(philos->is_end) = 1;
	pthread_mutex_unlock(philos->is_end_mutex);
}

int	check_eating_counts(t_philosopher *philos, t_rules *rules)
{
	if (rules->required_eat_count == -1)
		return (1);
	pthread_mutex_lock(philos->philos_finished_eating_mutex);
	if (*(philos->philos_finished_eating) == rules->amount)
	{
		pthread_mutex_unlock(philos->philos_finished_eating_mutex);
		return (0);
	}
	pthread_mutex_unlock(philos->philos_finished_eating_mutex);
	return (1);
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

	end_simulation(curr);
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
