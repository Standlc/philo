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

//PROTECT MUTEXES
void	init_philosopher(t_data *data, t_philosopher *curr, int i)
{
	data->philos[i].print_mutex = &(data->print_mutex);
	data->philos[i].some_dead_mutex = &(data->some_dead_mutex);
	curr->some_dead = &(data->some_dead);
	curr->rules = data->rules;
	curr->last_meal_time = data->rules.starting_time;
	curr->id = i + 1;
	curr->eating_count = 0;
	pthread_mutex_init(&(curr->fork_mutex), NULL);
	pthread_mutex_init(&(curr->eating_count_mutex), NULL);
	pthread_mutex_init(&(curr->last_meal_mutex), NULL);
}

int	create_philos(t_data *data)
{
	int	i;

	data->philos = malloc(sizeof(t_philosopher) * data->rules.amount);
	if (!data->philos)
		return (1);
	i = 0;
	while (i < data->rules.amount)
	{
		init_philosopher(data, data->philos + i, i);
		i++;
	}
	return (0);
}

int	args_to_int(t_rules *rules, int argc, char **argv)
{
	int	overflow_status;

	overflow_status = 0;
	rules->amount = ft_atoi(argv[1], &overflow_status);
	rules->time_to_die = ft_atoi(argv[2], &overflow_status);
	rules->time_to_eat = ft_atoi(argv[3], &overflow_status);
	rules->time_to_sleep = ft_atoi(argv[4], &overflow_status);
	if (argc == 6)
		rules->required_eat_count = ft_atoi(argv[5], &overflow_status);
	else
		rules->required_eat_count = -1;
	return (overflow_status);
}

int	handle_atoi_status(int atoi_status)
{
	if (atoi_status == INT_OVERFLOW)
		return (printf("arg error: interger overflow\n"), 1);
	else if (atoi_status == NEGATIVE_NB)
		return (printf("arg error: arguments must be positive and != 0\n"), 1);
	else if (atoi_status == CONTAINS_ALPHA)
		return (printf("arg error: arguments must be numbers\n"), 1);
	return (atoi_status);
}

int	init_data(t_data *data, int argc, char **argv)
{
	int	atoi_status;

	atoi_status = args_to_int(&(data->rules), argc, argv);
	if (handle_atoi_status(atoi_status))
		return (1);
	data->rules.starting_time = now();
	data->some_dead = 0;
	pthread_mutex_init(&(data->print_mutex), NULL);
	pthread_mutex_init(&(data->some_dead_mutex), NULL);
	return (0);
}
