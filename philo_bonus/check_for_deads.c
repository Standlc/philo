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
		if (philos[i].eating_count != rules->required_eat_count)
			return (1);
		i++;
	}
	return (0);
}

void	unlock_semaphores(t_rules *rules)
{
	sem_post(rules->forks);
}

void	check_for_deads(t_philosopher *philos, t_rules *rules)
{
	int	i;
	int	curr_time;
	int	timestamp;

	while (check_eating_counts(philos, rules))
	{
		i = 0;
		curr_time = now();
		while (i < rules->amount)
		{
			if (curr_time - philos[i].last_meal_time >= rules->time_to_die)
			{
				sem_post(rules->some_dead);
				timestamp = now() - rules->starting_time;
				printf("%d %d died\n", timestamp, philos[i].id);
				// unlock_semaphores(rules);
				return ;
			}
			i++;
		}
		usleep(1000);
	}
}
