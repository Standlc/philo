/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/15 17:17:07 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/15 17:17:08 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosopher(t_data *data, t_philosopher *curr, int i)
{
	curr->rules = &(data->rules);
	curr->last_meal_time = data->rules.starting_time;
	curr->id = i + 1;
	// curr->is_thinking = 0;
	curr->eating_count = 0;
	// pthread_mutex_init(&(curr->fork_mutex), NULL);
}

int	create_philos(t_data *data)
{
	int	i;
	int	starting_time;

	data->philos = malloc(sizeof(t_philosopher) * data->rules.amount);
	if (!data->philos)
		return (1);
	i = 0;
	starting_time = now();
	while (i < data->rules.amount)
	{
		// data->philos[i].print_mutex = &(data->print_mutex);
		init_philosopher(data, data->philos + i, i);
		i++;
	}
	return (0);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->rules.amount = ft_atoi(argv[1]);
	data->rules.time_to_die = ft_atoi(argv[2]);
	data->rules.time_to_eat = ft_atoi(argv[3]);
	data->rules.time_to_sleep = ft_atoi(argv[4]);
	sem_unlink("/forks");
	data->rules.forks = sem_open("/forks", O_CREAT, S_IRWXU, data->rules.amount);
	sem_unlink("/some_dead");
	data->rules.some_dead = sem_open("/some_dead", O_CREAT, S_IRWXU, 0);
	if (argc == 6)
	{
		data->rules.required_eat_count = ft_atoi(argv[5]);
		if (data->rules.required_eat_count <= 0)
			return (printf("You must pass a positive number of meals.\n"), 1);
	}
	else
		data->rules.required_eat_count = -1;
	data->rules.starting_time = now();
	data->rules.some_dead = 0;
	// pthread_mutex_init(&(data->print_mutex), NULL);
	return (0);
}
