/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 15:26:42 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/15 15:26:43 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	handle_mutex(pthread_mutex_t *mutex, int *data, int new_value)
{
	pthread_mutex_lock(mutex);
	*data = new_value;
	pthread_mutex_unlock(mutex);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.amount)
	{
		pthread_join(data->philos[i].thread, NULL);
		i++;
	}
	return (0);
}

void	enable_philos_start(t_data *data)
{
	data->rules.starting_time = now();
	pthread_mutex_lock(&(data->rules.start_philos_mutex));
	data->rules.start_philos = 1;
	pthread_mutex_unlock(&(data->rules.start_philos_mutex));
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rules.amount)
	{
		pthread_create(&(data->philos[i].thread),
			NULL, routine, &(data->philos[i]));
		i++;
	}
	enable_philos_start(data);
	return (1);
}

int	is_end_of_simulation(t_philosopher *curr)
{
	int	result;

	pthread_mutex_lock(curr->is_end_mutex);
	result = *(curr->is_end);
	pthread_mutex_unlock(curr->is_end_mutex);
	return (result);
}
