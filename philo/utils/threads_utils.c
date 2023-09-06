/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:42 by stde-la-          #+#    #+#             */
/*   Updated: 2023/08/13 13:06:58 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	join_threads(t_data *data, int launched_threads)
{
	int	i;

	if (launched_threads == 0)
		launched_threads = data->rules.amount;
	i = 0;
	while (i < launched_threads)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

int	start_threads(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->start_mutex));
	i = 0;
	while (i < data->rules.amount)
	{
		if (pthread_create(&(data->philos[i].thread),
				NULL, routine, &(data->philos[i])))
		{
			return (i + 1);
		}
		i++;
	}
	data->rules.starting_time = now();
	i = 0;
	while (i < data->rules.amount)
	{
		data->philos[i].last_meal_time = data->rules.starting_time;
		i++;
	}
	pthread_mutex_unlock(&(data->start_mutex));
	return (0);
}

int	is_end_of_simulation(t_philosopher *curr)
{
	int	result;

	pthread_mutex_lock(curr->is_end_mutex);
	result = *(curr->is_end);
	pthread_mutex_unlock(curr->is_end_mutex);
	return (result);
}
