/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stde-la- <stde-la-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/07 16:31:30 by stde-la-          #+#    #+#             */
/*   Updated: 2023/02/14 12:55:16 by stde-la-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philosopher(t_philosopher *curr, int argc, char **argv, int i)
{
	curr->philosophers_amount = ft_atoi(argv[1]);
	curr->time_to_die = ft_atoi(argv[2]);
	curr->time_to_eat = ft_atoi(argv[3]);
	curr->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		curr->required_eating_amount = ft_atoi(argv[5]);
	else
		curr->required_eating_amount = -1;
	curr->id = i + 1;
	curr->fork = 1;
	curr->is_thinking = 0;
	curr->last_meal_time = now();
	curr->timestamps = 0;
	pthread_mutex_init(&(curr->fork_mutex), NULL);
	curr->is_alive = 1;
}

int	create_philosophers(t_data *data, int argc, char **argv)
{
	int	i;

	data->philosophers = malloc(sizeof(t_philosopher) * data->philosophers_amount);
	if (!data->philosophers)
		return (1);
	i = 0;
	while (i < data->philosophers_amount)
	{
		init_philosopher(&(data->philosophers[i]), argc, argv, i);
		i++;
	}
	return (0);
}

int	join_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_join(data->philosophers[i].thread, NULL);
		i++;
	}
	return (0);
}

int	start_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philosophers_amount)
	{
		pthread_create(&(data->philosophers[i].thread), NULL, routine, &(data->philosophers[i]));
		i++;
	}
	return (0);
}

void	wait(int time)
{
	int	now_now = now();

	while (now() - now_now < time)
		usleep(100);
}

void	eat(t_philosopher *left, t_philosopher *curr)
{
	curr->is_thinking = 0;
	curr->last_meal_time = now();

	printf("%d %d is eating\n", curr->timestamps, curr->id);
	// wait(curr->time_to_eat);
	usleep(curr->time_to_eat * 1000);
	pthread_mutex_lock(&(left->fork_mutex));
	pthread_mutex_lock(&(curr->fork_mutex));
	left->fork = 1;
	curr->fork = 1;
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(curr->fork_mutex));
}

int	check_for_deads(void *args)
{
	int		i;
	t_data	*data;
	int		now_time;

	data = (t_data *)args;
	while (1)
	{
		i = 0;
		now_time = now();
		while (i < data->philosophers_amount)
		{
			data->philosophers[i].timestamps = now_time - data->starting_time;
			if (now_time - data->philosophers[i].last_meal_time >= data->philosophers[i].time_to_die)
			{
				printf("%d %d died\n", data->philosophers[i].timestamps, data->philosophers[i].id);
				return (1);
			}
			i++;
		}
		usleep(1000);
	}
	return (0);
}

void	think(t_philosopher *curr)
{
	if (!curr->is_thinking)
		printf("%d %d is thinking\n", curr->timestamps, curr->id);
	curr->is_thinking = 1;
}

void	put_philosopher_to_bed(t_philosopher *curr)
{
	printf("%d %d is sleeping\n", curr->timestamps, curr->id);
	// wait(curr->time_to_sleep);
	usleep(curr->time_to_sleep * 1000);
}

int	take_forks(t_philosopher *left, t_philosopher *curr)
{
	pthread_mutex_lock(&(left->fork_mutex));
	pthread_mutex_lock(&(curr->fork_mutex));
	if (left->fork && curr->fork)
	{
		printf("%d %d has taken a fork\n", curr->timestamps, curr->id);
		printf("%d %d has taken a fork\n", curr->timestamps, curr->id);
		curr->fork = 0;
		left->fork = 0;
		pthread_mutex_unlock(&(left->fork_mutex));
		pthread_mutex_unlock(&(curr->fork_mutex)); 
		return (2);
	}
	pthread_mutex_unlock(&(left->fork_mutex));
	pthread_mutex_unlock(&(curr->fork_mutex)); 
	return (0);
}

void	*routine(void *args)
{
	int				eating_count;
	t_philosopher	*left;
	t_philosopher	*curr;
	// t_philosopher	*right;

	curr = (t_philosopher *)args;
	left = get_philosopher_to_left(curr);
	// right = get_philosopher_to_right(curr);
	eating_count = 0;
	while ((curr->required_eating_amount == -1 || eating_count <= curr->required_eating_amount))
	{
		if (take_forks(left, curr) == 2)
		{
			eat(left, curr);
			put_philosopher_to_bed(curr);
			eating_count++;
		}
		think(curr);
	}
	return (NULL);
}

// 5 800 200 200
int main(int argc, char **argv)
{
	t_data			data;

	if (argc != 5 && argc != 6)
		return (printf("You must pass the required arguments.\n"), 1);
	data.philosophers_amount = ft_atoi(argv[1]);
	data.starting_time = now();
	create_philosophers(&data, argc, argv);
	start_threads(&data);
	check_for_deads(&data);
	// join_threads(&data);
	free_philosophers(data.philosophers, data.philosophers_amount);
	return (0);
}
